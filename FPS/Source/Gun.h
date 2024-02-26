#pragma once
#include "../Library/GameObject.h"
#include "Player.h"

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

	void Fire(); //���C����
	VECTOR TargetAcquisition(); //�W�I�ߑ�
	VECTOR hitPos = VGet(0, 0, 0); //�W�I�̈ʒu

	VECTOR bulletsPos = VGet(23, -2.5f, -11.75f); //Gun���猩�ďe�e�𐶐�������W

	Player* player;
};