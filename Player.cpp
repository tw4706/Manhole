#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"
#include <algorithm>

namespace
{
	// プレイヤーサイズ
	constexpr float kPlayerSize = 48.0f;
	// プレイヤーグラフィックのサイズ
	constexpr int kGraphWidth = 48;
	constexpr int kGraphHeight = 48;
	// アニメーション情報
	constexpr int kIdleAnimNum = 4;
	constexpr int kAnimWaitFrame = 4;
	constexpr int kRunAnimNum = 6;
	constexpr int kAttackAnimNum = 8;
	constexpr int kWeakAttackAnimNum = 6;
	constexpr int kHurtAnimNum = 2;	
	// 攻撃クールタイム
	constexpr int kAttackCoolTime = 50;
	constexpr int kWeakAttackCoolTime = 30;
	//強攻撃の準備時間
	constexpr int kAttackPrep = 20;
	// 攻撃を受けた後の無敵時間
	constexpr int kHurtDuration = 30;
	constexpr int kWeakHurtDuration = 15;
	// 当たり判定の半径
	constexpr float kDefaultRadius = 16.0f;
	// プレイヤーの移動速度
	constexpr int  kSpeed = 2.0;
	// プレイヤーの拡大率
	constexpr float kScale = 2.0f;
	// ノックバックの距離
	constexpr int knockBackDist = 60;
	// 重力
	constexpr float kGravity = 1.5f;
	// 地面の当たり判定
	constexpr int kGround = 400;

}

Player::Player():
	m_handle(-1),
	m_attackHandle(-1),
	m_wAttackHandle(-1),
	m_runHandle(-1),
	m_hurtHandle(-1),
	m_pos(0.0f, 0.0f),
	m_centerPos(0.0f, 0.0f),
	m_padType(0),
	m_radius(0.0f),
	m_isAttack(false),
	m_attackCount(0),
	m_wAttackCount(0),
	m_attackPrepCount(0),
	m_hurtCount(0),
	m_isTurn(false),
	m_animFrame(0),
	m_oldInput(0),
	m_isFalling(false),
	m_fallSpeed(0.0f),
	m_gameOver(false),
	m_currentFrame(0),
	m_hasHit(false),
	m_state(PlayerState::Idle),
	m_attackType(AttackType::Normal),
	m_otherPlayer(nullptr)
{
}

Player::~Player()
{

}

void Player::Init(int _padType, Vec2 _firstPos,int _handle,int _attackHandle,int _wAttackHandle,int _runHandle,int _hurtHandle,bool _isTurn)
{
	// 初期化
	m_handle = _handle;
	m_attackHandle = _attackHandle;
	m_wAttackHandle = _wAttackHandle;
	m_runHandle = _runHandle;
	m_hurtHandle = _hurtHandle;
	m_pos = _firstPos;
	m_centerPos = Vec2(0.0f, 0.0f);
	m_padType = _padType;
	m_radius = kDefaultRadius;
	m_isAttack = false;
	m_attackCount = 0;
	m_wAttackCount = 0;
	m_attackPrepCount = 0;
	m_hurtCount = 0;
	m_isTurn = _isTurn;
	m_animFrame = 0;
	m_oldInput = 0;
	m_isFalling = false;
	m_fallSpeed = 0.0f;
	m_gameOver = false;
	m_currentFrame = 0;
	m_hasHit = false;
	m_state = PlayerState::Idle;
	m_attackType = AttackType::Normal;
}

void Player::End()
{
}

void Player::Update()
{
	// 重力
	Gravity();

	// 当たり判定
	if (m_isTurn)
	{
		m_colRect.init(m_pos.x - kGraphWidth / 2 + 64.0f,
		m_pos.y - kGraphHeight / 2 + 48.0f,
		kGraphWidth, kGraphHeight);
		
	}
	else
	{
		m_colRect.init(m_pos.x - kGraphWidth / 2 + 32.0f,
		m_pos.y - kGraphHeight / 2 + 48.0f,
		kGraphWidth, kGraphHeight);
	}

	//	コントローラーのボタンの押された状態を取得する
	int input = GetJoypadInputState(m_padType);
	// プレイヤーの状態の更新
	UpdateState(input);
	// プレイヤーのアニメーションの更新
	UpdateAnim();
	// 重力の制限
	if (!m_isFalling&& !m_gameOver && m_pos.y >= kGround)
	{
		m_pos.y = kGround;
	}
	// 強攻撃の孔隙判定（Attack状態）
	if (m_state == PlayerState::Attack && (m_animFrame >= 3 && m_animFrame <= 5))
	{
		KnockBack();
	}

	// 弱攻撃の攻撃判定（WeakAttack状態）
	if (m_state == PlayerState::WeakAttack && (m_animFrame >= 2 && m_animFrame <= 3))
	{
		KnockBack();
	}


}

