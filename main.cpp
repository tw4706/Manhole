#include "DxLib.h"
#include"Game.h"
#include"SceneMain.h"
#include"SceneManager.h"

namespace
{

}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�C���h�E���[�h�ݒ�
	ChangeWindowMode(false);
	// �E�C���h�E�̃^�C�g���ύX
	SetMainWindowText("ManholeFight");
	// ��ʂ̃T�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �`��Ώۂ��o�b�N�o�b�t�@�ɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	int temp = LoadGraph("data/Player1.idle.png");
	SceneManager SceneManager;
	SceneManager.Init();

	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n���Ԃ��擾
		LONGLONG start = GetNowHiPerformanceCount();

		// �O�̃t���[���ɕ`�悵�����e���N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		SceneManager.Update();
		SceneManager.Draw();

		// esc�L�[����������Q�[���������I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// �`�悵�����e����ʂɔ��f����
		ScreenFlip();

		// �t���[�����[�g60�ɌŒ�
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}