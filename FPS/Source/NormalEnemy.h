#pragma once
#include "../Library/GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "animation.h"
#include "NormalEnemyAI.h"
#include "EnemiesGun.h"

class NormalEnemy : public GameObject, public Enemy
{
public:
	NormalEnemy();
	~NormalEnemy();
	void Update() override;
	void Draw() override;

	void SetPosition(VECTOR pos) override { position = pos; }
	void SetRotation(VECTOR rot) override { rotation = rot; }
	VECTOR GetPosition() override { return position; }
	VECTOR GetRotation() override { return rotation; }
	void RotateY(float angle) { rotation.y += angle; }

	void Idle();
	void Attack();

	void Damage(int damage) override;

	// 地面判定
	void GroundCheck() override;

	int GetAtk() override { return atk; }
	// プレイヤーの弾が当たるかどうかを設定・取得
	void CanHitCheck(bool _isHit) override { isHit = _isHit; }
	bool CanHitCheck() override { return isHit; }

private:
	Player* player;
	NormalEnemyAI* ai;

	VECTOR position;
	VECTOR rotation;

	VECTOR heightAdjust = VGet(0, 5, 0); //高さ調整

	string modelFile = "data/Enemy/NormalEnemy_1.mv1";

	// アニメーション
	string animationFolder = "data/Enemy/Animation/";
	string animationFilename[9] =
	{
		"Rifle Idle",
		"Rifle Walk",
		"Firing Rifle",
		"Stand To Crouch",
		"Crouch To Standing With Rifle",
		"Hit Reaction",
		"Dying",
		"Death From Front Headshot",
		"Death From Back Headshot"
	};
	Animation* animation;
	enum ANIM_ID {
		A_NOTHING = -1,
		A_IDLE = 0,
		A_WALK,
		A_ATT,
		A_TO_CROUCH,
		A_TO_STAND,
		A_DAMAGE,
		A_DEAD,
		A_HEADSHOT_FRONT,
		A_HEADSHOT_BACK,
		MAX
	};
	int hAnimation[MAX];
	ANIM_ID nowAnim = A_NOTHING;

	int hp;
	const int initHp = 10; // 初期体力
	int moveSpeed = 5; // 移動速度
	int atk = 5;

	EnemiesGun* gun = nullptr;
	bool attacking; // 攻撃中かどうか
	bool lastAttack;
	const float coolTime = 1.0f;
	float elapsedTime;
	void GunSet();

	bool isHit; // プレイヤーの攻撃が当たるかどうか
};