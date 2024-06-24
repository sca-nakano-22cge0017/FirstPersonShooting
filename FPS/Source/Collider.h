#pragma once

/// <summary>
/// 当たり判定
/// </summary>
class Collider
{
public:

	/// <summary>
	/// p1とp2を繋ぐ線分に当たったら、hitPosに当たった部分の座標を入れる
	/// </summary>
	/// <param name="p1">点1</param>
	/// <param name="p2">点2</param>
	/// <param name="hitPos">衝突があった場所の座標</param>
	/// <returns>当たったらtrue</returns>
	virtual bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr)
	{
		MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
		if (res.HitFlag) // 当たっている
		{
			if (hitPos != nullptr)
			{
				*hitPos = res.HitPosition;
			}
			return true;
		}
		return false;
	}

protected:
	int hModel;
};