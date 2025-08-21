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
	// グラフィックハンドル
	int m_handle;

};

