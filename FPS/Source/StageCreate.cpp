#include "StageCreate.h"
#include "Stage.h"
#include "Wall.h"
#include "NormalEnemy.h"

//! Todo CSV�f�[�^��ǂݍ���Ń}�b�v����

StageCreate::StageCreate()
{
	Instantiate<Stage>();
	Instantiate<NormalEnemy>();
	//Instantiate<Wall>();
}

StageCreate::~StageCreate()
{
}

void StageCreate::Update()
{
}

void StageCreate::Draw()
{
}
