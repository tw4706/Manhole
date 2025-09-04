#pragma once
#include"Title.h"
#include"SceneMain.h"

enum SceneType
{
	SCENE_TITLE,
	SCENE_MAIN,
};

enum FadeState
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN
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
	Title m_title;
	// SceneMain�̕ϐ�
	SceneMain m_main;
	// ���̃V�[���J�ڕۑ��p�ϐ�
	SceneType m_nextScene;
	// �t�F�[�h����
	FadeState m_fadeState;
	int m_fadeAlpha;
	// �t�F�[�h�C�����I�����Ă��邩�ǂ���
	bool m_hasFadeIn = false;
	// ���艹�̃T�E���h
	int m_pushHandle;
};

