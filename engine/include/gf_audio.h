/**
 * @file gf_audio.h
 * @~english
 * @brief Audio interface
 */

#ifndef __GF_AUDIO_H__
#define __GF_AUDIO_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/audio.h>

/* Engine */
#include <gf_type/core.h>

/* Standard */
#include <stddef.h>

/**
 * @~english
 * @brief Create audio interface
 * @param engine Engine instance
 * @return Audio interface
 */
GF_EXPORT gf_audio_t* gf_audio_create(gf_engine_t* engine);

/**
 * @~english
 * @brief Destroy audio interface
 * @param audio Audio interface
 */
GF_EXPORT void gf_audio_destroy(gf_audio_t* audio);

/**
 * @~english
 * @brief Destroy audio decoder
 * @param decoder Audio decoder
 */
GF_EXPORT void gf_audio_decoder_destroy(gf_audio_decoder_t* decoder);

/**
 * @~english
 * @brief Load and play file
 * @param audio Audio interface
 * @param path Path
 * @return `0` if successful, otherwise `-1`
 */
int gf_audio_load_file(gf_audio_t* audio, const char* path);

/**
 * @~english
 * @brief Load and play data
 * @param audio Audio interface
 * @param data Data
 * @param size Data size
 * @return `0` if successful, otherwise `-1`
 */
int gf_audio_load(gf_audio_t* audio, const void* data, size_t size);

#endif
