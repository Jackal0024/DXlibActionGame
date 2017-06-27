#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>
#include <unordered_map>
#include <DxLib.h>

static Effekseer::Manager*			g_manager  = nullptr;
static EffekseerRenderer::Renderer* g_renderer = nullptr;
static EffekseerSound::Sound*		g_sound    = nullptr;

static ID3D11Device*				g_device = nullptr;
static ID3D11DeviceContext*			g_context = nullptr;

static IXAudio2*					g_xa2 = nullptr;
static IXAudio2MasteringVoice*		g_xa2_master = nullptr;

static int g_effect_handle = 0;
static std::unordered_map<int, Effekseer::Effect*> g_effects;

int Effkseer_Init(int spriteMaxCount, int instanceMaxCount, int voiceMaxCount) {
	g_device  = (ID3D11Device*)GetUseDirect3D11Device();
	g_context = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
	g_renderer = EffekseerRendererDX11::Renderer::Create(g_device, g_context, spriteMaxCount);

	g_manager = Effekseer::Manager::Create(instanceMaxCount);
	g_manager->SetSpriteRenderer(g_renderer->CreateSpriteRenderer());
	g_manager->SetRibbonRenderer(g_renderer->CreateRibbonRenderer());
	g_manager->SetRingRenderer(g_renderer->CreateRingRenderer());
	g_manager->SetTrackRenderer(g_renderer->CreateTrackRenderer());
	g_manager->SetModelRenderer(g_renderer->CreateModelRenderer());

	g_manager->SetTextureLoader(g_renderer->CreateTextureLoader());
	g_manager->SetModelLoader(g_renderer->CreateModelLoader());

	g_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

	XAudio2Create(&g_xa2);
	g_xa2->CreateMasteringVoice(&g_xa2_master);

	g_sound = EffekseerSound::Sound::Create(g_xa2, voiceMaxCount, voiceMaxCount);
	g_manager->SetSoundPlayer(g_sound->CreateSoundPlayer());
	g_manager->SetSoundLoader(g_sound->CreateSoundLoader());
	return 0;
}

void Effkseer_End() {
	for (auto effect : g_effects) {
		effect.second->Release();
	}
	g_effects.clear();
	g_effect_handle = 0;
	if (g_manager != nullptr) {
		g_manager->Destroy();
		g_manager = nullptr;
	}
	if (g_sound != nullptr) {
		g_sound->Destory();
		g_sound = nullptr;
	}
	if (g_renderer != nullptr) {
		g_renderer->Destory();
		g_renderer = nullptr;
	}
	if (g_xa2_master != nullptr) {
		g_xa2_master->DestroyVoice();
		g_xa2_master = nullptr;
	}
	if (g_xa2 != nullptr) {
		g_xa2->Release();
		g_xa2 = nullptr;
	}
}

static Effekseer::Matrix43 ConvertMatrixToEffekseerMatrix43(const MATRIX& mat) {
	Effekseer::Matrix43 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.Value[i][j] = mat.m[i][j];
		}
	}
	return result;
}

static Effekseer::Matrix44 ConvertMatrixToEffekseerMatrix44(const MATRIX& mat) {
	Effekseer::Matrix44 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.Values[i][j] = mat.m[i][j];
		}
	}
	return result;
}

static MATRIX ConvertMatrixToEffekseerMatrix44(Effekseer::Matrix44& mat) {
	MATRIX result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = mat.Values[i][j];
		}
	}
	return result;
}

// SJIS‚ðUTF16‚É•ÏŠ·
static wchar_t* ConvertSjisToUTF16(const char* sjis) {
	// Shift-JIS•¶Žš—ñ‚©‚çUTF-16‚É•ÏŠ·‚µ‚½‚Æ‚«‚Ì•¶Žš—ñ’·‚ð‹‚ß‚é
	const int length = MultiByteToWideChar(CP_ACP, 0, sjis, strlen(sjis), NULL, 0);
	// UTF-16•¶Žš—ñ‚Ì—Ìˆæ‚ðŠm•Û‚·‚éB
	wchar_t* result = new wchar_t[length + 1];
	if (result != NULL) {
		// \0‚ð‘ã“ü
		result[length] = '\0';
		// Shift-JIS•¶Žš—ñ‚©‚çUTF-16‚É•ÏŠ·‚·‚é
		MultiByteToWideChar(CP_ACP, 0, sjis, strlen(sjis), result, length);
	}
	return result;
}

int LoadEffekseerEffect(const char* fileName) {
	const auto utf16_file_name = ConvertSjisToUTF16(fileName);
	const auto effect = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)utf16_file_name);
	delete [] utf16_file_name;
	if (effect == nullptr) {
		return -1;
	}
	g_effects[g_effect_handle] = effect;
	return g_effect_handle++;
}

void DeleteEffekseerEffect(int effectHandle) {
	if (g_effects.count(effectHandle) > 0) {
		g_effects[effectHandle]->Release();
		g_effects.erase(effectHandle);
	}
}

void Effekseer_Sync3DSetting() {
	g_renderer->SetCameraMatrix(ConvertMatrixToEffekseerMatrix44(GetCameraViewMatrix()));
	g_renderer->SetProjectionMatrix(ConvertMatrixToEffekseerMatrix44(GetCameraProjectionMatrix()));
}

void UpdateEffekseer(float deltaFrame) {
	g_manager->Update(deltaFrame);
}

void DrawEffekseer() {
	g_renderer->BeginRendering();
	g_manager->Draw();
	g_renderer->EndRendering();
}

int PlayEffekseerEffect(int effectHanlde, float x, float y, float z) {
	if (g_effects.count(effectHanlde) > 0) {
		return g_manager->Play(g_effects[effectHanlde], x, y, z);
	}
	return -1;
}

void StopPlayingEffeckseerEffect(int playngEffectHandle) {
	g_manager->StopEffect(playngEffectHandle);
}

void IsEffeckseerEffectPlaying(int playngEffectHandle) {
	g_manager->Exists(playngEffectHandle);
}

void SetPosPlayingEffeckseerEffect(int playngEffectHandle,float x, float y, float z) {
	g_manager->SetLocation(playngEffectHandle, x, y, z);
}

void SetRotationPlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z) {
	g_manager->SetRotation(playngEffectHandle, x, y, z);
}

void SetScalePlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z) {
	g_manager->SetScale(playngEffectHandle, x, y, z);
}

void SetMatrixPlayingEffeckseerEffect(int playngEffectHandle, const MATRIX& mat) {
	g_manager->SetMatrix(playngEffectHandle, ConvertMatrixToEffekseerMatrix43(mat));
}

void SetBaseMatrixPlayingEffeckseerEffect(int playngEffectHandle, const MATRIX& mat) {
	g_manager->SetBaseMatrix(playngEffectHandle, ConvertMatrixToEffekseerMatrix43(mat));
}

void SetTargetPosPlayingEffeckseerEffect(int playngEffectHandle, float x, float y, float z) {
	g_manager->SetTargetLocation(playngEffectHandle, x, y, z);
}

void ShowPlayingEffeckseerEffect(int playngEffectHandle, bool shown) {
	g_manager->SetShown(playngEffectHandle, shown);
}

void PauseEffeckseerEffect(int playngEffectHandle, bool paused) {
	g_manager->SetPaused(playngEffectHandle, paused);
}

void CalcCullingEffeckseerEffect(int playngEffectHandle) {
	g_manager->CalcCulling(g_renderer->GetCameraProjectionMatrix(), false);
}
