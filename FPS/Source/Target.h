#pragma once
#include "../Library/GameObject.h"
#include "Player.h"

class Target : public GameObject
{
public:
	Target();
	~Target();
	void Update() override;
	void Draw() override;

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};