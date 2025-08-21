#pragma once
#include"Title.h"
#include"SceneMain.h"

enum SceneType
{
	SCENE_TITLE,
	SCENE_MAIN,
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();
	void Update();
	void Draw();

	// ���݂̃V�[�����擾����֐�
	void ChangeScene(SceneType nextScene);

private:
	// ���݂̃V�[���̃^�C�v
	SceneType m_currentType;
	// SceneTitle�̕ϐ�
	Title* m_title;
	// SceneMain�̕ϐ�
	SceneMain* m_main;
};

