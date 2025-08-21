#include "SceneManager.h"
#include"Dxlib.h"

SceneManager::SceneManager():
	m_currentType(SCENE_TITLE),
	m_title(nullptr),
	m_main(nullptr)
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
}

void SceneManager::Update()
{
	switch (m_currentType)
	{
	case SCENE_TITLE:
		m_title->Update();
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			ChangeScene(SCENE_MAIN);
		}
		break;

	case SCENE_MAIN:
		m_main->Update();
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
}

// ƒV[ƒ“‚ÌØ‚è‘Ö‚¦
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