void Player::Draw()
{
	// アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNum = 0;
	//// プレイヤーのそれぞれの状態をもとにX座標を計算する
	int srcX = 0;
	int srcY = 0;
	int handle = m_handle;

	// プレイヤーの状態に応じてアニメーションのハンドルを設定
	switch (m_state)
	{
	case PlayerState::Idle:			// 待機中
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_handle;
		srcY = 0;
		break;
	}

	case PlayerState::Run:			// 移動中
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kRunAnimNum;
		handle = m_runHandle;
		srcY = 0;
		break;
	}

	case PlayerState::Attack:		// 強攻撃
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kAttackAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;
	}

	case PlayerState::WeakAttack:	// 弱攻撃
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kWeakAttackAnimNum;
		handle = m_wAttackHandle;
		srcY = 0;
		break;
	}

	case PlayerState::Hurt:			// 攻撃を受けた状態
	{
		animNum = (m_animFrame / kAnimWaitFrame) % kHurtAnimNum;
		handle = m_hurtHandle;
		srcY = 0;
		break;
	}
	}

	// アニメーションのX座標を求める
	srcX = kGraphWidth * animNum;

	// プレイヤーの描画処理
	if (handle != -1)
	{
		if (m_isTurn) 
		{ 
			// 左向き
			DrawRectExtendGraph(
				static_cast<int>(m_pos.x) + 96, static_cast<int>(m_pos.y),
				static_cast<int>(m_pos.x), static_cast<int>(m_pos.y) + 96,
				srcX, srcY,
				48, 48,
				handle, TRUE);
		}
		else 
		{
			// 右向き
			DrawRectExtendGraph(
				static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
				static_cast<int>(m_pos.x) + kGraphWidth*kScale,
				static_cast<int>(m_pos.y) + kGraphHeight*kScale,
				srcX, srcY,
				kGraphWidth, kGraphHeight,
				handle, TRUE);
		}
	}
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0xFFFF00, false);
#endif
}

void Player::Gravity()
{
	// 重力を追加する
	m_pos.y += kGravity;
}

// プレイヤーの状態を更新する関数
void Player::UpdateState(int _input)
{
	// プレイヤーの状態を保存
	PlayerState saveState = m_state;
	// 攻撃のトリガーをチェック
	bool attackTrigger = (_input & PAD_INPUT_A) && !(m_oldInput & PAD_INPUT_A);
	// 弱攻撃のトリガーをチェック
	bool weakAttackTrigger = (_input & PAD_INPUT_B) && !(m_oldInput & PAD_INPUT_B);

	// プレイヤーの状態を更新する
	switch (m_state)
	{
	case PlayerState::Idle:
		if (!m_isAttack && IsMoving(_input))
		{
			m_state = PlayerState::Run;
		}
		else if (!m_isAttack && (_input & PAD_INPUT_A))
		{
			m_state = PlayerState::AttackPrep;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("攻撃した！\n");
		}
		else if (!m_isAttack && (_input & PAD_INPUT_B))
		{
			printfDx("Bボタンを押した！\n");
			m_attackType = AttackType::Weak;
			m_wAttackCount = 0;
			m_isAttack = true;
			m_state = PlayerState::WeakAttack;
			printfDx("弱攻撃した！\n");
		}
		break;

		// 強攻撃の準備状態
	case PlayerState::AttackPrep:
	{
		m_attackPrepCount++;
		if (m_attackPrepCount >= kAttackPrep)
		{
			m_state = PlayerState::Attack;
			m_attackPrepCount = 0;
			m_attackType = AttackType::Normal;
			printfDx("強攻撃の準備完了!\n");
		}
		break;
	}

	case PlayerState::Run:
	{
		// 移動処理
		if (_input & PAD_INPUT_LEFT && !(_input & PAD_INPUT_RIGHT))
		{
			m_pos.x -= kSpeed;
			m_isTurn = true;
		}
		if (_input & PAD_INPUT_RIGHT && !(_input & PAD_INPUT_LEFT))
		{
			m_pos.x += kSpeed;
			m_isTurn = false;
		}
		if (!IsMoving(_input))
		{
			m_state = PlayerState::Idle;
		}
		break;
	}

	case PlayerState::Attack:
		m_attackCount++;
		// 攻撃
		// 押した瞬間判定する
		if (!m_isAttack && attackTrigger)
		{
			m_state = PlayerState::Attack;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("攻撃！\n");
		}

		// 攻撃のカウントがクールタイムを超えたら
		if (m_attackCount > kAttackCoolTime)
		{
			m_isAttack = false;
			m_attackType = AttackType::Normal;
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			// 攻撃カウントをリセット
			m_attackCount = 0;
			m_hasHit = false;
		}
		break;

	case PlayerState::WeakAttack:	// 弱攻撃
		m_wAttackCount++;
		if (!m_isAttack && weakAttackTrigger)
		{
			m_state = PlayerState::WeakAttack;
			m_attackCount = 0;
			m_isAttack = true;
			printfDx("弱パンチ！\n");
		}

		if (m_wAttackCount > kWeakAttackCoolTime)
		{
			// クールタイムを超えたら通常状態に戻す
			m_isAttack = false;
			m_attackType = AttackType::Normal;// 攻撃タイプを通常に戻す
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			m_wAttackCount = 0;
			m_hasHit = false;
		}
		break;
	case PlayerState::Hurt:
		m_hurtCount++;
		// 攻撃を受けた後の無敵時間を経過したら通常状態に戻す
		if ((m_attackType == AttackType::Weak && m_hurtCount > kWeakHurtDuration) ||
			(m_attackType == AttackType::Normal && m_hurtCount > kHurtDuration))
		{
			m_state = PlayerState::Idle;
			m_hurtCount = 0;
			m_attackType = AttackType::Normal;
			printfDx("Hurt終了\n");
			m_oldInput = _input; // 前回の入力状態を更新
		}
		return;

		// 状態が切り替わったらアニメーションフレームをリセット
		if (saveState != m_state)
		{
			m_animFrame = 0;
		}
		m_oldInput = _input; // 前回の入力状態を更新
	}
}

