#pragma once
#include "../Library/GameObject.h"
#include "Screen.h"
#include "Collider.h"
#include "animation.h"
#include "PlayersGun.h"

/// <summary>
/// プレイヤー
/// </summary>
class Player : public GameObject, public Collider
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// プレイヤーの座標を取得する
	/// </summary>
	VECTOR GetPosition() { return position; }
	VECTOR SetPosition(VECTOR pos) { position = pos; }
	/// <summary>
	/// プレイヤーの回転角度を取得する
	/// </summary>
	VECTOR GetRotation() { return rotation; }
	VECTOR SetRotation(VECTOR rot) { rotation = rot; }
	/// <summary>
	/// カメラの座標を取得する
	/// </summary>
	VECTOR GetCameraPos() { return position + cameraPos; }

	/// <summary>
	/// プレイヤー回転
	/// </summary>
	/// <param name="moveX">X方向の移動量</param>
	/// <param name="moveY">Y方向の移動量</param>
	void ViewRotate(float moveX, float moveY);

	/// <summary>
	/// ダメージ
	/// </summary>
	/// <param name="damage"></param>
	void Damage(int damage) { hp -= damage; }

	int GetHp() { return hp; }

private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR playerHeight = VGet(0, 100, 0);
	const float speed = 5;
	const float runSpeedTimes = 1.5f; // 走り時の速度上昇倍率

	//当たり判定
	void GroundCheck();
	std::list<StageObjects*> objects;

	//ジャンプ
	const float firstJumpVelocity = 5; //ジャンプの初速
	float vy; //Y軸方向の速度
	bool isGround;
	bool lastJumpKey;
	void Jump(); // ジャンプの処理
	bool isJumping;

	//カメラのプレイヤー基準の座標
	VECTOR cameraPos = VGet(0, 75, 0);
	//視点移動 上限下限
	const float rotXMin = -0.8f, rotXMax = 0.8f;

	PlayersGun* gun;

	//HP
	int hp;
	const int InitHp = 100;

	// アニメーション
	Animation* animation;
	enum ANIM_ID {
		A_NOTHING = -1,
		A_IDLE = 0,
		MAX
	};
	int hAnimation[MAX];

	//デバッグ用　座標表示
	void Debug();
};