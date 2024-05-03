#include "Bullet.h"
#include "Screen.h"
#include <assert.h>

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
	
	if (diff.y < 0) diff += VGet(0, 0.1f, 0);
	modelPosition = position + diff;

	if (abs(VSize(targetPos - position)) < 5)
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

void Bullet::SetPosition(VECTOR pos)
{
	position = pos;
}

void Bullet::SetRotation(VECTOR rot)
{
	rotation = rot;
}

void Bullet::SetTarget(VECTOR target)
{
	targetPos = target;
	dir = targetPos - position;
	modelDir = targetPos - modelPosition;
}

void Bullet::SetModelPosition(VECTOR pos)
{
	modelPosition = pos;

	diff = modelPosition - position;
}

void Bullet::SetModelRotation(VECTOR rot)
{
	modelRotation = rot;
}

void Bullet::SetModelMatrix(MATRIX mat)
{
	matrix = mat;
}
