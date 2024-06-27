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
	// プレイヤーの射線上にいた場合　かつ　壁が近くにある場合は隠れる

	// 敵の座標
	NormalEnemy* eObj = dynamic_cast<NormalEnemy*>(object);
	VECTOR ePos = eObj->GetPosition();

	// プレイヤーの座標
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

	// プレイヤーが範囲内にいる　かつ　敵の前方にいる
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
		// 正面にいない場合は回転
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
		// 範囲外・視野外に出たら攻撃状態解除
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