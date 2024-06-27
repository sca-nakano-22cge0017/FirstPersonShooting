#include "../Library/GameObject.h"
#include "../Library/Time.h"
#include "NormalEnemy.h"
#include "NormalEnemyAI.h"
#include "Player.h"
#include "StageObjects.h"

NormalEnemyAI::NormalEnemyAI(NormalEnemy* p)
{
	parent = p;
	rootNode = new Selector(parent);
}

NormalEnemyAI::~NormalEnemyAI()
{
}

void NormalEnemyAI::Update()
{
	rootNode->Update();
}

Node::~Node()
{
	for (Node* c : children) {
		delete c;
	}
	children.clear();
}

bool Node::NeedEnable()
{
	return false;
}

bool Node::Update()
{
	return false;
}

bool EnemyAvoid::NeedEnable()
{
	// �v���C���[�̎ː���ɂ����ꍇ ���� �v���C���[���G�O���ɂ����ꍇ�A���E�ǂ��炩�ɔ�����
	NormalEnemy* eObj = dynamic_cast<NormalEnemy*>(object);

	if (eObj->CanHitCheck())
	{
		
	}

	return false;
}

bool EnemyAvoid::Update()
{
	return false;
}

bool EnemyHide::NeedEnable()
{
	// �v���C���[�̎ː���ɂ����ꍇ�@���@�ǂ��߂��ɂ���ꍇ�͉B���

	// �G�̍��W
	NormalEnemy* eObj = dynamic_cast<NormalEnemy*>(object);
	VECTOR ePos = eObj->GetPosition();

	// �v���C���[�̍��W
	Player* pPl = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pPl->GetPosition();

	if (VSquareSize(ePos - pPos) < 200 * 200)
	{
		//return true;
	}

	return false;
}

bool EnemyHide::Update()
{
	return false;
}

bool EnemyAttack::NeedEnable()
{
	NormalEnemy* pEnemy = dynamic_cast<NormalEnemy*>(object);
	VECTOR ePos = pEnemy->GetPosition();

	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pPlayer->GetPosition();

	VECTOR forward = VGet(0, 0, 1) * MGetRotY(pEnemy->GetRotation().y);
	VECTOR dir = pPos - ePos;
	float targetCos = VDot(VNorm(dir), VNorm(forward));

	// �v���C���[���͈͓��ɂ���@���@�G�̑O���ɂ���
	if (VSquareSize(ePos - pPos) < 1000 * 1000 && targetCos <= -cos(DegToRad(45.0f)))
	{
		return true;
	}

	return false;
}

bool EnemyAttack::Update()
{
	NormalEnemy* pEnemy = dynamic_cast<NormalEnemy*>(object);
	VECTOR ePos = pEnemy->GetPosition();

	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pPlayer->GetPosition();

	VECTOR eRot = pEnemy->GetRotation();
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(eRot.y);
	VECTOR dir = VNorm(pPos - ePos);
	float targetCos = VDot(dir, forward);
	
	if (VSquareSize(ePos - pPos) < 1000 * 1000 && targetCos <= -cos(DegToRad(45.0f)))
	{
		// ���ʂɂ��Ȃ��ꍇ�͉�]
		if (targetCos >= -cos(DegToRad(10.0f)))
		{
			VECTOR right = VGet(1, 0, 0) * MGetRotY(eRot.y);
			float ip = VDot(dir, right);
			if (ip >= 0) pEnemy->RotateY(DegToRad(-1.0f));
			else pEnemy->RotateY(DegToRad(1.0f));
		}
		else pEnemy->Attack();
	}
	else
	{
		// �͈͊O�E����O�ɏo����U����ԉ���
		pEnemy->Idle();
		return true;
	}
}

Selector::Selector(GameObject* obj) : Node(obj)
{
	children.push_back(new EnemyAvoid(obj));
	children.push_back(new EnemyHide(obj));
	children.push_back(new EnemyAttack(obj));
	selected = nullptr;
}

bool Selector::NeedEnable()
{
	for (Node* c : children)
	{
		if (c->NeedEnable())
		{
			selected = c;
			return true;
		}
	}
	selected = nullptr;
	return false;
}

bool Selector::Update()
{
	// ���I��ł�����̂����s���A�I�������true
	if (selected == nullptr || selected->Update()) {
		if (NeedEnable()) {
			return false;
		}
		selected = nullptr;
		return true;
	}
	return false;
}