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

const char* gf_audio_mod_sig[] = {"M!K!", "M.K.", "FLT4", "FLT8", "4CHN", "6CHN", "8CHN", "10CH", "12CH", "14CH", "16CH", "18CH", "20CH", "22CH", "24CH", "26CH", "28CH", "30CH", "32CH"};

void gf_audio_callback(ma_device* dev, void* output, const void* input, ma_uint32 frame) {
	gf_audio_id_t i;
	gf_audio_t*   audio    = dev->pUserData;
	ma_int16*     out      = (ma_int16*)output;
	float*	      tmp      = malloc(sizeof(*tmp) * frame * 2);
	int	      unlocked = 0;

	for(i = 0; i < (gf_audio_id_t)frame; i++) {
		tmp[2 * i + 0] = 0;
		tmp[2 * i + 1] = 0;
	}

	ma_mutex_lock(audio->mutex);
	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		if(audio->decoder[i].used == 1 && audio->decoder[i].decoder != NULL) {
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
				ma_mutex_unlock(audio->mutex);
				unlocked = 1;
				gf_audio_decoder_destroy(&audio->decoder[i]);
			}
		} else if(audio->decoder[i].used == 1 && audio->decoder[i].xm != NULL) {
			int    j;
			int    gotframe;
			float* r = malloc(sizeof(*r) * frame * 2);
			jar_xm_generate_samples(audio->decoder[i].xm, r, frame);
			gotframe = audio->decoder[i].samples > (gf_audio_id_t)frame ? frame : audio->decoder[i].samples;
			for(j = 0; j < gotframe; j++) {
				tmp[2 * j + 0] += (double)r[2 * j + 0];
				tmp[2 * j + 1] += (double)r[2 * j + 1];
			}
			free(r);
			audio->decoder[i].samples -= frame;
			if(audio->decoder[i].samples <= 0) {
				ma_mutex_unlock(audio->mutex);
				unlocked = 1;
				gf_audio_decoder_destroy(&audio->decoder[i]);
			}
		} else if(audio->decoder[i].used == 1 && audio->decoder[i].mod != NULL) {
			int	  j;
			int	  gotframe;
			ma_int16* r = malloc(sizeof(*r) * frame * 2);
			jar_mod_fillbuffer(audio->decoder[i].mod, r, frame, NULL);
			gotframe = audio->decoder[i].samples > (gf_audio_id_t)frame ? frame : audio->decoder[i].samples;
			for(j = 0; j < gotframe; j++) {
				tmp[2 * j + 0] += (double)r[2 * j + 0] / 32768.0;
				tmp[2 * j + 1] += (double)r[2 * j + 1] / 32768.0;
			}
			free(r);
			audio->decoder[i].samples -= frame;
			if(audio->decoder[i].samples <= 0) {
				ma_mutex_unlock(audio->mutex);
				unlocked = 1;
				gf_audio_decoder_destroy(&audio->decoder[i]);
			}
		}
	}
	if(!unlocked) ma_mutex_unlock(audio->mutex);

	for(i = 0; i < (gf_audio_id_t)frame; i++) {
		out[2 * i + 0] = tmp[2 * i + 0] * 32768;
		out[2 * i + 1] = tmp[2 * i + 1] * 32768;
	}
	free(tmp);
}

