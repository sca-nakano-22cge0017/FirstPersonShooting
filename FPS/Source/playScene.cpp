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
#include "Target.h"

PlayScene::PlayScene()
{
	Instantiate<Stage>();
	Instantiate<Player>();
	Instantiate<Target>();
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
