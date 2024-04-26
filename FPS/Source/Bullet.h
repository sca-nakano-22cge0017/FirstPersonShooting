#pragma once
#include "../Library/GameObject.h"
#include "Gun.h"

/// <summary>
/// e’e
/// </summary>
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// e’e‚Ì¶¬ˆÊ’u‚ğ‘ã“ü‚·‚é
	/// </summary>
	/// <param name="pos">¶¬ˆÊ’u</param>
	void SetPosition(VECTOR pos);

	/// <summary>
	/// e’e‚Ì¶¬Šp“x‚ğ‘ã“ü‚·‚é
	/// </summary>
	/// <param name="rot">¶¬Šp“x</param>
	void SetRotation(VECTOR rot);

	/// <summary>
	/// –Ú•W•¨‚ÌÀ•W‚ğ‘ã“ü‚·‚é
	/// </summary>
	/// <param name="target">–Ú•WÀ•W</param>
	void SetTarget(VECTOR target);

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	float speed = 200.0f / 60;

	VECTOR dir; //ˆÚ“®•ûŒü
	VECTOR targetPos = VGet(0, 0, 0);

	Gun* gun;
};