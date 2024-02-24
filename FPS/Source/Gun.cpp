#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>

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
	mat = MGetRotY(rotation.y) * MGetRotAxis(right, playerRot.x); //プレイヤーから見て右方向へのベクトルを回転軸にして回転させる

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
}

void Gun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);

		//同じ部分だけ見えるようにカメラの角度に応じて回転する
		MV1SetRotationMatrix(hModel, mat);

		MV1DrawModel(hModel);
	}
	
	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 0, 0), "GunPositionX=%2f", position.x);
	DrawFormatString(Screen::WIDTH - 200, 25, GetColor(255, 0, 0), "GunPositionY=%2f", position.y);
	DrawFormatString(Screen::WIDTH - 200, 50, GetColor(255, 0, 0), "GunPositionZ=%2f", position.z);
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
}
