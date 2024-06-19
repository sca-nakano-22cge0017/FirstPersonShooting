#include <assert.h>
#include "Bullet.h"
#include "Screen.h"
#include "Stage.h"
#include "Enemy.h"

Bullet::Bullet()
{
	gun = ObjectManager::FindGameObject<Gun>();
	assert(gun != nullptr);

	hModel = MV1LoadModel("data/Gun/Bullet1.mv1");

	isColl = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	position += VNorm(dir) * speed;
	
	// モデル位置調整
	if (diff.y < 0) diff += VGet(0, 1 / dirSize, 0);
	modelPosition = position + diff;

	CollCheck();

	if (VSize(targetPos - position) < 5 || isColl)
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

	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "x= %f, \ny= %f, \nz= %f", position.x, position.y, position.z);
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
