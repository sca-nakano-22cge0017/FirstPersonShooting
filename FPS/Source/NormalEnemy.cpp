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
	hp = initHp;
	attacking = false;
	isHit = false;
	
	// ���f��
	hModel = MV1LoadModel(modelFile.c_str());
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	//�A�j���[�V����
	for (int i = 0; i < MAX; i++)
	{
		hAnimation[i] = MV1LoadModel((animationFolder + animationFilename[i] + ".mv1").c_str());
	}
	animation = new Animation();
	animation->SetModel(hModel); //�A�j���[�V������t���郂�f��
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
	animation->Update(); //�A�j���[�V�����̍Đ�
	MV1RefreshCollInfo(hModel); // �R���W�������̍X�V

	gun->SetPosition(position);

	if (CheckHitKey(KEY_INPUT_C))
	{
		Attack();
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

void NormalEnemy::Attack()
{
	animation->Play(hAnimation[A_ATT], true);

	gun->Fire();
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
		position = nearHitPos + heightAdjust; // position��n�ʂɍ��킹��
	}

	objects.clear();
}