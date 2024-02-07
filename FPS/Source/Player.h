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

	//����
	const float runSpeed = 2;

	//�����蔻��
	void CollCheck();

	//�W�����v
	const float firstJumpVelocity = 5; //�W�����v�̏���
	float vy; //Y�������̑��x
	bool isGround;
	bool lastJumpKey;
	void Jump();

	//���_�ړ�
	int lastMouseX, lastMouseY;
	const float moveSpeed = 0.005f; //���x
	int mouseX, mouseY;
	void ViewPoint();

	//HP
	int hp;
	void Damage();

	//�f�o�b�O�p�@���W�\��
	void Debug();
};