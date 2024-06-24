#include <assert.h>
#include "Bullet.h"
#include "Screen.h"
#include "Stage.h"
#include "Enemy.h"

Bullet::Bullet(Gun* obj)
{
	hModel = MV1LoadModel("data/Gun/Bullet1.mv1");

	gun = obj;
	assert(gun != nullptr);

	isColl = false;
	dis = 0;
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	modelPosition = VGet(0, 0, 0);
	modelRotation = VGet(0, 0, 0);
	matrix = MGetRotX(0) * MGetRotY(0) * MGetRotZ(0);
}

Bullet::~Bullet()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
	}
}

void Bullet::Update()
{
	position += VNorm(dir) * speed;
	dis += speed;
	
	// モデル位置調整
	if (diff.y < 0) diff += VGet(0, 1 / dirSize, 0);
	modelPosition = position + diff;

	CollCheck();

	// 射程距離まで飛んだ　もしくは　何かに衝突したら
	if (dis >= gun->GetRange() || isColl)
	{
		DestroyMe(); //削除
	}
}

void Bullet::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, modelPosition);
		MV1SetRotationMatrix(hModel, matrix);
		MV1DrawModel(hModel);
	}
}

void Bullet::CollCheck()
{
	objects = ObjectManager::FindGameObjects<StageObjects>();
	for (StageObjects* o : objects)
	{
		VECTOR hit;
		if (o != nullptr)
		{
			if (o->CollLine(position, position + VGet(10, 0, 0), &hit))
			{
				isColl = true;
			}
		}
	}

	enemies = ObjectManager::FindGameObjects<Enemy>();
	for (Enemy* e : enemies)
	{
		VECTOR hit;
		if (e != nullptr) {
			if (e->CollLine(position, position + VGet(10, 0, 0), &hit))
			{
				isColl = true;

				// ダメージを与える
				e->Damage(attack);
			}
		}
	}

	objects.clear();
	enemies.clear();
}
