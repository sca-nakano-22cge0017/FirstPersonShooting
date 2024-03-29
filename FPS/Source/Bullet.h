#pragma once
#include "../Library/GameObject.h"
#include "Gun.h"

/// <summary>
/// 銃弾
/// </summary>
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 銃弾の生成位置を代入する
	/// </summary>
	/// <param name="pos">生成位置</param>
	void SetPosition(VECTOR pos);

	/// <summary>
	/// 銃弾の生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	void SetRotation(VECTOR rot);

	/// <summary>
	/// 目標物の座標を代入する
	/// </summary>
	/// <param name="target">目標座標</param>
	void SetTarget(VECTOR target);

private:
	int hModel;
	VECTOR position = VGet(0, 0, 0);
	VECTOR rotation = VGet(0, 0, 0);
	float speed = 200.0f / 60;

	VECTOR dir; //移動方向
	VECTOR targetPos = VGet(0, 0, 0);

	Gun* gun;
};