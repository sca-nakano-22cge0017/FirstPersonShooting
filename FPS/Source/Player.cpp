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

	Debug();
}

void Player::Draw()
{
}

void Player::ViewRotate(float moveX, float moveY)
{
	rotation.y += moveX;

	//上下方向への視点移動に制限を掛ける
	if (rotXMin <= rotation.x && rotXMax >= rotation.x)
	{
		rotation.x += moveY;
	}
	else if (rotXMin > rotation.x) rotation.x = rotXMin;
	else if (rotXMax < rotation.x) rotation.x = rotXMax;
}

void Player::CollCheck()
{
	VECTOR nearHitPos = position - VGet(0, -500, 0);
	bool hit = false;

	objects = ObjectManager::FindGameObjects<Collider>();
	for (Collider* o : objects)
	{
		VECTOR groundHit;
		if (o != nullptr)
		{
			if (o->CollLine(position, position + VGet(0, -300, 0), &groundHit))
			{
				if (VSize(position - groundHit) < VSize(position - nearHitPos))
				{
					nearHitPos = groundHit;
					hit = true;
				}
			}
		}
	}

	if (hit)
	{
		if (!isJumping) // ジャンプ中でなければ
			position = nearHitPos + playerHeight; // positionを地面に合わせる

		if (position.y <= nearHitPos.y + playerHeight.y)
		{
			isGround = true;
			isJumping = false;
		}
		else isGround = false;
	}
	else isGround = false;
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