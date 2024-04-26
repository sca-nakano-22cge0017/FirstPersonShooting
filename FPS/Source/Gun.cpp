#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>
#include "Stage.h"
#include <vector>

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
	//���Ƃ̍��W * x����]�s�� * y����]�s�� * �ړ����W(��]�̒��S���W������)
	position = basePos * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(cameraPos);
	
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
}

//VECTOR bulletPosAjust = VGet(12.0f, -13.6f, 32.0f);
VECTOR bulletPosAjust = VGet(0, 0, 0);

void Gun::Fire()
{
	//�e�̐���
	Bullet* bullet = Instantiate<Bullet>();

	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH/2, Screen::HEIGHT/2, 0.998f)); //���e�B�N���̃��[���h���W

	//�����ʒu�̑��
	VECTOR bulletPos = reticulePos;
	VECTOR bulletRot = VGet(0, rotation.y + DX_PI / 2, 0);

	bullet->SetPosition(bulletPos);
	bullet->SetRotation(bulletRot);
	bullet->SetTarget(hitPos);
}

VECTOR Gun::TargetAcquisition()
{
	VECTOR cameraPos = player->GetCameraPos(); //�J�������W
	VECTOR playerRot = player->GetRotation(); //�v���C���[��]�p�x

	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f)); //���e�B�N���̃��[���h���W

	//���e�B�N���̈ʒu����O�������ւ̃x�N�g��
	VECTOR targetVec = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 1.0f));

	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr) {
		VECTOR hit;
		if (pStage->CollLine(reticulePos, targetVec, &hit))
		{
			//���e�B�N���̈ʒu����O���֌����Ẵx�N�g���ɉ����Ԃ�������A�Փˈʒu��Ԃ� -> �W�I�̍��W�Ƃ��Ďg��
			return hit;
		}
		else return targetVec; //���ɂ��Ԃ���Ȃ�������A�O�������ւ̃x�N�g����Ԃ�
	}
}