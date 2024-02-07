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
	/// e‚ÌÀ•W‚ğæ“¾‚·‚é
	/// </summary>
	VECTOR GetPosition() { return position; }

	/// <summary>
	/// e‚Ì‰ñ“]Šp“x‚ğæ“¾‚·‚é
	/// </summary>
	VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// Å‘å’e”
	/// </summary>
	int GetFullBullets() { return fullBullets; }

	/// <summary>
	/// c‚è’e”
	/// </summary>
	int GetRestBullets() { return restBullets; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX mat;

	int fullBullets; //Å‘å’e”
	int restBullets; //c’e”
	bool lastHitKey;
	const float coolTime = 1.0f;
	float elapsedTime;

	void Fire();

	Player* player;
};