#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>
#include "Stage.h"

/// <summary>
/// 銃
/// </summary>
Gun::Gun()
{
	hModel = MV1LoadModel("data/Gun/Gun.mv1");

	player = ObjectManager::FindGameObject<Player>();
	assert(player != nullptr);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	lastHitKey = false;
	elapsedTime = 0;
	fullBullets = 10;
	restBullets = 10;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	//カメラを中心にして銃を回転させ、常に視点内に銃を表示する
	VECTOR playerRot = player->GetRotation();
	VECTOR cameraPos = player->GetCameraPos();
	position = basePos * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(cameraPos);
	//もとの座標 * x軸回転行列 * y軸回転行列 * 移動座標(回転の中心座標を入れる)
	
	//同じ部分だけ見えるようにカメラの角度に応じて回転する
	rotation = VGet(0, playerRot.y + 0.5f * DX_PI, 0); //プレイヤーの向きに対してデフォルトで90度回転してるので調整
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	matrix = MGetRotY(rotation.y) * MGetRotAxis(right, playerRot.x); //プレイヤーから見て右方向へのベクトルを回転軸にして回転させる

	//左クリックで発砲
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		//押した瞬間なら
		if (!lastHitKey)
		{
			lastHitKey = true;
			Fire();
		}
	}
	else lastHitKey = false;

	hitPos = TargetAcquisition();
}

void Gun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		//同じ部分だけ見えるようにカメラの角度に応じて回転する
		MV1SetRotationMatrix(hModel, matrix);

		MV1DrawModel(hModel);
	}
	
	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "HIT.X=%2f", hitPos.x);
	DrawFormatString(Screen::WIDTH - 200, 25, GetColor(255, 0, 0), "HIT.Y=%2f", hitPos.y);
	DrawFormatString(Screen::WIDTH - 200, 50, GetColor(255, 0, 0), "HIT.Z=%2f", hitPos.z);

	DrawSphere3D(hitPos, 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void Gun::Fire()
{
	//弾の生成
	Bullet* bullet = Instantiate<Bullet>();

	//生成位置の代入
	VECTOR bulletPos = bulletsPos * MGetRotX(rotation.x) * MGetRotY(rotation.y) * MGetTranslate(position);
	VECTOR bulletRot = VGet(0, rotation.y + DX_PI / 2, 0);

	bullet->SetPosition(bulletPos);
	bullet->SetRotation(bulletRot);

	bullet->SetTarget(hitPos);
}

VECTOR Gun::TargetAcquisition()
{
	VECTOR cameraPos = player->GetCameraPos();
	VECTOR playerRot = player->GetRotation();

	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f));
	VECTOR targetVec = VGet(0, 0, 1000) * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(reticulePos);

	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr) {
		VECTOR hit;
		if (pStage->CollLine(reticulePos, targetVec, &hit))
		{
			return hit;
		}
		else return targetVec;
	}
}