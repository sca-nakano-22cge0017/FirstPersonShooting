#pragma once
#include "Gun.h"
#include "Enemy.h"
#include "StageObjects.h"
class Player;
class Camera;

class PlayersGun : public Gun
{
public:
	PlayersGun(Player* p);
	~PlayersGun();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �ő�e��
	/// </summary>
	int GetFullBullets() { return fullBullets; }

	/// <summary>
	/// �c��e��
	/// </summary>
	int GetRestBullets() { return restBullets; }

	float GetRange() override { return range; }
	void SetRange(float r) override { range = r; }

	void Fire() override;

private:
	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;
	int fullBullets; //�ő�e��
	int restBullets; //�c�e��

	Player* player;
	Camera* camera;
	std::list<StageObjects*> objects; // �X�e�[�W��̃I�u�W�F�N�g/��Q���̃��X�g
	std::list<Enemy*> enemies; // �G�̃��X�g
};