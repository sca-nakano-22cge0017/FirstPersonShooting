#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// 銃
/// </summary>
class Gun : public GameObject
{
public:
	virtual VECTOR GetPosition() { return position; }
	virtual void SetPosition(VECTOR pos) {};

	virtual VECTOR GetRotation() { return rotation; }
	virtual void SetRotation(VECTOR rot) {};

	/// <summary>
	/// 射程距離取得
	/// </summary>
	/// <returns>射程距離</returns>
	virtual float GetRange() { return range; }

	/// <summary>
	/// 発砲処理
	/// </summary>
	virtual void Fire() { };

	/// <summary>
	/// 着弾位置の計算
	/// </summary>
	/// <param name="start">生成位置</param>
	/// <param name="target">目標</param>
	/// <returns>着弾位置</returns>
	virtual VECTOR TargetAcquisition(VECTOR start, VECTOR target) { return VGet(0, 0, 0); }

protected:
	int hModel = -1;
	VECTOR position = VGet(0, 0, 0);
	VECTOR rotation = VGet(0, 0, 0);
	MATRIX matrix = MGetIdent();

	// 銃を所持するキャラクターから見た相対的な座標
	VECTOR relativelyPos = VGet(0, 0, 0);
	VECTOR relativelyRot = VGet(0, 0, 0);

	VECTOR targetPos = VGet(0, 0, 0); //弾の目標位置

	VECTOR bulletsCreatePos = VGet(0.0f, 20.0f, 0.0f); // 銃から見て銃弾を生成する座標

private:
	const float attack = 10; // 攻撃力
	const float range = 1500; // 射程距離
};