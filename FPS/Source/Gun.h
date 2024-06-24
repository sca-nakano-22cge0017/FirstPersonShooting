#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// �e
/// </summary>
class Gun : public GameObject
{
public:
	virtual VECTOR GetPosition() { return position; }
	virtual void SetPosition(VECTOR pos) {};

	virtual VECTOR GetRotation() { return rotation; }
	virtual void SetRotation(VECTOR rot) {};

	/// <summary>
	/// �˒������擾
	/// </summary>
	/// <returns>�˒�����</returns>
	virtual float GetRange() { return range; }

	/// <summary>
	/// ���C����
	/// </summary>
	virtual void Fire() { };

	/// <summary>
	/// ���e�ʒu�̌v�Z
	/// </summary>
	/// <param name="start">�����ʒu</param>
	/// <param name="target">�ڕW</param>
	/// <returns>���e�ʒu</returns>
	virtual VECTOR TargetAcquisition(VECTOR start, VECTOR target) { return VGet(0, 0, 0); }

protected:
	int hModel = -1;
	VECTOR position = VGet(0, 0, 0);
	VECTOR rotation = VGet(0, 0, 0);
	MATRIX matrix = MGetIdent();

	// �e����������L�����N�^�[���猩�����ΓI�ȍ��W
	VECTOR relativelyPos = VGet(0, 0, 0);
	VECTOR relativelyRot = VGet(0, 0, 0);

	VECTOR targetPos = VGet(0, 0, 0); //�e�̖ڕW�ʒu

	VECTOR bulletsCreatePos = VGet(0.0f, 20.0f, 0.0f); // �e���猩�ďe�e�𐶐�������W

private:
	const float attack = 10; // �U����
	const float range = 1500; // �˒�����
};