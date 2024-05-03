#pragma once
#include "../Library/GameObject.h"

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

	/// <summary>
	/// プレイヤーの回転角度を取得する
	/// </summary>
	VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// カメラの座標を取得する
	/// </summary>
	VECTOR GetCameraPos() { return position + cameraPos; }

	int GetHp() { return hp; }

private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR playerHeight = VGet(0, 100, 0);

	//走り
	const float runSpeed = 2;

	//当たり判定
	void CollCheck();

	//ジャンプ
	const float firstJumpVelocity = 5; //ジャンプの初速
	float vy; //Y軸方向の速度
	bool isGround;
	bool lastJumpKey;
	// ジャンプの処理
	void Jump();

	//カメラのプレイヤー基準の座標
	VECTOR cameraPos = VGet(0, 75, 0);

	//視点移動
	const float rotXMin = -0.8f, rotXMax = 0.8f;
	int lastMouseX, lastMouseY;
	const float moveSpeed = 0.005f; //感度
	int mouseX, mouseY;
	// 視点移動の処理
	void ViewPoint();

	//HP
	int hp;
	// ダメージ処理
	void Damage();

	//デバッグ用　座標表示
	void Debug();
};