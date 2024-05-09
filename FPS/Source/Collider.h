#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// 当たり判定　継承する
/// </summary>
class Collider
{
public:

	/// <summary>
	/// 地面との当たり判定
	/// p1とp2を繋ぐ線分に当たったら、hitPosに当たった部分の座標を入れる
	/// </summary>
	/// <param name="p1">点1</param>
	/// <param name="p2">点2</param>
	/// <param name="hitPos">衝突があった場所の座標</param>
	/// <returns>当たったらtrue</returns>
	virtual bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) { return false; };
};