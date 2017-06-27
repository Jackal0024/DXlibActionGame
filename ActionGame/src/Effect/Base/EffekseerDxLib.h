#ifndef EFFECSEER_DXLIB_H_
#define EFFECSEER_DXLIB_H_

#include "DxLib.h"

int Effkseer_Init(int spriteMaxCount = 2048, int instanceMaxCount = 2048, int voiceMaxCount = 32);

void Effkseer_End();

int LoadEffekseerEffect(const char* fileName);

void Effekseer_Sync3DSetting();

void DeleteEffekseerEffect(int effectHandle);

void UpdateEffekseer(float deltaFrame);

void DrawEffekseer();

int PlayEffekseerEffect(int effectHanlde, float x = 0.0f, float y = 0.0f, float z = 0.0f);

void StopPlayingEffeckseerEffect(int playngEffectHandle);

void IsEffeckseerEffectPlaying(int playngEffectHandle);

void SetPosPlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z);

void SetRotationPlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z);

void SetScalePlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z);

void SetMatrixPlayingEffeckseerEffect(int playngEffectHandle, const MATRIX& mat);

void SetBaseMatrixPlayingEffeckseerEffect(int playngEffectHandle, const MATRIX& mat);

void SetTargetPosPlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z);

void ShowPlayingEffeckseerEffect(int playngEffectHandle, bool shown);

void PauseEffeckseerEffect(int playngEffectHandle, bool paused);

void CalcCullingEffeckseerEffect(int playngEffectHandle);

// 
#ifdef NDEBUG
#pragma comment(lib, "Effekseer.ReleaseMT.lib" )
#pragma comment(lib, "EffekseerRendererDX11.Release.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.ReleaseMT.lib" )
#else
#pragma comment(lib, "Effekseer.DebugMT.lib" )
#pragma comment(lib, "EffekseerRendererDX11.Debug.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.DebugMT.lib" )
#endif
#pragma comment(lib, "xaudio2.lib")

#endif
