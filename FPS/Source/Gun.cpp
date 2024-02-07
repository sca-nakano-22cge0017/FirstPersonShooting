#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>

Gun::Gun()
{
	hModel = MV1LoadModel("data/Gun/Gun.mv1");
	player = ObjectManager::FindGameObject<Player>();
	assert(player != nullptr);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	lastHitKey = false;
	elapsedTime = 0;
	fullBullets = 10;
	restBullets = 10;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	VECTOR playerRot = player->GetRotation();
	VECTOR playerPos = player->GetPosition();
	position = VGet(0, -25, 50) * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(playerPos + VGet(0, 75, 0));
	//���Ƃ̍��W * x����]�s�� * y����]�s�� * �ړ����W(��]�̒��S���W������)

	rotation = VGet(0, playerRot.y + 0.5f * DX_PI, 0);

	//���C
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		if (!lastHitKey)
		{
			lastHitKey = true;
			Fire();
		}
	}
	else lastHitKey = false;
}

void Gun::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);

	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "GunPositionX=%2f", position.x);
	DrawFormatString(Screen::WIDTH - 200, 25, GetColor(255, 0, 0), "GunPositionY=%2f", position.y);
	DrawFormatString(Screen::WIDTH - 200, 50, GetColor(255, 0, 0), "GunPositionZ=%2f", position.z);
}

void Gun::Fire()
{
	//�e�̐���
	Bullet* bullet = Instantiate<Bullet>();

	//�����ʒu�̑��
	VECTOR bulletPos = VGet(23, -2.5f, -11.75f) * MGetRotX(rotation.x) * MGetRotY(rotation.y) * MGetTranslate(position);
	VECTOR bulletRot = VGet(0, rotation.y + DX_PI / 2, 0);

	bullet->SetPosition(bulletPos);
	bullet->SetRotation(bulletRot);
}
