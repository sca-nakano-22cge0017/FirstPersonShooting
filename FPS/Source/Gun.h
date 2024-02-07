#pragma once
#include "../Library/GameObject.h"
#include "Player.h"

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
	MATRIX mat;

	int fullBullets; //最大弾数
	int restBullets; //残弾数
	bool lastHitKey;
	const float coolTime = 1.0f;
	float elapsedTime;

	void Fire();

	Player* player;
};