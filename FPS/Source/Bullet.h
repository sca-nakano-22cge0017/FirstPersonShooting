#pragma once
#include "../Library/GameObject.h"
#include "Gun.h"
#include "StageObjects.h"
#include "Enemy.h"
#include "Player.h"

/// <summary>
/// �e�e
/// </summary>
class Bullet : public GameObject
{
public:
	Bullet(Gun* obj);
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
		dirSize = VSize(targetPos - modelPosition);
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

	float speed = 1000.0f / 60;

	float attack = 10; // �U����

	/// <summary>
	/// �Փ˔���
	/// </summary>
	void CollCheck();
	bool isColl;

	VECTOR dir; //�ړ�����
	VECTOR targetPos = VGet(0, 0, 0);

	VECTOR diff; // ���ۂ̍��W�ƃ��f�����\���������W�̍�
	VECTOR modelPosition;
	VECTOR modelRotation;
	MATRIX matrix;

	float dis; // ��s����

	float dirSize;

	Gun* gun;

	std::list<StageObjects*> objects; // �X�e�[�W��̃I�u�W�F�N�g/��Q���̃��X�g
	std::list<Enemy*> enemies; // �G�̃��X�g
};