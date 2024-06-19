#pragma once
#include "../Library/GameObject.h"

class StageCreate : public GameObject
{
public:
	StageCreate();
	~StageCreate();
	void Update() override;
	void Draw() override;
};