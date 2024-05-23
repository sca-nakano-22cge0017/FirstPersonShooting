#pragma once
#include "StageObjects.h"

class Wall : public StageObjects
{
public:
	Wall();
	~Wall();
	void Update() override;
	void Draw() override;

	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos = nullptr) override;

	/// <summary>
	/// �����ʒu��������
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	void SetPosition(VECTOR pos) override { position = pos; };

	/// <summary>
	/// �����p�x��������
	/// </summary>
	/// <param name="rot">�����p�x</param>
	void SetRotation(VECTOR rot) override { rotation = rot; };

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};