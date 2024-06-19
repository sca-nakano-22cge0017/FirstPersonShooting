#pragma once
#include "../Library/GameObject.h"
#include "Collider.h"

class StageObjects : public GameObject, public Collider
{
public:
	virtual void SetPosition(VECTOR pos) {}
	virtual void SetRotation(VECTOR rot) {}
};