#pragma once
#include "../Library/GameObject.h"
#include "Player.h"
#include "Collider.h"

class Enemy : public Collider
{
public:
	/// <summary>
	/// �G�̃_���[�W����
	/// </summary>
	/// <param name="damage">�_���[�W��</param>
	virtual void Damage(int damage) {};

	/// <summary>
	/// �����ʒu��������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	virtual void SetPosition(VECTOR pos) {};

	/// <summary>
	/// �����p�x��������
	/// </summary>
	/// <param name="rot">�����p�x</param>
	virtual void SetRotation(VECTOR rot) {};
};