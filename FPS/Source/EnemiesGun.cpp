#include "EnemiesGun.h"
#include "Enemy.h"

EnemiesGun::EnemiesGun(Enemy* e)
{
	hModel = MV1LoadModel("data/Objects/BlackBox.mv1");

	player = ObjectManager::FindGameObject<Player>();
	assert(player != nullptr);

	parent = e;
	assert(parent != nullptr);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	parentPos = VGet(0, 0, 0);
	parentRot = VGet(0, 0, 0);
	matrix = MGetIdent();
	relativelyPos = VGet(0, 0, 0);
	relativelyRot = VGet(0, 0, 0);
}

EnemiesGun::~EnemiesGun()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
	}
}

void EnemiesGun::Update()
{
}

void EnemiesGun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);
		MV1SetRotationMatrix(hModel, matrix);
		MV1DrawModel(hModel);
	}
}

void EnemiesGun::Fire()
{
	if (parent == nullptr) return;

	VECTOR target = VGet(0, 0, range) * MGetRotY(parentRot.y);

	VECTOR hitPos = TargetAcquisition(bulletsCreatePos, target);

	Bullet* bullet = new Bullet(this);
	bullet->SetPosition(position + bulletsCreatePos);
	bullet->SetTarget(target);
	bullet->SetModelPosition(position + bulletsCreatePos);
}

VECTOR EnemiesGun::TargetAcquisition(VECTOR start, VECTOR target)
{
	VECTOR nearHitPos = target;

	Collider* nearObj = nullptr;

	std::list<StageObjects*> objects = ObjectManager::FindGameObjects<StageObjects>();

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

	if (player != nullptr)
	{
		VECTOR hit;
		if (player->CollLine(start, target, &hit))
		{
			if (VSquareSize(position - hit) < VSquareSize(position - nearHitPos))
			{
				nearHitPos = hit;
			}
		}
	}

	objects.clear();

	return nearHitPos;
}
