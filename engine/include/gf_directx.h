/**
 * @file gf_directx.h
 * @~english
 * @brief DirectX headers
 * @note User should not include this, this header is used internally
 */

#ifndef __GF_DIRECTX_H__
#define __GF_DIRECTX_H__

#ifdef _WIN32
#include <windows.h>
#endif
#if defined(USE_DX11)
#include <d3d11.h>
#include <dxgi1_3.h>
#include <d3dcompiler.h>
#endif

#endif
