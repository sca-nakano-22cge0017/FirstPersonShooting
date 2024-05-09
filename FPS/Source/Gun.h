#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "Stage.h"
#include "Enemy.h"

class Gun : public GameObject
{
public:
	Gun();
	~Gun();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 銃の座標を取得する
	/// </summary>
	VECTOR GetPosition() { return position; }

	/// <summary>
	/// 銃の回転角度を取得する
	/// </summary>
	VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// 最大弾数
	/// </summary>
	int GetFullBullets() { return fullBullets; }

	/// <summary>
	/// 残り弾数
	/// </summary>
	int GetRestBullets() { return restBullets; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;

	VECTOR basePos = VGet(0, -25, 50); //基本の座標　プレイヤーが初期位置から移動・回転していない場合の座標

	int fullBullets; //最大弾数
	int restBullets; //残弾数
	bool lastHitKey;
	const float coolTime = 1.0f;
	float elapsedTime;

	float attack = 10; // 攻撃力

	void Fire(); //発砲処理

	/// <summary>
	/// 着弾位置計算
	/// </summary>
	/// <returns>着弾位置</returns>
	VECTOR TargetAcquisition();
	VECTOR reticulePos; // レティクルのワールド座標
	VECTOR targetPos = VGet(0, 0, 0); //弾の目標位置

	VECTOR bulletsCreatePos = VGet(0.0f, 20.0f, 0.0f); //Gunから見て銃弾を生成する座標

	Player* player;

	std::list<Enemy*> enemies; //敵のリスト
};