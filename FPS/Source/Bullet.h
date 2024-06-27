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
	/// <summary>
	/// �e�e����
	/// </summary>
	/// <param name="obj">Gun�N���X�̃|�C���^</param>
	/// <param name="_canHitPlayer">�v���C���[�ɓ����邩</param>
	/// <param name="_canHitEnemy">�G�ɓ����邩</param>
	Bullet(Gun* obj, bool _canHitPlayer, bool _canHitEnemy);
	~Bullet();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �e�e�̐����ʒu��������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	void SetPosition(VECTOR pos) { position = pos; }

	/// <summary>
	/// ���f�������ʒu�Ǝ��ۂ̐����ʒu���قȂ�ꍇ
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	/// <param name="modelPos">���f�������ʒu</param>
	void SetPosition(VECTOR pos, VECTOR modelPos)
	{
		position = pos;
		modelPosition = modelPos;
		diff = modelPosition - position;
	}

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
	bool canHitPlayer = false; // �v���C���[�ɓ����邩
	bool canHitEnemy = false;  // �G�ɓ����邩

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
	Player* player;
};