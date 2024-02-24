#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>

/// <summary>
/// �e
/// </summary>
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
	//�J�����𒆐S�ɂ��ďe����]�����A��Ɏ��_���ɏe��\������
	VECTOR playerRot = player->GetRotation();
	VECTOR cameraPos = player->GetCameraPos();
	position = basePos * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(cameraPos);
	//���Ƃ̍��W * x����]�s�� * y����]�s�� * �ړ����W(��]�̒��S���W������)
	
	//������������������悤�ɃJ�����̊p�x�ɉ����ĉ�]����
	rotation = VGet(0, playerRot.y + 0.5f * DX_PI, 0); //�v���C���[�̌����ɑ΂��ăf�t�H���g��90�x��]���Ă�̂Œ���
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	mat = MGetRotY(rotation.y) * MGetRotAxis(right, playerRot.x); //�v���C���[���猩�ĉE�����ւ̃x�N�g������]���ɂ��ĉ�]������

	//���N���b�N�Ŕ��C
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//�������u�ԂȂ�
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
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		//������������������悤�ɃJ�����̊p�x�ɉ����ĉ�]����
		MV1SetRotationMatrix(hModel, mat);

		MV1DrawModel(hModel);
	}
	
	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "GunPositionX=%2f", position.x);
	DrawFormatString(Screen::WIDTH - 200, 25, GetColor(255, 0, 0), "GunPositionY=%2f", position.y);
	DrawFormatString(Screen::WIDTH - 200, 50, GetColor(255, 0, 0), "GunPositionZ=%2f", position.z);
}

void Gun::Fire()
{
	//�e�̐���
	Bullet* bullet = Instantiate<Bullet>();

	//�����ʒu�̑��
	VECTOR bulletPos = bulletsPos * MGetRotX(rotation.x) * MGetRotY(rotation.y) * MGetTranslate(position);
	VECTOR bulletRot = VGet(0, rotation.y + DX_PI / 2, 0);

	bullet->SetPosition(bulletPos);
	bullet->SetRotation(bulletRot);
}
