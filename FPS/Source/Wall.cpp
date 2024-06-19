#include "Wall.h"

Wall::Wall()
{
	hModel = MV1LoadModel("data/Objects/BlackBox.mv1");
	position = VGet(100, 200, 0);
	rotation = VGet(0, 0, 0);
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Draw()
{
	if (hModel != -1)
	{
		MV1SetScale(hModel, VGet(50.0f, 300.0f, 500.0f));
		MV1SetPosition(hModel, position);
		MV1SetRotationXYZ(hModel, rotation);
		MV1DrawModel(hModel);
	}
}

bool Wall::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
{
	MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (res.HitFlag) // “–‚½‚Á‚Ä‚¢‚é
	{
		if (hitPos != nullptr)
		{
			*hitPos = res.HitPosition;
		}
		return true;
	}
	return false;
}
