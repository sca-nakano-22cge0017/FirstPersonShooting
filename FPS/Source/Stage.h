#pragma once
#include "../Library/GameObject.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	/// <summary>
	/// 地面との当たり判定
	/// p1とp2を繋ぐ線分に当たったら、hitPosに当たった部分の座標を入れる
	/// </summary>
	/// <param name="p1">点1</param>
	/// <param name="p2">点2</param>
	/// <param name="hitPos">衝突があった場所の座標</param>
	/// <returns>当たったらtrue</returns>
	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos=nullptr);

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};