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
	/// 敵から見たときの相対的な銃の位置を設定
	/// </summary>
	/// <param name="pos">相対位置</param>
	void SetRelativelyPos(VECTOR pos) { relativelyPos = pos; }

	/// <summary>
	/// 敵から見たときの相対的な銃の角度を設定
	/// </summary>
	/// <param name="pos">相対角度</param>
	void SetRelativelyRot(VECTOR rot) { relativelyRot = rot; }

	void Fire() override;
	
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;

	VECTOR relativelyPos = VGet(0, 0, 0); // 敵から見たときの相対位置
	VECTOR relativelyRot = VGet(0, 0, 0); // 敵から見たときの相対角度

	const VECTOR bulletsCreatePos = VGet(0, 0, 0);

	int range = 1000; // 射程距離
	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;

	Player* player;

	// 敵
	Enemy* parent;
	VECTOR parentPos;
	VECTOR parentRot;
};