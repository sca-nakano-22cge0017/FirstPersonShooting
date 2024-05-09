#include "Warzombie.h"
#include "Screen.h"

Warzombie::Warzombie()
{
	hModel = MV1LoadModel("data/Enemy/Warzombie.mv1");

	position = VGet(0, 50, 0);
	rotation = VGet(0, 0, 0);

	hp = defaultHp;
}

Warzombie::~Warzombie()
{
}

void Warzombie::Update()
{
	if (hp <= 0)
		DestroyMe();
}

void Warzombie::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		MV1DrawModel(hModel);
	}
}

void Warzombie::Damage(int damage)
{
	hp -= damage;
}

bool Warzombie::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
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
