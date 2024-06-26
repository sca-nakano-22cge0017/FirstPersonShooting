#pragma once
#include "../Library/GameObject.h"
#include "Gun.h"
#include "StageObjects.h"
#include "Enemy.h"
#include "Player.h"

/// <summary>
/// 銃弾
/// </summary>
class Bullet : public GameObject
{
public:
	/// <summary>
	/// 銃弾生成
	/// </summary>
	/// <param name="obj">Gunクラスのポインタ</param>
	/// <param name="_canHitPlayer">プレイヤーに当たるか</param>
	/// <param name="_canHitEnemy">敵に当たるか</param>
	Bullet(Gun* obj, bool _canHitPlayer, bool _canHitEnemy);
	~Bullet();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 銃弾の生成位置を代入する
	/// </summary>
	/// <param name="pos">生成位置</param>
	void SetPosition(VECTOR pos) { position = pos; }

	/// <summary>
	/// モデル生成位置と実際の生成位置が異なる場合
	/// </summary>
	/// <param name="pos">生成位置</param>
	/// <param name="modelPos">モデル生成位置</param>
	void SetPosition(VECTOR pos, VECTOR modelPos)
	{
		position = pos;
		modelPosition = modelPos;
		diff = modelPosition - position;
	}

	/// <summary>
	/// 銃弾の生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	void SetRotation(VECTOR rot) { rotation = rot; }

	/// <summary>
	/// 目標物の座標を代入する
	/// </summary>
	/// <param name="target">目標座標</param>
	void SetTarget(VECTOR target)
	{
		targetPos = target;
		dir = targetPos - position;
		dirSize = VSize(targetPos - modelPosition);
	}

	/// <summary>
	/// 銃弾モデルの生成角度を代入する
	/// </summary>
	/// <param name="rot">生成角度</param>
	void SetModelMatrix(MATRIX mat) { matrix = mat; }

private:
	int hModel;
	VECTOR position;
	VECTOR rotation;

	float speed = 1000.0f / 60;

	float attack = 10; // 攻撃力

	/// <summary>
	/// 衝突判定
	/// </summary>
	void CollCheck();
	bool isColl;
	bool canHitPlayer = false; // プレイヤーに当たるか
	bool canHitEnemy = false;  // 敵に当たるか

	VECTOR dir; //移動方向
	VECTOR targetPos = VGet(0, 0, 0);

	VECTOR diff; // 実際の座標とモデルが表示される座標の差
	VECTOR modelPosition;
	VECTOR modelRotation;
	MATRIX matrix;

	float dis; // 飛行距離

	float dirSize;

	Gun* gun;

	std::list<StageObjects*> objects; // ステージ上のオブジェクト/障害物のリスト
	std::list<Enemy*> enemies; // 敵のリスト
	Player* player;
};