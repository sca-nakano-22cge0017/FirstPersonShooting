#include "NormalEnemy.h"

NormalEnemy::NormalEnemy()
{
	hModel = MV1LoadModel("data/Enemy/NormalEnemy_1.mv1");

	position = VGet(0, 50, 0);
	rotation = VGet(0, 0, 0);

	hp = defaultHp;

	player = ObjectManager::FindGameObject<Player>();
	ai = new NormalEnemyAI(this);
}

NormalEnemy::~NormalEnemy()
{
}

void NormalEnemy::Update()
{
	if (hp <= 0)
		DestroyMe();
}

void NormalEnemy::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		MV1DrawModel(hModel);
	}
}

void NormalEnemy::Damage(int damage)
{
	hp -= damage;
}

bool NormalEnemy::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
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
