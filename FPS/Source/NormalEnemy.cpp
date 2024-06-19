#include "NormalEnemy.h"

NormalEnemy::NormalEnemy()
{
	hp = defaultHp;

	player = ObjectManager::FindGameObject<Player>();
	ai = new NormalEnemyAI(this);

	hModel = MV1LoadModel("data/Enemy/NormalEnemy_1.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	position = VGet(0, 50, 0);
	rotation = VGet(0, 0, 0);

	//アニメーション
	string folder = "data/Enemy/Animation/";
	string filename[] =
	{
		"Rifle Idle",
		"Rifle Walk",
		"Firing Rifle",
		"Stand To Crouch",
		"Crouch To Standing With Rifle",
		"Hit Reaction",
		"Dying",
		"Death From Front Headshot",
		"Death From Back Headshot"
	};
	for (int i = 0; i < MAX; i++)
	{
		hAnimation[i] = MV1LoadModel((folder + filename[i] + ".mv1").c_str());
	}
	animation = new Animation();
	animation->SetModel(hModel); //アニメーションを付けるモデル
	animation->Play(hAnimation[A_IDLE], true);
}

NormalEnemy::~NormalEnemy()
{
}

void NormalEnemy::Update()
{
	animation->Update(); //アニメーションの再生

	MATRIX rotY = MGetRotY(rotation.y);
	VECTOR move = VGet(0, 0, moveSpeed);
	VECTOR forward = move * rotY;
	VECTOR right = forward * MGetRotY(-0.5 * DX_PI);
	VECTOR left = forward * MGetRotY(0.5 * DX_PI);
	if (CheckHitKey(KEY_INPUT_C))
	{
		position += forward;
	}

	GroundCheck();

	if (hp <= 0)
		DestroyMe();
}

void NormalEnemy::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		MV1DrawModel(hModel);
	}
}

void NormalEnemy::Damage(int damage)
{
	hp -= damage;
}

void NormalEnemy::GroundCheck()
{
	VECTOR nearHitPos = position - VGet(0, -500, 0);
	bool hit = false;

	list<Collider*> objects = ObjectManager::FindGameObjects<Collider>();
	for (Collider* o : objects)
	{
		VECTOR groundHit;
		if (o != nullptr)
		{
			if (o->CollLine(position, position + VGet(0, -300, 0), &groundHit))
			{
				if (VSize(position - groundHit) < VSize(position - nearHitPos))
				{
					nearHitPos = groundHit;
					hit = true;
				}
			}
		}
	}

	if (hit)
	{
		position = nearHitPos + height; // positionを地面に合わせる
	}

	objects.clear();
}

bool NormalEnemy::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
{
	MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (res.HitFlag) // 当たっている
	{
		if (hitPos != nullptr)
		{
			*hitPos = res.HitPosition;
		}
		return true;
	}
	return false;
}
