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
	// �v���C���[�����͈͓��ɂ���ꍇ�A�B���

	// �G�̍��W
	NormalEnemy* eObj = dynamic_cast<NormalEnemy*>(object);
	VECTOR ePos = eObj->GetPosition();

	// �v���C���[�̍��W
	Player* pPl = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pPl->GetPosition();

	if (VSquareSize(ePos - pPos) < 200 * 200)
	{
		return true;
	}

	return false;
}

bool EnemyHide::Update()
{
	return false;
}

bool EnemyAttack::NeedEnable()
{
	// �v���C���[���˒��͈͓��ɂ���Ύˌ�����
	return false;
}

bool EnemyAttack::Update()
{
	return false;
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
	// children�����ԂɌ��āANeedEnable�̂��̂������true
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