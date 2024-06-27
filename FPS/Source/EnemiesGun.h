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

	VECTOR GetPosition() override { return position; }
	void SetPosition(VECTOR pos) override { position = pos; }

	VECTOR GetRotation() override { return rotation; }
	void SetRotation(VECTOR rot) override { rotation = rot; }

	/// <summary>
	/// �G���猩���Ƃ��̑��ΓI�ȏe�̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">���Έʒu</param>
	void SetRelativelyPos(VECTOR pos) override { relativelyPos = pos; }

	/// <summary>
	/// �G���猩���Ƃ��̑��ΓI�ȏe�̊p�x��ݒ�
	/// </summary>
	/// <param name="pos">���Ίp�x</param>
	void SetRelativelyRot(VECTOR rot) override { relativelyRot = rot; }

	float GetRange() override { return range; }
	void SetRange(float r) override { range = r; }

	void Fire() override;
	
private:
	VECTOR scale;

	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;

	Player* player;

	// �G
	Enemy* parent;
	VECTOR parentPos;
	VECTOR parentRot;
};