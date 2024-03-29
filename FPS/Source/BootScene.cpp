#include "BootScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"

BootScene::BootScene()
{
	DebugScreen* ds = Instantiate<DebugScreen>();
	ObjectManager::SetDrawOrder(ds, 10000);
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TitleScene"); // 起動が終わったらTitleを表示
}

void BootScene::Draw()
{
}
