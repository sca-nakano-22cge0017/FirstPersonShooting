#pragma once
#include "../Library/GameObject.h"
#include "Enemy.h"
#include "Player.h"
#include "animation.h"
#include "NormalEnemyAI.h"

class NormalEnemy : public GameObject, public Enemy
{
public:
	NormalEnemy();
	~NormalEnemy();
	void Update() override;
	void Draw() override;

	void SetPosition(VECTOR pos) override { position = pos; }
	void SetRotation(VECTOR rot) override { rotation = rot; }
	VECTOR GetPosition() override { return position; }
	VECTOR GetRotation() override { return rotation; }

	void Damage(int damage) override;

	void HitCheck(bool _isHit) override { isHit = _isHit; }
	bool HitCheck() override { return isHit; }

	void GroundCheck() override;

	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) override;

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	VECTOR height = VGet(0, 5, 0);

	int hp;
	const int defaultHp = 100;

	int moveSpeed = 5;

	bool isHit; // ÉvÉåÉCÉÑÅ[ÇÃçUåÇÇ™ìñÇΩÇÈÇ©Ç«Ç§Ç©

	Player* player;
	NormalEnemyAI* ai;

	Animation* animation;
	enum ANIM_ID {
		A_NOTHING = -1,
		A_IDLE = 0,
		A_WALK,
		A_ATT,
		A_TO_CROUCH,
		A_TO_STAND,
		A_DAMAGE,
		A_DEAD,
		A_HEADSHOT_FRONT,
		A_HEADSHOT_BACK,
		MAX
	};
	int hAnimation[MAX];
};