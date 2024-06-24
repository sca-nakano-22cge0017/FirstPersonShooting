#include "PlayScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"
#include "../Library/Time.h"
#include <DxLib.h>
#include "Screen.h"
#include "Player.h"
#include "Camera.h"
#include "StageCreate.h"
#include "SkyDoom.h"
#include "UI.h"
#include "Bullet.h"

PlayScene::PlayScene()
{
	Instantiate<Player>();
	Instantiate<StageCreate>();
	Instantiate<SkyDoom>();
	
	Camera* cam = Instantiate<Camera>();
	cam->SetDrawOrder(100); // ï`âÊèáïœçX

	UI* ui = Instantiate<UI>();
	ui->SetDrawOrder(500);

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
