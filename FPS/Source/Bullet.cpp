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
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	position += VNorm(dir) * speed;
	
	// ÉÇÉfÉãà íuí≤êÆ
	if (diff.y < 0) diff += VGet(0, 1 / dirSize, 0);
	modelPosition = position + diff;

	if (VSize(targetPos - position) < 5)
	{
		DestroyMe(); //çÌèú
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
