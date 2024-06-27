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
	/// 最大弾数
	/// </summary>
	int GetFullBullets() { return fullBullets; }

	/// <summary>
	/// 残り弾数
	/// </summary>
	int GetRestBullets() { return restBullets; }

	float GetRange() override { return range; }
	void SetRange(float r) override { range = r; }

	void Fire() override;

private:
	VECTOR TargetAcquisition(VECTOR start, VECTOR target) override;
	int fullBullets; //最大弾数
	int restBullets; //残弾数

	Player* player;
	Camera* camera;
	std::list<StageObjects*> objects; // ステージ上のオブジェクト/障害物のリスト
	std::list<Enemy*> enemies; // 敵のリスト
};