#pragma once
#include "../Library/GameObject.h"
#include "Collider.h"

class StageObjects : public GameObject, public Collider
{
public:
	/// <summary>
	/// 生成位置を代入する
	/// </summary>
	/// <param name="pos">生成位置</param>
	virtual void SetPosition(VECTOR pos) {};

	/// <summary>
	/// 生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	virtual void SetRotation(VECTOR rot) {};
};