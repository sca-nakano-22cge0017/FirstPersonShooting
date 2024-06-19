#include "../Library/GameObject.h"
#include "../Library/Time.h"
#include "NormalEnemy.h"
#include "NormalEnemyAI.h"
#include "Player.h"

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
}

Node::~Node()
{
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
	return false;
}

bool EnemyAvoid::Update()
{
	return false;
}

bool EnemyHide::NeedEnable()
{
	return false;
}

bool EnemyHide::Update()
{
	return false;
}

bool EnemyAttack::NeedEnable()
{
	return false;
}

bool EnemyAttack::Update()
{
	return false;
}

bool EnemyApproach::NeedEnable()
{
	return false;
}

bool EnemyApproach::Update()
{
	return false;
}

Selector::Selector(GameObject* obj) : Node(obj)
{
}

bool Selector::NeedEnable()
{
	return false;
}

bool Selector::Update()
{
	return false;
}