// プレイヤーの移動反転処理
bool Player::IsMoving(int _input)
{
	return (_input & PAD_INPUT_LEFT) || (_input & PAD_INPUT_RIGHT);
}

// プレイヤーのアニメーション
void Player::UpdateAnim()
{
	int animFrames = 0;
	switch (m_state)
	{
	case PlayerState::Idle:
		animFrames = kIdleAnimNum;
		break;
	case PlayerState::AttackPrep:
		animFrames = 1; 
		break;
	case PlayerState::Run:
		animFrames = kRunAnimNum;
		break;
	case PlayerState::Attack:
		animFrames = kAttackAnimNum;
		break;
	case PlayerState::WeakAttack:
		animFrames = kWeakAttackAnimNum;
		break;
	case PlayerState::Hurt:
		animFrames = kHurtAnimNum;
		break;
	}

	// アニメーションフレームを更新
	if (m_animFrame++ >= animFrames * kAnimWaitFrame)
	{
		m_animFrame = 0;
	}
}

// プレイヤーの当たり判定を取得する関数
const Rect& Player::GetCollisionRect() const
{
	return m_colRect;
}

// Hurt状態を返す関数
bool Player::IsHurt() const
{
	return m_state == PlayerState::Hurt;
}

//プレイヤーの攻撃(ノックバック)処理 
void Player::KnockBack()
{
	// 相手プレイヤーがいない、または相手プレイヤーがHurt状態なら何もしない
	if (!m_otherPlayer||m_otherPlayer->IsHurt()) return;

	if (m_colRect.IsCollision(m_otherPlayer->GetCollisionRect()))
	{
		float knockBackValue = knockBackDist;
		// 攻撃の種類によってノックバックの数値を変える
		if (m_attackType == AttackType::Weak)
		{
			knockBackValue *= 0.35f;
		}

		// ノックバックの方向
		if (!m_isTurn)
		{
			m_otherPlayer->m_pos.x += knockBackValue; // 右に吹っ飛ぶ
		}
		else
		{
			m_otherPlayer->m_pos.x -= knockBackValue; // 左に吹っ飛ぶ
		}

		m_otherPlayer->m_hurtCount = 0;
		m_otherPlayer->m_state = PlayerState::Hurt;
		m_otherPlayer->m_attackType = m_attackType;
		m_otherPlayer->m_animFrame = 0;

		m_hasHit = true;
	}
}

bool Player::IsFalling() const
{
	return m_isFalling;
}