#pragma once
#include "Collider.h"

class Enemy : public Collider
{
public:
	/// <summary>
	/// 敵のダメージ処理
	/// </summary>
	/// <param name="damage">ダメージ量</param>
	virtual void Damage(int damage) {};

	/// <summary>
	/// プレイヤーの射線上にいるか（攻撃が当たるかどうか）を設定
	/// </summary>
	/// <param name="_isHit"></param>
	virtual void HitCheck(bool _isHit) {};
	virtual bool HitCheck() { return isHit; }

	/// <summary>
	/// 生成位置を代入する
	/// </summary>
	/// <param name="pos">生成位置</param>
	virtual void SetPosition(VECTOR pos) {};

	/// <summary>
	/// 生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	virtual void SetRotation(VECTOR rot) {};

	virtual VECTOR GetPosition() { return position; }
	virtual VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// 接地判定
	/// </summary>
	virtual void GroundCheck() { };

protected:
	VECTOR position;
	VECTOR rotation;
	bool isHit;
};