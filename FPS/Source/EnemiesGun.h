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
	/// 敵から見たときの相対的な銃の位置を設定
	/// </summary>
	/// <param name="pos">相対位置</param>
	void SetRelativelyPos(VECTOR pos) override { relativelyPos = pos; }

	/// <summary>
	/// 敵から見たときの相対的な銃の角度を設定
	/// </summary>
	/// <param name="pos">相対角度</param>
	void SetRelativelyRot(VECTOR rot) override { relativelyRot = rot; }

	float GetRange() override { return range; }
	void SetRange(float r) override { range = r; }

	void Fire() override;
	
private:
	VECTOR scale;

	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;

	Player* player;

	// 敵
	Enemy* parent;
	VECTOR parentPos;
	VECTOR parentRot;
};