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

	/// <summary>
	/// 生成位置を代入する
	/// </summary>
	/// <param name="pos">生成位置</param>
	void SetPosition(VECTOR pos) override { position = pos; };

	/// <summary>
	/// 生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	void SetRotation(VECTOR rot) override { rotation = rot; };

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};