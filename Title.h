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
	// �^�C�g����ʂ̃O���t�B�b�N�n���h��
	int m_titleGraphHandle;
	// BGM�̃O���t�B�b�N�n���h��
	int m_bgmHandle;

};

