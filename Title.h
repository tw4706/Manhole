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
	int m_titleLogoHandle;
	// BGM�̃O���t�B�b�N�n���h��
	int m_bgmHandle;

};

