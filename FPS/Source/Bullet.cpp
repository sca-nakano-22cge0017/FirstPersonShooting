#include "Bullet.h"
#include "Screen.h"

Bullet::Bullet()
{
	gun = ObjectManager::FindGameObject<Gun>();

	hModel = MV1LoadModel("data/Gun/Bullet.mv1");

	speed = 100.0f / 60;
	isFire = false;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	position += VGet(-1, 0, 0) * speed;

	//DestroyMe(); //�폜
}

void Bullet::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

void Bullet::SetPosition(VECTOR pos)
{
	position = pos;
}

void Bullet::SetRotation(VECTOR rot)
{
	rotation = rot;
}
