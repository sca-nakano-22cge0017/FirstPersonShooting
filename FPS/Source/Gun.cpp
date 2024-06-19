#include <math.h>
#include <assert.h>
#include <vector>
#include "Gun.h"
#include "Screen.h"
#include "Bullet.h"
#include "Stage.h"
#include "Enemy.h"
#include "Camera.h"
#include "Collider.h"

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

	enemies = ObjectManager::FindGameObjects<Enemy>();
}

Gun::~Gun()
{
}

void Gun::Update()
{
	//カメラを中心にして銃を回転させ、常に視点内に銃を表示する
	VECTOR playerRot = player->GetRotation();

	Camera* cam = ObjectManager::FindGameObject<Camera>();
	VECTOR cameraPos = player->GetPosition() + cam->GetRelativePos();

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

void Gun::Fire()
{
	targetPos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 1.0f));
	reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f));

	//弾の生成
	Bullet* bullet = Instantiate<Bullet>();

	VECTOR hitPos = TargetAcquisition();

	bullet->SetPosition(reticulePos);
	bullet->SetTarget(hitPos);

	// 銃弾モデルの生成位置設定
	VECTOR modelPosition = position + bulletsCreatePos;
	VECTOR modelRotation = VGet(0, rotation.y - DX_PI / 2, 0);

	bullet->SetModelPosition(modelPosition);

	// 銃弾モデルの向き調整
	VECTOR playerRot = player->GetRotation();
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	MATRIX bulletMatrix = MGetRotY(modelRotation.y) * MGetRotAxis(right, playerRot.x);
	bullet->SetModelMatrix(bulletMatrix);
}

// 着弾位置の計算
VECTOR Gun::TargetAcquisition()
{
	VECTOR cameraPos = player->GetCameraPos(); //カメラ座標
	VECTOR playerRot = player->GetRotation(); //プレイヤー回転角度
	
	// レティクルから飛ばされた線分が衝突したものの座標のうち、もっともプレイヤーに近い座標を保存
	VECTOR nearHitPos = targetPos;

	objects = ObjectManager::FindGameObjects<StageObjects>();
	for (StageObjects* o : objects)
	{
		VECTOR hit;
		if (o != nullptr)
		{
			if (o->CollLine(reticulePos, targetPos, &hit))
			{
				if (VSize(position - hit) < VSize(position - nearHitPos))
				{
					nearHitPos = hit;
				}
			}
		}
	}

	// 最も近い敵を保存
	Enemy* nearEnemy = nullptr;

	enemies = ObjectManager::FindGameObjects<Enemy>();
	// もっとも近い位置の敵を取得する
	for (Enemy* e : enemies)
	{
		VECTOR hit;
		if (e != nullptr) {
			if (e->CollLine(reticulePos, targetPos, &hit))
			{
				if (VSize(position - hit) < VSize(position - nearHitPos))
				{
					nearHitPos = hit;
					nearEnemy = e;
				}
			}
		}
	}

	objects.clear();
	enemies.clear();

	return nearHitPos;
}