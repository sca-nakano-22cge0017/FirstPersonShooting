#pragma once
#include "../Library/GameObject.h"
#include "Collider.h"

class StageObjects : public GameObject, public Collider
{
public:
	/// <summary>
	/// �����ʒu��������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	virtual void SetPosition(VECTOR pos) {};

	/// <summary>
	/// �����p�x��������
	/// </summary>
	/// <param name="rot">�����p�x</param>
	virtual void SetRotation(VECTOR rot) {};
};