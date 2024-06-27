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

	virtual int GetAtk() { return atk; }
	/// <summary>
	/// 攻撃
	/// </summary>
	/// <param name="atk">攻撃力</param>
	virtual void Attack(int atk) {};

	/// <summary>
	/// // プレイヤーの弾が当たるかどうかを設定・取得
	/// </summary>
	/// <param name="_isHit"></param>
	virtual void CanHitCheck(bool _isHit) {};
	virtual bool CanHitCheck() { return isHit; }

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
	bool isHit;

private:
	VECTOR position;
	VECTOR rotation;
	int atk;
};