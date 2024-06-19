#pragma once
#include "StageObjects.h"

class Wall : public StageObjects
{
public:
	Wall();
	~Wall();
	void Update() override;
	void Draw() override;

	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) override;

	void SetPosition(VECTOR pos) override { position = pos; }
	void SetRotation(VECTOR rot) override { rotation = rot; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};