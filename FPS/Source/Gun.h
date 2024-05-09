#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"

class Gun : public GameObject
{
public:
	Gun();
	~Gun();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �e�̍��W���擾����
	/// </summary>
	VECTOR GetPosition() { return position; }

	/// <summary>
	/// �e�̉�]�p�x���擾����
	/// </summary>
	VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// �ő�e��
	/// </summary>
	int GetFullBullets() { return fullBullets; }

	/// <summary>
	/// �c��e��
	/// </summary>
	int GetRestBullets() { return restBullets; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;

	VECTOR basePos = VGet(0, -25, 50); //��{�̍��W�@�v���C���[�������ʒu����ړ��E��]���Ă��Ȃ��ꍇ�̍��W

	int fullBullets; //�ő�e��
	int restBullets; //�c�e��
	bool lastHitKey;
	const float coolTime = 1.0f;
	float elapsedTime;

	float attack = 10; // �U����

	void Fire(); //���C����

	/// <summary>
	/// ���e�ʒu�v�Z
	/// </summary>
	/// <returns>���e�ʒu</returns>
	VECTOR TargetAcquisition();
	VECTOR reticulePos; // ���e�B�N���̃��[���h���W
	VECTOR targetPos = VGet(0, 0, 0); //�e�̖ڕW�ʒu

	VECTOR bulletsCreatePos = VGet(0.0f, 20.0f, 0.0f); //Gun���猩�ďe�e�𐶐�������W

	Player* player;

	std::list<Enemy*> enemies; //�G�̃��X�g
};