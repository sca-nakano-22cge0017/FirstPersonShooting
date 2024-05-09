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
	void SetPosition(VECTOR pos) { position = pos; }

	/// <summary>
	/// �e�e�̐����p�x��������
	/// </summary>
	/// <param name="rot">�����p�x</param>
	void SetRotation(VECTOR rot) { rotation = rot; }

	/// <summary>
	/// �ڕW���̍��W��������
	/// </summary>
	/// <param name="target">�ڕW���W</param>
	void SetTarget(VECTOR target)
	{
		targetPos = target;
		dir = targetPos - position;
		modelDir = targetPos - modelPosition;
	}

	/// <summary>
	/// �e�e���f���̐����ʒu��������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	void SetModelPosition(VECTOR pos)
	{
		modelPosition = pos;
		diff = modelPosition - position;
	}

	/// <summary>
	/// �e�e���f���̐����p�x��������
	/// </summary>
	/// <param name="pos">�����p�x</param>
	void SetModelRotation(VECTOR rot) { modelRotation = rot; }

	/// <summary>
	/// �e�e���f���̐����p�x��������
	/// </summary>
	/// <param name="rot">�����p�x</param>
	void SetModelMatrix(MATRIX mat) { matrix = mat; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	float speed = 600.0f / 60;

	VECTOR dir; //�ړ�����
	VECTOR targetPos = VGet(0, 0, 0);

	VECTOR diff; // ���ۂ̍��W�ƃ��f�����\���������W�̍�
	VECTOR modelPosition;
	VECTOR modelRotation;
	MATRIX matrix;
	VECTOR modelDir;

	Gun* gun;
};