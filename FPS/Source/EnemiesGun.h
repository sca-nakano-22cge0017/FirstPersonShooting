#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "Gun.h"
#include "Bullet.h"
#include "Stage.h"
class Enemy;

class EnemiesGun : public Gun
{
public:
	EnemiesGun(Enemy* e);
	~EnemiesGun();
	void Update() override;
	void Draw() override;

	VECTOR GetPosition() { return position; }
	void SetPosition(VECTOR pos) override { position = pos; }

	VECTOR GetRotation() { return rotation; }
	void SetRotation(VECTOR rot) override { rotation = rot; }

	/// <summary>
	/// �G���猩���Ƃ��̑��ΓI�ȏe�̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">���Έʒu</param>
	void SetRelativelyPos(VECTOR pos) { relativelyPos = pos; }

	/// <summary>
	/// �G���猩���Ƃ��̑��ΓI�ȏe�̊p�x��ݒ�
	/// </summary>
	/// <param name="pos">���Ίp�x</param>
	void SetRelativelyRot(VECTOR rot) { relativelyRot = rot; }

	void Fire() override;
	
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;

	VECTOR relativelyPos = VGet(0, 0, 0); // �G���猩���Ƃ��̑��Έʒu
	VECTOR relativelyRot = VGet(0, 0, 0); // �G���猩���Ƃ��̑��Ίp�x

	const VECTOR bulletsCreatePos = VGet(0, 0, 0);

	int range = 1000; // �˒�����
	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;

	Player* player;

	// �G
	Enemy* parent;
	VECTOR parentPos;
	VECTOR parentRot;
};