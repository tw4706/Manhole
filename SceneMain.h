#pragma once
#include"Player.h"
#include"Bg.h"
#include"Manhole.h"
#include"Timer.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

private:
	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_player1GraphHandle; 
	int m_player2GraphHandle;
	// �v���C���[�̍U���O���t�B�b�N�n���h��
	int m_player1AttackGraphHandle; 
	int m_player2AttackGraphHandle;
	// �v���C���[�̎�U���O���t�B�b�N�n���h��
	int m_player1WeakAttackGraphHandle;
	int m_player2WeakAttackGraphHandle;
	// �v���C���[�̑���O���t�B�b�N�n���h��
	int m_player1RunGraphHandle;	
	int m_player2RunGraphHandle;
	// �v���C���[�̍U�����󂯂����̃n���h��
	int m_player1HurtGraphHandle;
	int m_player2HurtGraphHandle;
	// �v���C���[�̗������̃O���t�B�b�N�n���h��
	int m_player1FallGraphHandle;
	int m_player2FallGraphHandle;
	// �}���z�[���̃O���t�B�b�N�n���h��
	int m_manhole1GraphHandle;
	int m_manhole2GraphHandle;
	// ���������v���C���[�̃n���h��
	int m_winPlayer1GraphHandle;
	int m_winPlayer2GraphHandle;
	// �Q�[����ʂ̎��Ԃ��J�E���g����ϐ�
	int m_timer;
	// �Q�[���X�^�[�g�̎��Ԃ��J�E���g����ϐ�
	int m_startTimer;
	// �Q�[���X�^�[�g�̃V�[�P���X
	bool m_isStartSeq;
	// �Q�[���J�n���}�̃T�E���h
	int m_gameStartSoundHandle;
	// �Q�[���J�n��UI�n���h��
	int m_gameStartUI1Handle;
	int m_gameStartUI2Handle;
	// �Q�[���I�[�o�[�̃t���O
	bool m_gameOver;
	// ���������v���C���[�̃t���O
	bool m_player1WinFlag;
	bool m_player2WinFlag;
	// BGM�̃n���h��
	int m_bgmHandle;
	// ��������BGM�n���h��
	int m_winBgmHandle;
	// �Q�[���I�[�o�[�̃T�E���h
	int m_gameOverBgHandle;

	// �v���C���[
	Player*m_player1;
	Player*m_player2;
	// �w�i
	Bg* m_Bg;
	// �}���z�[��
	Manhole* m_manhole;
	// �^�C�}�[
	Timer*m_roundTimer;
};