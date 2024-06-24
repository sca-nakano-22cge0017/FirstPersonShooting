#pragma once

/// <summary>
/// �����蔻��
/// </summary>
class Collider
{
public:

	/// <summary>
	/// p1��p2���q�������ɓ���������AhitPos�ɓ������������̍��W������
	/// </summary>
	/// <param name="p1">�_1</param>
	/// <param name="p2">�_2</param>
	/// <param name="hitPos">�Փ˂��������ꏊ�̍��W</param>
	/// <returns>����������true</returns>
	virtual bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr)
	{
		MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
		if (res.HitFlag) // �������Ă���
		{
			if (hitPos != nullptr)
			{
				*hitPos = res.HitPosition;
			}
			return true;
		}
		return false;
	}

protected:
	int hModel;
};