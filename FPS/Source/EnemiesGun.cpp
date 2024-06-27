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
	matrix = MGetIdent();
	scale = VGet(2, 3, 75);

	relativelyPos = VGet(-11, 144, -50);
	relativelyRot = VGet(0, 0, 0);
	bulletsCreatePos = VGet(-3, 0, 25);
	parentPos = VGet(0, 0, 0);
	parentRot = VGet(0, 0, 0);
	
	range = 500.0f;

	MV1SetScale(hModel, scale);
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
	if (parent != nullptr)
	{
		parentPos = parent->GetPosition();
		parentRot = parent->GetRotation();

		position = relativelyPos * MGetRotX(parentRot.x) * MGetRotY(parentRot.y) * MGetTranslate(parentPos);
		rotation = VGet(0, parentRot.y, 0) + relativelyRot;
	}
}

void EnemiesGun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);
		MV1SetRotationXYZ(hModel, rotation);
		MV1DrawModel(hModel);
	}
}

void EnemiesGun::Fire()
{
	if (parent == nullptr) return;

	VECTOR createPos = position + bulletsCreatePos;
	MATRIX matrix = MGetRotY(parentRot.y + 0.4f * DX_PI_F);

	VECTOR startPos = createPos * MGetRotY(parentRot.y + DX_PI_F);
	VECTOR target = VGet(range, createPos.y, bulletsCreatePos.z) * matrix;
	VECTOR hitPos = TargetAcquisition(startPos, target);

	Bullet* bullet = new Bullet(this, true, false);
	bullet->SetPosition(position + bulletsCreatePos);
	bullet->SetTarget(target);
	bullet->SetModelMatrix(MGetRotY(parentRot.y + DX_PI_F));
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