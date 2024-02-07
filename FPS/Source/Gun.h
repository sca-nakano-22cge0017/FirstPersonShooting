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
	MATRIX mat;

	int fullBullets; //�ő�e��
	int restBullets; //�c�e��
	bool lastHitKey;
	const float coolTime = 1.0f;
	float elapsedTime;

	void Fire();

	Player* player;
};