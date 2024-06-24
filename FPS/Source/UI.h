#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "PlayersGun.h"

class UI : public GameObject
{
public:
	UI();
	~UI();
	void Update() override;
	void Draw() override;
private:
	Player* player;
	PlayersGun* gun;

	int hp;
	int fullBullets;
	int restBullets;
};