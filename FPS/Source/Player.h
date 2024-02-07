#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Start() override;
	void Update() override;
	void Draw() override;

	VECTOR GetPosition() { return position; }
	VECTOR GetRotation() { return rotation; }

	int GetHp() { return hp; }

private:
	VECTOR position;
	VECTOR rotation;

	//走り
	const float runSpeed = 2;

	//当たり判定
	void CollCheck();

	//ジャンプ
	const float firstJumpVelocity = 5; //ジャンプの初速
	float vy; //Y軸方向の速度
	bool isGround;
	bool lastJumpKey;
	void Jump();

	//視点移動
	int lastMouseX, lastMouseY;
	const float moveSpeed = 0.005f; //感度
	int mouseX, mouseY;
	void ViewPoint();

	//HP
	int hp;
	void Damage();

	//デバッグ用　座標表示
	void Debug();
};