#pragma once
#include "../Library/GameObject.h"
#include "Player.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;

	VECTOR GetPosition() { return position; }
	VECTOR GetRotation() { return rotation; }

	VECTOR GetRelativePos() { return relativePos; }

	float GetRange() { return cameraRange; }

private:
	VECTOR position;
	VECTOR rotation;
	VECTOR relativePos = VGet(0, 75, 0);

	Player* player;
	VECTOR playerPos;
	VECTOR playerRot;

	float cameraRange = 12000.0f;

	//視点移動
	int lastMouseX, lastMouseY;
	const float moveSpeed = 0.005f; //感度
	int mouseX, mouseY;
	// 視点移動の処理
	void ViewPoint();
};