#pragma once
class Bg
{
public:
	Bg();
	~Bg();

	void Init(int _handle);
	void End();
	void Update();
	void Draw();

private:
	// �w�i�̃n���h��
	int m_handle;
	// �O���t�B�b�N�����ɉ��`�b�v�����邩�̏��
	int m_graphChipNumX;
};

