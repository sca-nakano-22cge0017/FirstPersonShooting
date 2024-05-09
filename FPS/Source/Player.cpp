#include "Player.h"
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "Screen.h"

Player::Player()
{
	position = VGet(0, 200, 0);
	rotation = VGet(0, -0.5f * DX_PI, 0);
	hp = 100;

	isGround = true;
	isJumping = false;
	lastJumpKey = false;
	vy = 0;

	lastMouseX = Screen::WIDTH / 2;
	lastMouseY = Screen::HEIGHT / 2;
	mouseX = mouseY = 0;

	//カメラの表示範囲設定
	SetCameraNearFar(0.1f, 4000.0f);
}

Player::~Player()
{
}

void Player::Start()
{
}

void Player::Update()
{
	MATRIX rotY = MGetRotY(rotation.y);
	VECTOR move;

	//Fキー同時押しで移動速度上昇
	if (CheckHitKey(KEY_INPUT_F)) move = VGet(0, 0, speed) * runSpeedTimes;
	else move = VGet(0, 0, speed);

	VECTOR forward = move * rotY;
	VECTOR right = forward * MGetRotY(-0.5 * DX_PI);
	VECTOR left = forward * MGetRotY(0.5 * DX_PI);

	//WASD移動
	if (CheckHitKey(KEY_INPUT_W))
	{		
		position += forward;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		position -= forward;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		position += right;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		position += left;
	}

	CollCheck();
	Jump();
	ViewPoint();

	Debug();
}

void Player::Draw()
{
}

void Player::CollCheck()
{
	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr) {
		VECTOR groundHit;
		if (pStage->CollLine(position, position + VGet(0, -110, 0), &groundHit))
		{
			if(!isJumping) // ジャンプ中でなければ
				position = groundHit + playerHeight; // positionを地面に合わせる

			if (position.y <= groundHit.y + playerHeight.y)
			{
				isGround = true;
				isJumping = false;
			}
			else isGround = false;
		}
		else isGround = false;
	}
}

const float g = 9.8f; //重力加速度
void Player::Jump()
{
	//接地していたら
	if (isGround)
	{
		//スペースキーを押したら
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			isJumping = true;

			//前フレームで押されている状態じゃなかったら = 押した瞬間だったら
			if (!lastJumpKey)
			{
				//上昇
				vy = firstJumpVelocity;
				position.y += vy;
			}
			lastJumpKey = true;
		}
		else lastJumpKey = false;
	}

	//接地していなかったら
	else
	{
		//自由落下
		vy -= g / 60;
		position.y += vy;
	}
}

void Player::ViewPoint() //視点移動
{
	//マウスの座標を取得
	GetMousePoint(&mouseX, &mouseY);

	//マウスの移動量からカメラの回転角度を算出・設定する
	int moveX = mouseX - lastMouseX;
	int moveY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	rotation.y += moveX * moveSpeed;

	//上下方向への視点移動に制限を掛ける
	if (rotXMin <= rotation.x && rotXMax >= rotation.x)
	{
		rotation.x += moveY * moveSpeed;
	}
	else if (rotXMin > rotation.x) rotation.x = rotXMin;
	else if (rotXMax < rotation.x) rotation.x = rotXMax;

	SetCameraPositionAndAngle(position + cameraPos, rotation.x, rotation.y, 0);
}

void Player::Damage()
{
}

void Player::Debug()
{
	//プレイヤーの座標・角度などを表示
	ImGui::Begin("Player");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &position.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::InputFloat("RotX", &rotation.x);
	ImGui::InputFloat("RotY", &rotation.y);
	ImGui::InputFloat("RotZ", &rotation.z);
	ImGui::End();
}