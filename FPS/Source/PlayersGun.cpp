#include "Camera.h"
#include "Collider.h"
#include "Enemy.h"
#include "Bullet.h"
#include "PlayersGun.h"

PlayersGun::PlayersGun(Player* p)
{
	hModel = MV1LoadModel("data/Gun/Gun.mv1");

	player = p;
	assert(player != nullptr);

	enemies = ObjectManager::FindGameObjects<Enemy>();

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	relativelyPos = VGet(0.0f, -25.0f, 50.0f);
	bulletsCreatePos = VGet(0.0f, 20.0f, 0.0f);

	fullBullets = 10;
	restBullets = 10;
}

PlayersGun::~PlayersGun()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
	}
}

void PlayersGun::Update()
{
	if (camera == nullptr)
		camera = ObjectManager::FindGameObject<Camera>();

	//�J�����𒆐S�ɂ��ďe����]�����A��Ɏ��_���ɏe��\������
	VECTOR playerRot = player->GetRotation();
	VECTOR cameraPos = player->GetPosition() + camera->GetRelativePos();

	// �v���C���[�ʒu���猩���e�̍��W * x����]�s�� * y����]�s�� * �ړ����W(��]�̒��S���W������)
	position = relativelyPos * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(cameraPos);

	//������������������悤�ɃJ�����̊p�x�ɉ����ĉ�]����
	rotation = VGet(0, playerRot.y + 0.5f * DX_PI, 0); //�v���C���[�̌����ɑ΂��ăf�t�H���g��90�x��]���Ă�̂Œ���
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	matrix = MGetRotY(rotation.y) * MGetRotAxis(right, playerRot.x); //�v���C���[���猩�ĉE�����ւ̃x�N�g������]���ɂ��ĉ�]������
}

void PlayersGun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);
		//������������������悤�ɃJ�����̊p�x�ɉ����ĉ�]����
		MV1SetRotationMatrix(hModel, matrix);
		MV1DrawModel(hModel);
	}
}

void PlayersGun::Fire()
{
	float r = range / camera->GetRange();
	VECTOR target = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, r));

	//���e�B�N���̃��[���h���W
	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f));

	//�e�̐���
	Bullet* bullet = new Bullet(this, false, true);

	VECTOR hitPos = TargetAcquisition(reticulePos, target);

	// �e�e���f���̐����ʒu�ݒ�
	VECTOR modelPosition = position + bulletsCreatePos;
	VECTOR modelRotation = VGet(0, rotation.y - DX_PI / 2, 0);

	// �e�e���f���̌�������
	VECTOR playerRot = player->GetRotation();
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	MATRIX bulletMatrix = MGetRotY(modelRotation.y) * MGetRotAxis(right, playerRot.x);

	bullet->SetPosition(reticulePos, modelPosition);
	bullet->SetTarget(hitPos);
	bullet->SetModelMatrix(bulletMatrix);
}

VECTOR PlayersGun::TargetAcquisition(VECTOR start, VECTOR target)
{
	// ���e�B�N�������΂��ꂽ�������Փ˂������̂̍��W�̂����A�����Ƃ��v���C���[�ɋ߂����W��ۑ�
	VECTOR nearHitPos = target;

	Collider* nearObj = nullptr;

	objects = ObjectManager::FindGameObjects<StageObjects>();
	for (StageObjects* o : objects)
	{
		VECTOR hit;
		if (o != nullptr)
		{
			if (o->CollLine(start, target, &hit))
			{
				if (VSquareSize(position - hit) < VSquareSize(position - nearHitPos))
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

			e->CanHitCheck(false);

			if (e->CollLine(start, target, &hit))
			{
				if (VSquareSize(position - hit) < VSquareSize(position - nearHitPos))
				{
					nearHitPos = hit;
					nearEnemy = e;
				}
			}
		}
	}

	if (nearEnemy != nullptr)
	{
		// �˒��ɓ����Ă���
		nearEnemy->CanHitCheck(true);
	}

	objects.clear();
	enemies.clear();

	return nearHitPos;
}