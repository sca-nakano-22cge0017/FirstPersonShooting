#pragma once
#include "StageObjects.h"

class Stage : public StageObjects
{
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	
	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) override;

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};