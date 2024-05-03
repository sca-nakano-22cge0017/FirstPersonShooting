#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// �v���C���[
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
	/// �v���C���[�̍��W���擾����
	/// </summary>
	VECTOR GetPosition() { return position; }

	/// <summary>
	/// �v���C���[�̉�]�p�x���擾����
	/// </summary>
	VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// �J�����̍��W���擾����
	/// </summary>
	VECTOR GetCameraPos() { return position + cameraPos; }

	int GetHp() { return hp; }

private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR playerHeight = VGet(0, 100, 0);

	//����
	const float runSpeed = 2;

	//�����蔻��
	void CollCheck();

	//�W�����v
	const float firstJumpVelocity = 5; //�W�����v�̏���
	float vy; //Y�������̑��x
	bool isGround;
	bool lastJumpKey;
	// �W�����v�̏���
	void Jump();

	//�J�����̃v���C���[��̍��W
	VECTOR cameraPos = VGet(0, 75, 0);

	//���_�ړ�
	const float rotXMin = -0.8f, rotXMax = 0.8f;
	int lastMouseX, lastMouseY;
	const float moveSpeed = 0.005f; //���x
	int mouseX, mouseY;
	// ���_�ړ��̏���
	void ViewPoint();

	//HP
	int hp;
	// �_���[�W����
	void Damage();

	//�f�o�b�O�p�@���W�\��
	void Debug();
};