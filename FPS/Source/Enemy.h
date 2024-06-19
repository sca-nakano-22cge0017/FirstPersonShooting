#pragma once
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
	/// �v���C���[�̎ː���ɂ��邩�i�U���������邩�ǂ����j��ݒ�
	/// </summary>
	/// <param name="_isHit"></param>
	virtual void HitCheck(bool _isHit) {};
	virtual bool HitCheck() { return isHit; }

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

	virtual VECTOR GetPosition() { return position; }
	virtual VECTOR GetRotation() { return rotation; }

	/// <summary>
	/// �ڒn����
	/// </summary>
	virtual void GroundCheck() { };

protected:
	VECTOR position;
	VECTOR rotation;
	bool isHit;
};