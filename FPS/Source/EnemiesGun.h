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
	/// “G‚©‚çŒ©‚½‚Æ‚«‚Ì‘Š‘Î“I‚Èe‚ÌˆÊ’u‚ğİ’è
	/// </summary>
	/// <param name="pos">‘Š‘ÎˆÊ’u</param>
	void SetRelativelyPos(VECTOR pos) { relativelyPos = pos; }

	/// <summary>
	/// “G‚©‚çŒ©‚½‚Æ‚«‚Ì‘Š‘Î“I‚Èe‚ÌŠp“x‚ğİ’è
	/// </summary>
	/// <param name="pos">‘Š‘ÎŠp“x</param>
	void SetRelativelyRot(VECTOR rot) { relativelyRot = rot; }

	void Fire() override;
	
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;

	VECTOR relativelyPos = VGet(0, 0, 0); // “G‚©‚çŒ©‚½‚Æ‚«‚Ì‘Š‘ÎˆÊ’u
	VECTOR relativelyRot = VGet(0, 0, 0); // “G‚©‚çŒ©‚½‚Æ‚«‚Ì‘Š‘ÎŠp“x

	const VECTOR bulletsCreatePos = VGet(0, 0, 0);

	int range = 1000; // Ë’ö‹——£
	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;

	Player* player;

	// “G
	Enemy* parent;
	VECTOR parentPos;
	VECTOR parentRot;
};