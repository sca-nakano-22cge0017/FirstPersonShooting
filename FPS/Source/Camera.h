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

private:
	VECTOR position;
	VECTOR rotation;
	VECTOR relativePos = VGet(0, 75, 0);

	Player* player;
	VECTOR playerPos;
	VECTOR playerRot;

	//���_�ړ�
	int lastMouseX, lastMouseY;
	const float moveSpeed = 0.005f; //���x
	int mouseX, mouseY;
	// ���_�ړ��̏���
	void ViewPoint();
};