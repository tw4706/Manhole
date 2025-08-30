#include "SceneManager.h"
#include"Dxlib.h"

namespace
{
	constexpr int kFadeSpeed = 5;
}

SceneManager::SceneManager():
	m_currentType(SCENE_TITLE),
	m_nextScene(SCENE_TITLE),
	m_title(nullptr),
	m_main(nullptr),
	m_fadeState(FADE_NONE),
	m_fadeAlpha(0),
	m_hasFadeIn(false),
	m_pushHandle(-1)
{
}

SceneManager::~SceneManager()
{
	if (m_title)
	{
		m_title->End();
		delete m_title;
	}
	if (m_main)
	{
		m_main->End();
		delete m_main;
	}
}

void SceneManager::Init()
{
 	m_title = new Title();
	m_title->Init();
	m_pushHandle = LoadSoundMem("data/push.mp3");
}

void SceneManager::End()
{
	StopSoundMem(m_pushHandle);
	DeleteSoundMem(m_pushHandle);
}

void SceneManager::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_PAD1);
	int pad2 = GetJoypadInputState(DX_INPUT_PAD2);
	switch (m_fadeState)
	{
	case FADE_NONE:
		switch (m_currentType)
		{
		case SCENE_TITLE:
			m_title->Update();
			// Enter�L�[����������Q�[����ʂɔ��

			if (CheckHitKey(KEY_INPUT_RETURN) || (pad & PAD_INPUT_A) || (pad2 & PAD_INPUT_A))
			{
				PlaySoundMem(m_pushHandle, DX_PLAYTYPE_BACK);
				ChangeVolumeSoundMem(200, m_pushHandle);
				m_fadeState = FADE_OUT;
				m_fadeAlpha = 0;
				m_nextScene = SCENE_MAIN;
			}
			break;

		case SCENE_MAIN:
			m_main->Update();
			break;
		}
		break;
	case FADE_OUT:
		m_fadeAlpha += kFadeSpeed;
		if (m_fadeAlpha >= 255)
		{
			m_fadeAlpha = 255;
			ChangeScene(SCENE_MAIN);
			// �ŏ��̃t�F�[�h�C����������
			if (!m_hasFadeIn)
			{
				m_fadeState = FADE_IN;
				m_hasFadeIn = true;
			}
			else
			{
				m_fadeState = FADE_NONE;
			}
		}
		break;
	case FADE_IN:
		m_fadeAlpha -= kFadeSpeed;
		if (m_fadeAlpha <= 0)
		{
			m_fadeAlpha = 0;
			m_fadeState = FADE_NONE;
		}
		break;
	}
}

void SceneManager::Draw()
{
	switch (m_currentType)
	{
	case SCENE_TITLE:
		m_title->Draw();
		break;
	case SCENE_MAIN:
		m_main->Draw();
		break;
	}
	if (m_fadeState != FADE_NONE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
		DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}

// �V�[���̐؂�ւ�
void SceneManager::ChangeScene(SceneType nextScene)
{
	switch (m_currentType)
	{
	case SCENE_TITLE:
		m_title->End();
		delete m_title;
		m_title = nullptr;
		break;

		case SCENE_MAIN:
			m_main->End();
			delete m_main;
			m_main = nullptr;
			break;
	}
	m_currentType = nextScene;
	switch (m_currentType)
	{
	case SCENE_TITLE:
		m_title = new Title();
		m_title->Init();
		break;

	case SCENE_MAIN:
		m_main = new SceneMain();
		m_main->Init();
		break;
	}


}
