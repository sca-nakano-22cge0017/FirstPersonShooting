#include "Stage.h"

/// <summary>
/// ステージ
/// </summary>
Stage::Stage()
{
	hModel = MV1LoadModel("data/Stage/Stage00.mv1");
	position = VGet(-600, 0, 0);
	rotation = VGet(0, 1 * DX_PI, 0);
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);
		MV1SetRotationXYZ(hModel, rotation);
		MV1DrawModel(hModel);
	}
}

bool Stage::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
{
	MV1_COLL_RESULT_POLY res =
		MV1CollCheck_Line(hModel, -1, p1, p2);
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
