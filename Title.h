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
	// BGMのグラフィックハンドル
	int m_bgmHandle;

};

