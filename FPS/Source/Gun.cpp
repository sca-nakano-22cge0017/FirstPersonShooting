#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>
#include "Stage.h"

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
	matrix = MGetRotY(rotation.y) * MGetRotAxis(right, playerRot.x); //�v���C���[���猩�ĉE�����ւ̃x�N�g������]���ɂ��ĉ�]������

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

	hitPos = TargetAcquisition();
}

void Gun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		//������������������悤�ɃJ�����̊p�x�ɉ����ĉ�]����
		MV1SetRotationMatrix(hModel, matrix);

		MV1DrawModel(hModel);
	}
	
	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "HIT.X=%2f", hitPos.x);
	DrawFormatString(Screen::WIDTH - 200, 25, GetColor(255, 0, 0), "HIT.Y=%2f", hitPos.y);
	DrawFormatString(Screen::WIDTH - 200, 50, GetColor(255, 0, 0), "HIT.Z=%2f", hitPos.z);

	DrawSphere3D(hitPos, 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
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

	bullet->SetTarget(hitPos);
}

VECTOR Gun::TargetAcquisition()
{
	VECTOR cameraPos = player->GetCameraPos();
	VECTOR playerRot = player->GetRotation();

	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f));
	VECTOR targetVec = VGet(0, 0, 1000) * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(reticulePos);

	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr) {
		VECTOR hit;
		if (pStage->CollLine(reticulePos, targetVec, &hit))
		{
			return hit;
		}
		else return targetVec;
	}
}