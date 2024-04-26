#include "Gun.h"
#include "Screen.h"
#include <math.h>
#include "Bullet.h"
#include <assert.h>
#include "Stage.h"
#include <vector>

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
	//もとの座標 * x軸回転行列 * y軸回転行列 * 移動座標(回転の中心座標を入れる)
	position = basePos * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(cameraPos);
	
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
}

//VECTOR bulletPosAjust = VGet(12.0f, -13.6f, 32.0f);
VECTOR bulletPosAjust = VGet(0, 0, 0);

void Gun::Fire()
{
	//弾の生成
	Bullet* bullet = Instantiate<Bullet>();

	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH/2, Screen::HEIGHT/2, 0.998f)); //レティクルのワールド座標

	//生成位置の代入
	VECTOR bulletPos = reticulePos;
	VECTOR bulletRot = VGet(0, rotation.y + DX_PI / 2, 0);

	bullet->SetPosition(bulletPos);
	bullet->SetRotation(bulletRot);
	bullet->SetTarget(hitPos);
}

VECTOR Gun::TargetAcquisition()
{
	VECTOR cameraPos = player->GetCameraPos(); //カメラ座標
	VECTOR playerRot = player->GetRotation(); //プレイヤー回転角度

	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f)); //レティクルのワールド座標

	//レティクルの位置から前方方向へのベクトル
	VECTOR targetVec = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 1.0f));

	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr) {
		VECTOR hit;
		if (pStage->CollLine(reticulePos, targetVec, &hit))
		{
			//レティクルの位置から前方へ向けてのベクトルに何かぶつかったら、衝突位置を返す -> 標的の座標として使う
			return hit;
		}
		else return targetVec; //何にもぶつからなかったら、前方方向へのベクトルを返す
	}
}