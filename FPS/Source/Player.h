#pragma once
#include "../Library/GameObject.h"
#include "Collider.h"

/// <summary>
/// プレイヤー
/// </summary>
class Player : public GameObject
{
public:
	Player();
	~Player();
	void Start() override;
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
	/// プレイヤー回転
	/// </summary>
	/// <param name="moveX">X方向の移動量</param>
	/// <param name="moveY">Y方向の移動量</param>
	void ViewRotate(float moveX, float moveY);

	/// <summary>
	/// カメラの座標を取得する
	/// </summary>
	VECTOR GetCameraPos() { return position + cameraPos; }

	int GetHp() { return hp; }

private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR playerHeight = VGet(0, 100, 0);

	const float speed = 5;

	//走り
	const float runSpeedTimes = 1.5f; // 走り時の速度上昇倍率

	//当たり判定
	void CollCheck();

	std::list<Collider*> objects;

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

	//HP
	int hp;
	// ダメージ処理
	void Damage();

	//デバッグ用　座標表示
	void Debug();
};