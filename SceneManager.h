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

	// 現在のシーンを取得する関数
	void ChangeScene(SceneType nextScene);

private:
	// 現在のシーンのタイプ
	SceneType m_currentType;
	// SceneTitleの変数
	Title* m_title;
	// SceneMainの変数
	SceneMain* m_main;
};

