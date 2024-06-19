#pragma once
#include "../Library/GameObject.h"
#include "Collider.h"

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

	VECTOR SetPosition(VECTOR pos) { position = pos; }

	/// <summary>
	/// �v���C���[�̉�]�p�x���擾����
	/// </summary>
	VECTOR GetRotation() { return rotation; }

	VECTOR SetRotation(VECTOR rot) { rotation = rot; }

	/// <summary>
	/// �v���C���[��]
	/// </summary>
	/// <param name="moveX">X�����̈ړ���</param>
	/// <param name="moveY">Y�����̈ړ���</param>
	void ViewRotate(float moveX, float moveY);

	/// <summary>
	/// �J�����̍��W���擾����
	/// </summary>
	VECTOR GetCameraPos() { return position + cameraPos; }

	int GetHp() { return hp; }

private:
	VECTOR position;
	VECTOR rotation;

	const VECTOR playerHeight = VGet(0, 100, 0);

	const float speed = 5;

	//����
	const float runSpeedTimes = 1.5f; // ���莞�̑��x�㏸�{��

	//�����蔻��
	void CollCheck();

	std::list<Collider*> objects;

	//�W�����v
	const float firstJumpVelocity = 5; //�W�����v�̏���
	float vy; //Y�������̑��x
	bool isGround;
	bool lastJumpKey;
	
	void Jump(); // �W�����v�̏���
	bool isJumping;

	//�J�����̃v���C���[��̍��W
	VECTOR cameraPos = VGet(0, 75, 0);

	//���_�ړ� �������
	const float rotXMin = -0.8f, rotXMax = 0.8f;

	//HP
	int hp;
	// �_���[�W����
	void Damage();

	//�f�o�b�O�p�@���W�\��
	void Debug();
};