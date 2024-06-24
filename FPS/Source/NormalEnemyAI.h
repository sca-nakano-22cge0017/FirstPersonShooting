#pragma once
#include <list>
#include "../Library/GameObject.h"
using namespace std;
class NormalEnemy;

class Node {
public:
	Node(GameObject* obj)
	{
		object = obj;
	}

	~Node();

	virtual bool NeedEnable();
	virtual bool Update();

protected:
	list<Node*> children;
	Node* parent = nullptr;
	GameObject* object = nullptr;
};

class NormalEnemyAI {
public:
	NormalEnemyAI(NormalEnemy* p);
	~NormalEnemyAI();
	void Update();
private:
	NormalEnemy* parent;
	Node* rootNode;
};

// îÇØÇÈ
class EnemyAvoid : public Node {
public:
	EnemyAvoid(GameObject* obj) : Node(obj){}
	bool NeedEnable() override;
	bool Update() override;
};

// âBÇÍÇÈ
class EnemyHide : public Node {
public:
	EnemyHide(GameObject* obj) : Node(obj) {}
	bool NeedEnable() override;
	bool Update() override;
};

// çUåÇÇ∑ÇÈ
class EnemyAttack : public Node {
public:
	EnemyAttack(GameObject* obj) : Node(obj) {}
	bool NeedEnable() override;
	bool Update() override;
};

class Selector : public Node {
public:
	Selector(GameObject* obj);
	bool NeedEnable() override;
	bool Update() override;
protected:
	Node* selected = nullptr;
};