#include "StageCreate.h"
#include "Stage.h"
#include "Wall.h"
#include "NormalEnemy.h"

//! Todo CSVデータを読み込んでマップ生成

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
