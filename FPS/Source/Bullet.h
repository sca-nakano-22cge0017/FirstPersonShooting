#pragma once
#include "../Library/GameObject.h"
#include "Gun.h"

/// <summary>
/// �e�e
/// </summary>
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �e�e�̐����ʒu��������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	void SetPosition(VECTOR pos);

	/// <summary>
	/// �e�e�̐����p�x��������
	/// </summary>
	/// <param name="rot">�����p�x</param>
	void SetRotation(VECTOR rot);

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	float speed;

	Gun* gun;
};