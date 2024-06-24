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
	// プレイヤーの射線上にいた場合 かつ プレイヤーが敵前方にいた場合、左右どちらかに避ける
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
	// プレイヤーが一定範囲内にいる場合、隠れる

	// 敵の座標
	NormalEnemy* eObj = dynamic_cast<NormalEnemy*>(object);
	VECTOR ePos = eObj->GetPosition();

	// プレイヤーの座標
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
	// プレイヤーが射程範囲内にいれば射撃する
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
	// childrenを順番に見て、NeedEnableのものがあればtrue
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
	// 今選んでいるものを実行し、終わったらtrue
	if (selected == nullptr || selected->Update()) {
		if (NeedEnable()) {
			return false;
		}
		selected = nullptr;
		return true;
	}
	return false;
}