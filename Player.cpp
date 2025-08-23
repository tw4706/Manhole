#include "Player.h"
#include "SceneMain.h"
#include"Dxlib.h"
#include <vector>
#define _DEBUG

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
	constexpr int kAttackCoolTime = 30;
	constexpr int kWeakAttackCoolTime = 20;
	//強攻撃の準備時間
	constexpr int kAttackPrep = 20;
	// 攻撃を受けた後の無敵時間
	constexpr int kHurtDuration = 30;
	constexpr int kWeakHurtDuration = 15;
	// 当たり判定の半径
	constexpr float kDefaultRadius = 16.0f;
	// プレイヤーの移動速度
	constexpr int  kSpeed = 6;
	// プレイヤーの拡大率
	constexpr float kScale = 2.0f;
	// ノックバックの距離
	constexpr int knockBackDist = 60;
	// 重力
	constexpr float kGravity = 1.5f;
	// 地面の当たり判定
	constexpr int kGround = 400;
	// 同時攻撃と状態遷移の競合を回避するための構造体
	struct PendingHit
	{
		Player* attacker;
		Player* target;
		AttackType type;
	};
	std::vector<PendingHit> pendingHits;

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
	m_state = PlayerState::Idle;
	m_attackType = AttackType::Normal;
}

void Player::End()
{
}

void Player::Update()
{
	// 試しのコード
	if (m_state == PlayerState::Hurt)
	{
		m_hurtCount++;
	}
	if (ShouldTriggerHit()) 
	{
		pendingHits.push_back({ this, m_otherPlayer, m_attackType });
		printfDx("攻撃が追加されました！\n");
	}

	// 全プレイヤーの更新後に攻撃を適用
	for (auto& hit : pendingHits) 
	{
		if (hit.target->CanBeHit()) 
		{
			hit.target->ApplyHit(hit.type,hit.attacker);
		}
	}
	pendingHits.clear();

	// 落下中の処理
	if (m_isFalling)
	{
		printfDx("落ちています!");
		m_fallSpeed += 6.0f * kGravity;
		m_pos.y += m_fallSpeed;

		if (m_pos.x > 750)
		{
			m_isFalling = false;
			m_fallSpeed = 0.0f;
		}
	}
	else
	{
		// 通常の重力処理
		Gravity();

		// 通常の当たり判定
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
	}
	//	コントローラーのボタンの押された状態を取得する
	int input = GetJoypadInputState(m_padType);
	// プレイヤーの状態の更新
	UpdateState(input);
	// プレイヤーのアニメーションの更新
	UpdateAnim();
	// 重力の制限
	if (!m_isFalling&&m_pos.y >= kGround)
	{
		m_pos.y = kGround;
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
		animNum = (m_animFrame / kAnimWaitFrame) % kIdleAnimNum;
		handle = m_handle;
		srcY = 0;
		break;

	case PlayerState::Run:			// 移動中
		animNum = (m_animFrame / kAnimWaitFrame) % kRunAnimNum;
		handle = m_runHandle;
		srcY = 0;
		break;

	case PlayerState::Attack:		// 強攻撃
		animNum = (m_animFrame / kAnimWaitFrame) % kAttackAnimNum;
		handle = m_attackHandle;
		srcY = 0;
		break;

	case PlayerState::WeakAttack:	// 弱攻撃
		animNum = (m_animFrame / kAnimWaitFrame) % kWeakAttackAnimNum;
		handle = m_wAttackHandle;
		srcY = 0;
		break;

	case PlayerState::Hurt:			// 攻撃を受けた状態
		animNum = (m_animFrame / kAnimWaitFrame) % kHurtAnimNum;
		handle = m_hurtHandle;
		srcY = 0;
		break;
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
		m_attackPrepCount++;
		if (m_attackPrepCount >= kAttackPrep)
		{
			m_state = PlayerState::Attack;
			m_attackPrepCount = 0;
			m_attackType = AttackType::Normal;
			printfDx("強攻撃の準備完了!\n");
		}
		break;

	case PlayerState::Run:
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
		// 最初のフレームで攻撃の判定を行う
		if (ShouldTriggerHit()) 
		{
			pendingHits.push_back({ this, m_otherPlayer, AttackType::Normal });
		}

		// 攻撃のカウントがクールタイムを超えたら
		if (m_attackCount > kAttackCoolTime) 
		{
			m_isAttack = false;
			m_attackType = AttackType::Normal;
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			// 攻撃カウントをリセット
			m_attackCount = 0; 
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

		if (ShouldTriggerHit()) 
		{
			pendingHits.push_back({ this, m_otherPlayer, AttackType::Normal });
		}

		if (m_wAttackCount > kWeakAttackCoolTime)
		{
			// クールタイムを超えたら通常状態に戻す
			m_isAttack = false;
			m_attackType = AttackType::Normal;// 攻撃タイプを通常に戻す
			m_state = IsMoving(_input) ? PlayerState::Run : PlayerState::Idle;
			m_wAttackCount = 0;
		}
		break;
	case PlayerState::Hurt:
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
		break;
	}

	// 状態が切り替わったらアニメーションフレームをリセット
	if (saveState != m_state) 
	{
		m_animFrame = 0;
	}
	m_oldInput = _input; // 前回の入力状態を更新
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

// 無敵時間が残っているなら攻撃を受けない
bool Player::CanBeHit() const
{
	if (m_state == PlayerState::Hurt)return true;
	if ((m_attackType == AttackType::Weak && m_hurtCount < kWeakHurtDuration) ||
		(m_attackType == AttackType::Normal && m_hurtCount < kHurtDuration)) 
	{
		return false; // 無敵時間中
	}
	return true;
}

// 攻撃判定を出すべきかを判定する関数
bool Player::ShouldTriggerHit() const
{
	if (m_state == PlayerState::Attack && m_attackCount == 1) return true;
	if (m_state == PlayerState::WeakAttack && m_wAttackCount == 1) return true;

	return false;
}

void Player::ApplyHit(AttackType _type,const Player*_attacker)
{
	if (!CanBeHit()) return;

	float knockBackValue = knockBackDist;
	if (_type == AttackType::Weak)
	{
		knockBackValue *= 0.35f;
	}

	if (_attacker->m_isTurn) 
	{
		m_pos.x += knockBackValue; // 攻撃者が左向き → 相手を右に吹っ飛ばす
		printfDx("ノックバック: 右に %.2f 移動\n", knockBackValue);
	}
	else 
	{
		m_pos.x -= knockBackValue; // 攻撃者が右向き → 相手を左に吹っ飛ばす
		printfDx("ノックバック: 左に %.2f 移動\n", knockBackValue);
	}

	m_state = PlayerState::Hurt;
	m_attackType = _type;
	m_hurtCount = 0;
	m_animFrame = 0;
}

bool Player::IsFalling() const
{
	return m_isFalling;
}


void Player::DisableCollision()
{
	m_colRect.init(-9999, -9999, 0, 0);
}
