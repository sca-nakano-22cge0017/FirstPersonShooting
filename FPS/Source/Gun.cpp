#include <math.h>
#include <assert.h>
#include <vector>
#include "Gun.h"
#include "Screen.h"
#include "Bullet.h"
#include "Stage.h"
#include "Enemy.h"
#include "Camera.h"
#include "Collider.h"

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

	enemies = ObjectManager::FindGameObjects<Enemy>();
}

Gun::~Gun()
{
}

void Gun::Update()
{
	//�J�����𒆐S�ɂ��ďe����]�����A��Ɏ��_���ɏe��\������
	VECTOR playerRot = player->GetRotation();

	Camera* cam = ObjectManager::FindGameObject<Camera>();
	VECTOR cameraPos = player->GetPosition() + cam->GetRelativePos();

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

void Gun::Fire()
{
	targetPos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 1.0f));
	reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f));

	//�e�̐���
	Bullet* bullet = Instantiate<Bullet>();

	VECTOR hitPos = TargetAcquisition();

	bullet->SetPosition(reticulePos);
	bullet->SetTarget(hitPos);

	// �e�e���f���̐����ʒu�ݒ�
	VECTOR modelPosition = position + bulletsCreatePos;
	VECTOR modelRotation = VGet(0, rotation.y - DX_PI / 2, 0);

	bullet->SetModelPosition(modelPosition);

	// �e�e���f���̌�������
	VECTOR playerRot = player->GetRotation();
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	MATRIX bulletMatrix = MGetRotY(modelRotation.y) * MGetRotAxis(right, playerRot.x);
	bullet->SetModelMatrix(bulletMatrix);
}

// ���e�ʒu�̌v�Z
VECTOR Gun::TargetAcquisition()
{
	VECTOR cameraPos = player->GetCameraPos(); //�J�������W
	VECTOR playerRot = player->GetRotation(); //�v���C���[��]�p�x
	
	// ���e�B�N�������΂��ꂽ�������Փ˂������̂̍��W�̂����A�����Ƃ��v���C���[�ɋ߂����W��ۑ�
	VECTOR nearHitPos = targetPos;

	objects = ObjectManager::FindGameObjects<StageObjects>();
	for (StageObjects* o : objects)
	{
		VECTOR hit;
		if (o != nullptr)
		{
			if (o->CollLine(reticulePos, targetPos, &hit))
			{
				if (VSize(position - hit) < VSize(position - nearHitPos))
				{
					nearHitPos = hit;
				}
			}
		}
	}

	// �ł��߂��G��ۑ�
	Enemy* nearEnemy = nullptr;

	enemies = ObjectManager::FindGameObjects<Enemy>();
	// �����Ƃ��߂��ʒu�̓G���擾����
	for (Enemy* e : enemies)
	{
		VECTOR hit;
		if (e != nullptr) {
			if (e->CollLine(reticulePos, targetPos, &hit))
			{
				if (VSize(position - hit) < VSize(position - nearHitPos))
				{
					nearHitPos = hit;
					nearEnemy = e;
				}
			}
		}
	}

	objects.clear();
	enemies.clear();

	return nearHitPos;
}