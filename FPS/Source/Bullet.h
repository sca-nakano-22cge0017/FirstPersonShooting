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
	void SetPosition(VECTOR pos) { position = pos; }

	/// <summary>
	/// 銃弾の生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	void SetRotation(VECTOR rot) { rotation = rot; }

	/// <summary>
	/// 目標物の座標を代入する
	/// </summary>
	/// <param name="target">目標座標</param>
	void SetTarget(VECTOR target)
	{
		targetPos = target;
		dir = targetPos - position;
		modelDir = targetPos - modelPosition;
	}

	/// <summary>
	/// 銃弾モデルの生成位置を代入する
	/// </summary>
	/// <param name="pos">生成位置</param>
	void SetModelPosition(VECTOR pos)
	{
		modelPosition = pos;
		diff = modelPosition - position;
	}

	/// <summary>
	/// 銃弾モデルの生成角度を代入する
	/// </summary>
	/// <param name="pos">生成角度</param>
	void SetModelRotation(VECTOR rot) { modelRotation = rot; }

	/// <summary>
	/// 銃弾モデルの生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	void SetModelMatrix(MATRIX mat) { matrix = mat; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	float speed = 600.0f / 60;

	VECTOR dir; //移動方向
	VECTOR targetPos = VGet(0, 0, 0);

	VECTOR diff; // 実際の座標とモデルが表示される座標の差
	VECTOR modelPosition;
	VECTOR modelRotation;
	MATRIX matrix;
	VECTOR modelDir;

	Gun* gun;
};