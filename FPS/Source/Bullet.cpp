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
	
	//! ”ò‹——£‚É‚æ‚Á‚Ä’²®’l‚ğ•Ï‚¦‚é
	if (diff.y < 0) diff += VGet(0, 0.1f, 0);
	modelPosition = position + diff;

	if (VSize(targetPos - position) < 5)
	{
		DestroyMe(); //íœ
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
