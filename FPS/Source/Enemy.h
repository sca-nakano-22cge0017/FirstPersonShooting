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

	virtual int GetAtk() { return atk; }
	/// <summary>
	/// �U��
	/// </summary>
	/// <param name="atk">�U����</param>
	virtual void Attack(int atk) {};

	/// <summary>
	/// // �v���C���[�̒e�������邩�ǂ�����ݒ�E�擾
	/// </summary>
	/// <param name="_isHit"></param>
	virtual void CanHitCheck(bool _isHit) {};
	virtual bool CanHitCheck() { return isHit; }

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
	bool isHit;

private:
	VECTOR position;
	VECTOR rotation;
	int atk;
};