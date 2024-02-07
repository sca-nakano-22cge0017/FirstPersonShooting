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

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	float speed;

	Gun* gun;
};