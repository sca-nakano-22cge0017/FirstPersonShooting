#include "Target.h"
#include "Screen.h"

Target::Target()
{
	hModel = MV1LoadModel("data/Target/Target.mv1");

	position = VGet(0, 200, 0);
	rotation = VGet(0, 0, 0);
}

Target::~Target()
{
}

void Target::Update()
{
}

void Target::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		MV1DrawModel(hModel);
	}
}