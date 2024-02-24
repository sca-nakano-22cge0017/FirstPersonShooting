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

private:
	int hModel;
	VECTOR position = VGet(0, 0, 0);
	VECTOR rotation = VGet(0, 0, 0);
	float speed;

	Gun* gun;
};