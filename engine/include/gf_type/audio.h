/**
 * @file gf_type/audio.h
 * @~english
 * @brief Type definitions related to audio interface
 */

#ifndef __GF_TYPE_AUDIO_H__
#define __GF_TYPE_AUDIO_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_AUDIO
typedef struct gf_audio_t	  gf_audio_t;
typedef struct gf_audio_decoder_t gf_audio_decoder_t;

/* External library */
#include <miniaudio.h>
#include <jar_xm.h>
#include <jar_mod.h>

/* Engine */
#include <gf_type/core.h>

/* Standard */

/**
 * @~english
 * @brief Max decoders audio interface can handle
 */
#define GF_AUDIO_MAX_DECODERS 64

/**
 * @struct gf_audio_decoder_t
 * @~english
 * @brief Audio decoder
 *
 * @var gf_audio_decoder_t::decoder_config
 * @brief miniaudio decoder config
 *
 * @var gf_audio_decoder_t::decoder
 * @brief miniaudio decoder
 *
 * @var gf_audio_decoder_t::xm
 * @brief XM context
 *
 * @var gf_audio_decoder_t::mod
 * @brief MOD context
 *
 * @var gf_audio_decoder_t::samples
 * @brief Remaining samples
 *
 * @var gf_audio_decoder_t::used
 * @brief `1` if used, otherwise `0`
 */
GF_DECLARE_TYPE(audio_decoder, {
	ma_decoder_config  decoder_config;
	ma_decoder*	   decoder;
	jar_xm_context_t*  xm;
	jar_mod_context_t* mod;
	int		   samples;
	int		   used;
});

/**
 * @struct gf_audio_t
 * @~english
 * @brief Audio interface
 *
 * @var gf_audio_t::engine
 * @brief Engine instance
 *
 * @var gf_audio_t::device_config
 * @brief miniaudio device config
 *
 * @var gf_audio_t::device
 * @brief miniaudio device
 *
 * @var gf_audio_t::decoder
 * @brief Decoder
 */
GF_DECLARE_TYPE(audio, {
	gf_engine_t*	   engine;
	ma_device_config   device_config;
	ma_device*	   device;
	gf_audio_decoder_t decoder[GF_AUDIO_MAX_DECODERS];
});
#else
typedef void gf_audio_decoder_t;
typedef void gf_audio_t;
#endif

#endif
