#pragma once
#include "../Library/GameObject.h"
#include "Gun.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();
	void Update() override;
	void Draw() override;
	void Fire() { isFire = true; }

	void SetPosition(VECTOR pos);
	void SetRotation(VECTOR rot);

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	float speed;
	bool isFire;

	Gun* gun;
};