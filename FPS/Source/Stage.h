#pragma once
#include "../Library/GameObject.h"
#include "Collider.h"

class Stage : public GameObject, public Collider
{
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	
	//bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) override;

private:
	VECTOR position;
	VECTOR rotation;
};