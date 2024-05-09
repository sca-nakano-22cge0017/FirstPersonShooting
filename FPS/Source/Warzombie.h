#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Warzombie : public GameObject, public Enemy
{
public:
	Warzombie();
	~Warzombie();
	void Update() override;
	void Draw() override;

	void Damage(int damage) override;

	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) override;

	void SetPosition(VECTOR pos) override { position = pos; }
	void SetRotation(VECTOR rot) override { rotation = rot; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	int hp;
	const int defaultHp = 100;
};