#define GF_EXPOSE_AUDIO

#include <gf_pre.h>

/* External library */
#include <miniaudio.h>
#include <jar_xm.h>
#include <jar_mod.h>

/* Interface */
#include <gf_audio.h>

/* Engine */
#include <gf_log.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void gf_audio_callback(ma_device* dev, void* output, const void* input, ma_uint32 frame) {
	int	    i;
	gf_audio_t* audio = dev->pUserData;
	ma_int16*   out	  = (ma_int16*)output;
	float*	    tmp	  = malloc(sizeof(*tmp) * frame * 2);

	for(i = 0; i < frame; i++) {
		tmp[2 * i + 0] = 0;
		tmp[2 * i + 1] = 0;
	}

	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		if(audio->decoder[i].used == 1) {
			ma_uint64 readframe;
			int	  j;
			ma_int16* r = malloc(sizeof(*r) * frame * 2);
			ma_decoder_read_pcm_frames(audio->decoder[i].decoder, r, frame, &readframe);
			for(j = 0; j < readframe; j++) {
				tmp[2 * j + 0] += (double)r[2 * j + 0] / 32768.0;
				tmp[2 * j + 1] += (double)r[2 * j + 1] / 32768.0;
			}
			free(r);
			if(frame > readframe) {
				ma_decoder_uninit(audio->decoder[i].decoder);
				free(audio->decoder[i].decoder);
				audio->decoder[i].decoder = NULL;
				audio->decoder[i].used	  = 0;
			}
		}
	}

	for(i = 0; i < frame; i++) {
		out[2 * i + 0] = tmp[2 * i + 0] * 32768;
		out[2 * i + 1] = tmp[2 * i + 1] * 32768;
	}
	free(tmp);
}

int gf_audio_load(gf_audio_t* audio, const void* data, size_t size) {
	int i;
	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		if(audio->decoder[i].used == 0) {
			audio->decoder[i].decoder = malloc(sizeof(*audio->decoder[i].decoder));
			if(ma_decoder_init_memory(data, size, &audio->decoder[i].decoder_config, audio->decoder[i].decoder) == MA_SUCCESS) {
				audio->decoder[i].used = 1;
				return 0;
			}
			free(audio->decoder[i].decoder);
			audio->decoder[i].decoder = NULL;
			return -1;
		}
	}
	return -1;
}

int gf_audio_load_file(gf_audio_t* audio, const char* path) {
	FILE*	       f = fopen(path, "rb");
	size_t	       sz;
	unsigned char* data;
	int	       st;
	if(f == NULL) return -1;
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	data = malloc(sz);
	fread(data, sz, 1, f);
	st = gf_audio_load(audio, data, sz);

	fclose(f);

	return st;
}

gf_audio_t* gf_audio_create(gf_engine_t* engine) {
	gf_audio_t* audio = malloc(sizeof(*audio));
	int	    i;

	memset(audio, 0, sizeof(*audio));
	audio->engine = engine;

	audio->device_config		       = ma_device_config_init(ma_device_type_playback);
	audio->device_config.playback.format   = ma_format_s16;
	audio->device_config.playback.channels = 2;
	audio->device_config.sampleRate	       = 44100;
	audio->device_config.dataCallback      = gf_audio_callback;
	audio->device_config.pUserData	       = audio;

	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		audio->decoder[i].used		 = 0;
		audio->decoder[i].decoder	 = NULL;
		audio->decoder[i].decoder_config = ma_decoder_config_init(audio->device_config.playback.format, audio->device_config.playback.channels, audio->device_config.sampleRate);
	}

	audio->device = malloc(sizeof(*audio->device));
	if(ma_device_init(NULL, &audio->device_config, audio->device) != MA_SUCCESS) {
		gf_log_function(engine, "Failed to open playback device", "");
		free(audio->device);
		audio->device = NULL;
		gf_audio_destroy(audio);
		return NULL;
	}

	if(ma_device_start(audio->device) != MA_SUCCESS) {
		gf_log_function(engine, "Failed to start playback device", "");
		gf_audio_destroy(audio);
		return NULL;
	}

	gf_log_function(engine, "Audio interface started", "");

	return audio;
}

void gf_audio_destroy(gf_audio_t* audio) {
	int i;
	if(audio->device != NULL) {
		ma_device_uninit(audio->device);
		free(audio->device);
	}
	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		if(audio->decoder[i].decoder != NULL) {
			ma_decoder_uninit(audio->decoder[i].decoder);
			free(audio->decoder[i].decoder);
		}
	}
	gf_log_function(audio->engine, "Destroyed audio interface", "");
	free(audio);
}
