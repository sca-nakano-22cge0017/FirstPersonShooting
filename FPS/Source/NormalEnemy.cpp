#include "NormalEnemy.h"

NormalEnemy::NormalEnemy()
{
	player = ObjectManager::FindGameObject<Player>();
	ai = new NormalEnemyAI(this);
	assert(ai != nullptr);
	gun = new EnemiesGun(this);
	assert(gun != nullptr);

	position = VGet(300, 75, 300);
	rotation = VGet(0, 0, 0);
	lastAttack = false;
	elapsedTime = coolTime;
	hp = initHp;
	attacking = false;
	isHit = false;
	
	// モデル
	hModel = MV1LoadModel(modelFile.c_str());
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	//アニメーション
	for (int i = 0; i < MAX; i++)
	{
		hAnimation[i] = MV1LoadModel((animationFolder + animationFilename[i] + ".mv1").c_str());
	}
	animation = new Animation();
	animation->SetModel(hModel); //アニメーションを付けるモデル
	animation->Play(hAnimation[A_IDLE], true);
}

NormalEnemy::~NormalEnemy()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
	}
}

void NormalEnemy::Update()
{
	ai->Update();
	animation->Update(); //アニメーションの再生
	MV1RefreshCollInfo(hModel); // コリジョン情報の更新

	GroundCheck();

	if (hp <= 0) DestroyMe();
}

void NormalEnemy::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);
		MV1SetRotationXYZ(hModel, rotation);
		MV1DrawModel(hModel);
	}
}

void NormalEnemy::Idle()
{
	animation->Play(hAnimation[A_IDLE], true);
}

void NormalEnemy::Attack()
{
	elapsedTime += 1.0f / 60.0f;

	if (elapsedTime >= coolTime)
	{
		if (!lastAttack)
		{
			//! プレイヤーの方を向く
			//! 銃弾の生成タイミング調整

			lastAttack = true;
			animation->Play(hAnimation[A_ATT], true);
			gun->Fire();
			elapsedTime = 0;
		}
		else lastAttack = false;
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
		position = nearHitPos + heightAdjust; // positionを地面に合わせる
	}

	objects.clear();
}

void NormalEnemy::GunSet()
{
	// アニメーションに応じて銃の位置を調整

	VECTOR pos = VGet(0, 0, 0);
	VECTOR rot = VGet(0, 0, 0);

	switch (nowAnim)
	{
	case A_IDLE:
		break;
	case A_WALK:
		break;
	case A_ATT:
		break;
	case A_TO_CROUCH:
		break;
	case A_TO_STAND:
		break;
	case A_DAMAGE:
		break;
	case A_DEAD:
		break;
	case A_HEADSHOT_FRONT:
		break;
	case A_HEADSHOT_BACK:
		break;
	default:
		break;
	}

	if (gun != nullptr)
	{
		gun->SetRelativelyPos(pos);
		gun->SetRelativelyRot(rot);
	}
}