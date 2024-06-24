#pragma once
#include "StageObjects.h"

class Wall : public StageObjects
{
public:
	Wall();
	~Wall();
	void Update() override;
	void Draw() override;

	void SetPosition(VECTOR pos) override { position = pos; }
	void SetRotation(VECTOR rot) override { rotation = rot; }

	VECTOR GetPosition() override { return position; }
	VECTOR GetRotation() override { return rotation; }

private:
	VECTOR position;
	VECTOR rotation;
};