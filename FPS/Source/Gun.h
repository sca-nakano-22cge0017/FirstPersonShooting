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
	VECTOR GetPosition() { return position; }
	VECTOR GetRotation() { return rotation; }
	int GetFullBullets() { return fullBullets; }
	int GetRestBullets() { return restBullets; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	int fullBullets; //ç≈ëÂíeêî
	int restBullets; //écíeêî
	bool lastHitKey;
	const float coolTime = 1.0f;
	float elapsedTime;

	void Fire();

	Player* player;
};