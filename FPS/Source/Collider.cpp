#include "Collider.h"

bool Collider::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
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
