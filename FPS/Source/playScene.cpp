#include "PlayScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"
#include "../Library/Time.h"
#include <DxLib.h>
#include "Screen.h"
#include "Player.h"
#include "Stage.h"
#include "Wall.h"
#include "UI.h"
#include "Gun.h"
#include "Bullet.h"
#include "Warzombie.h"

PlayScene::PlayScene()
{
	Instantiate<Stage>();
	Instantiate<Wall>();
	Instantiate<Player>();
	Instantiate<Warzombie>();
	Instantiate<Gun>();
	Instantiate<UI>();

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));
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
