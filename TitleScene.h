#pragma once
class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void End();
	void Update();
	void Draw();

	// �^�C�g���V�[�����I�����Ă��邩�ǂ���
	bool IsSceneEnd() const;

private:
	// �V�[���I���t���O
	bool m_isSceneEnd;

};

