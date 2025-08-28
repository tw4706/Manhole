#pragma once
class Title
{
public:
	Title();
	~Title();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	// タイトル画面のグラフィックハンドル
	int m_titleGraphHandle;
	int m_titleLogoHandle;
	// BGMのグラフィックハンドル
	int m_bgmHandle;

};

