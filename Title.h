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
	// BGM�̃O���t�B�b�N�n���h��
	int m_bgmHandle;

};

