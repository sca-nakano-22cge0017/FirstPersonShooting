#include "PlayScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"
#include "../Library/Time.h"
#include <DxLib.h>
#include "Screen.h"
#include "Player.h"
#include "Stage.h"
#include "UI.h"
#include "Gun.h"
#include "Bullet.h"

PlayScene::PlayScene()
{
	Instantiate<Player>();
	Instantiate<Stage>();
	Instantiate<Gun>();
	Instantiate<Bullet>();
	Instantiate<UI>();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void PlayScene::Draw()
{
}
