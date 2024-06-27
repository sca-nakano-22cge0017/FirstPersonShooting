#include <assert.h>
#include "Bullet.h"
#include "Screen.h"
#include "Stage.h"
#include "Enemy.h"

Bullet::Bullet(Gun* obj, bool _canHitPlayer, bool _canHitEnemy)
{
	hModel = MV1LoadModel("data/Gun/Bullet1.mv1");

	gun = obj;
	assert(gun != nullptr);

	isColl = false;
	dis = 0;
	dirSize = 0;
	dir = VGet(0, 0, 0);
	diff = VGet(0, 0, 0);
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	modelPosition = VGet(0, 0, 0);
	modelRotation = VGet(0, 0, 0);
	matrix = MGetIdent();

	player = ObjectManager::FindGameObject<Player>();

	canHitPlayer = _canHitPlayer;
	canHitEnemy = _canHitEnemy;
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

	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "x= %f\ny= %f\nz= %f", position.x, position.y, position.z);
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
	objects.clear();

	if (canHitEnemy)
	{
		enemies = ObjectManager::FindGameObjects<Enemy>();
		for (Enemy* e : enemies)
		{
			VECTOR hit;
			if (e != nullptr) {
				if (e->CollLine(position, position + VGet(10, 0, 0), &hit))
				{
					isColl = true;
					attack = e->GetAtk();
					e->Damage(attack);
				}
			}
		}
		enemies.clear();
	}
	
	if (canHitPlayer)
	{
		VECTOR hit;
		if (player != nullptr)
		{
			if (player->CollLine(position, position + VGet(10, 0, 0), &hit))
			{
				isColl = true;
				attack = player->GetAtk();
				player->Damage(attack);
			}
		}
	}
}
