#include "Camera.h"
#include "Collider.h"
#include "Enemy.h"
#include "Bullet.h"
#include "PlayersGun.h"

PlayersGun::PlayersGun(Player* p)
{
	hModel = MV1LoadModel("data/Gun/Gun.mv1");

	player = p;
	assert(player != nullptr);

	enemies = ObjectManager::FindGameObjects<Enemy>();

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	relativelyPos = VGet(0.0f, -25.0f, 50.0f);
	bulletsCreatePos = VGet(0.0f, 20.0f, 0.0f);

	fullBullets = 10;
	restBullets = 10;
}

PlayersGun::~PlayersGun()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
	}
}

void PlayersGun::Update()
{
	if (camera == nullptr)
		camera = ObjectManager::FindGameObject<Camera>();

	//カメラを中心にして銃を回転させ、常に視点内に銃を表示する
	VECTOR playerRot = player->GetRotation();
	VECTOR cameraPos = player->GetPosition() + camera->GetRelativePos();

	// プレイヤー位置から見た銃の座標 * x軸回転行列 * y軸回転行列 * 移動座標(回転の中心座標を入れる)
	position = relativelyPos * MGetRotX(playerRot.x) * MGetRotY(playerRot.y) * MGetTranslate(cameraPos);

	//同じ部分だけ見えるようにカメラの角度に応じて回転する
	rotation = VGet(0, playerRot.y + 0.5f * DX_PI, 0); //プレイヤーの向きに対してデフォルトで90度回転してるので調整
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	matrix = MGetRotY(rotation.y) * MGetRotAxis(right, playerRot.x); //プレイヤーから見て右方向へのベクトルを回転軸にして回転させる
}

void PlayersGun::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position);
		//同じ部分だけ見えるようにカメラの角度に応じて回転する
		MV1SetRotationMatrix(hModel, matrix);
		MV1DrawModel(hModel);
	}
}

void PlayersGun::Fire()
{
	float r = range / camera->GetRange();
	VECTOR target = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, r));

	//レティクルのワールド座標
	VECTOR reticulePos = ConvScreenPosToWorldPos(VGet(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0.0f));

	//弾の生成
	Bullet* bullet = new Bullet(this, false, true);

	VECTOR hitPos = TargetAcquisition(reticulePos, target);

	// 銃弾モデルの生成位置設定
	VECTOR modelPosition = position + bulletsCreatePos;
	VECTOR modelRotation = VGet(0, rotation.y - DX_PI / 2, 0);

	// 銃弾モデルの向き調整
	VECTOR playerRot = player->GetRotation();
	VECTOR right = VGet(1, 0, 0) * MGetRotY(playerRot.y);
	MATRIX bulletMatrix = MGetRotY(modelRotation.y) * MGetRotAxis(right, playerRot.x);

	bullet->SetPosition(reticulePos, modelPosition);
	bullet->SetTarget(hitPos);
	bullet->SetModelMatrix(bulletMatrix);
}

VECTOR PlayersGun::TargetAcquisition(VECTOR start, VECTOR target)
{
	// レティクルから飛ばされた線分が衝突したものの座標のうち、もっともプレイヤーに近い座標を保存
	VECTOR nearHitPos = target;

	Collider* nearObj = nullptr;

	objects = ObjectManager::FindGameObjects<StageObjects>();
	for (StageObjects* o : objects)
	{
		VECTOR hit;
		if (o != nullptr)
		{
			if (o->CollLine(start, target, &hit))
			{
				if (VSquareSize(position - hit) < VSquareSize(position - nearHitPos))
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

			e->CanHitCheck(false);

			if (e->CollLine(start, target, &hit))
			{
				if (VSquareSize(position - hit) < VSquareSize(position - nearHitPos))
				{
					nearHitPos = hit;
					nearEnemy = e;
				}
			}
		}
	}

	if (nearEnemy != nullptr)
	{
		// 射程に入っている
		nearEnemy->CanHitCheck(true);
	}

	objects.clear();
	enemies.clear();

	return nearHitPos;
}