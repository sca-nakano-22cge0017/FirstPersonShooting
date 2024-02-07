#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "Gun.h"

class UI : public GameObject
{
public:
	UI();
	~UI();
	void Update() override;
	void Draw() override;
private:
	Player* player;
	Gun* gun;

	int hp;
	int fullBullets;
	int restBullets;
};