gf_audio_id_t gf_audio_load(gf_audio_t* audio, const void* data, size_t size) {
	gf_audio_id_t i;
	ma_mutex_lock(audio->mutex);
	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		if(audio->decoder[i].used == 0) {
			int xm_cond  = size > 37 && memcmp(data, "Extended Module: ", 17) == 0 && ((char*)data)[37] == 0x1a;
			int mod_cond = size > 1080;

			if(mod_cond) {
				int j;
				int mod_sig_cond = 0;
				for(j = 0; j < sizeof(gf_audio_mod_sig) / sizeof(gf_audio_mod_sig[0]); j++) {
					mod_sig_cond = mod_sig_cond || (memcmp((char*)data + 1080, gf_audio_mod_sig[j], 4) == 0);
				}
				mod_cond = mod_cond && mod_sig_cond;
			}

			if(xm_cond) {
				if(jar_xm_create_context_safe(&audio->decoder[i].xm, data, size, audio->device_config.sampleRate) == 0) {
					audio->decoder[i].samples = jar_xm_get_remaining_samples(audio->decoder[i].xm);
					audio->decoder[i].used	  = -1;
					ma_mutex_unlock(audio->mutex);
					return i;
				}
				audio->decoder[i].xm = NULL;
			} else if(mod_cond) {
				audio->decoder[i].mod = malloc(sizeof(*audio->decoder[i].mod));
				jar_mod_init(audio->decoder[i].mod);
				jar_mod_setcfg(audio->decoder[i].mod, audio->device_config.sampleRate, 16, 1, 0, 0);
				if(jar_mod_load(audio->decoder[i].mod, (void*)data, size)) {
					audio->decoder[i].samples = jar_mod_max_samples(audio->decoder[i].mod);
					audio->decoder[i].used	  = -1;
					ma_mutex_unlock(audio->mutex);
					return i;
				}
				free(audio->decoder[i].mod);
				audio->decoder[i].mod = NULL;
			}
			audio->decoder[i].decoder = malloc(sizeof(*audio->decoder[i].decoder));
			if(ma_decoder_init_memory(data, size, &audio->decoder[i].decoder_config, audio->decoder[i].decoder) == MA_SUCCESS) {
				audio->decoder[i].used = -1;
				ma_mutex_unlock(audio->mutex);
				return i;
			}
			free(audio->decoder[i].decoder);
			audio->decoder[i].decoder = NULL;
			ma_mutex_unlock(audio->mutex);
			return -1;
		}
	}
	ma_mutex_unlock(audio->mutex);
	return -1;
}

gf_audio_id_t gf_audio_load_file(gf_audio_t* audio, const char* path) {
	FILE*	       f = fopen(path, "rb");
	size_t	       sz;
	unsigned char* data;
	gf_audio_id_t  st;
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
		audio->decoder[i].audio		 = NULL;
		audio->decoder[i].decoder	 = NULL;
		audio->decoder[i].xm		 = NULL;
		audio->decoder[i].mod		 = NULL;
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

	audio->mutex = malloc(sizeof(*audio->mutex));
	if(ma_mutex_init(audio->mutex) != MA_SUCCESS) {
		gf_log_function(engine, "Failed to create mutex", "");
		free(audio->mutex);
		audio->mutex = NULL;
		gf_audio_destroy(audio);
		return NULL;
	}

	if(ma_device_start(audio->device) != MA_SUCCESS) {
		gf_log_function(engine, "Failed to start playback device", "");
		gf_audio_destroy(audio);
		return NULL;
	}

	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		audio->decoder[i].audio = audio;
	}

	gf_log_function(engine, "Audio interface started, max %d decoders", GF_AUDIO_MAX_DECODERS);

	return audio;
}

void gf_audio_decoder_destroy(gf_audio_decoder_t* decoder) {
	ma_mutex_lock(decoder->audio->mutex);
	if(decoder->decoder != NULL) {
		ma_decoder_uninit(decoder->decoder);
		free(decoder->decoder);
		decoder->decoder = NULL;
	}
	if(decoder->xm != NULL) {
		jar_xm_free_context(decoder->xm);
		decoder->xm = NULL;
	}
	if(decoder->mod != NULL) {
		jar_mod_unload(decoder->mod);
		free(decoder->mod);
		decoder->mod = NULL;
	}
	decoder->used = 0;
	ma_mutex_unlock(decoder->audio->mutex);
}

void gf_audio_destroy(gf_audio_t* audio) {
	int i;
	if(audio->device != NULL) {
		ma_device_uninit(audio->device);
		free(audio->device);
	}
	if(audio->mutex != NULL) {
		ma_mutex_uninit(audio->mutex);
		free(audio->mutex);
	}
	for(i = 0; i < GF_AUDIO_MAX_DECODERS; i++) {
		gf_audio_decoder_destroy(&audio->decoder[i]);
	}
	gf_log_function(audio->engine, "Destroyed audio interface", "");
	free(audio);
}

void gf_audio_resume(gf_audio_t* audio, gf_audio_id_t id) {
	ma_mutex_lock(audio->mutex);
	if(audio->decoder[id].used != 0) audio->decoder[id].used = 1;
	ma_mutex_unlock(audio->mutex);
}

void gf_audio_pause(gf_audio_t* audio, gf_audio_id_t id) {
	ma_mutex_lock(audio->mutex);
	if(audio->decoder[id].used != 0) audio->decoder[id].used = -1;
	ma_mutex_unlock(audio->mutex);
}

void gf_audio_stop(gf_audio_t* audio, gf_audio_id_t id) { gf_audio_decoder_destroy(&audio->decoder[id]); }
