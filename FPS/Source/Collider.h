#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// �����蔻��@�p������
/// </summary>
class Collider
{
public:
	int hModel;

	/// <summary>
	/// �n�ʂƂ̓����蔻��
	/// p1��p2���q�������ɓ���������AhitPos�ɓ������������̍��W������
	/// </summary>
	/// <param name="p1">�_1</param>
	/// <param name="p2">�_2</param>
	/// <param name="hitPos">�Փ˂��������ꏊ�̍��W</param>
	/// <returns>����������true</returns>
	virtual bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr);

	// Bullet.cpp�őS�I�u�W�F�N�g��CollLine���m�F������
	// ����������A�ł��������߂����̂̍��W���擾����
};