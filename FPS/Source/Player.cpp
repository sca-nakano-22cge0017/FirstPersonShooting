#include "Player.h"
#include "Stage.h"
#include "Gun.h"
#include "Bullet.h"
#include "../ImGui/imgui.h"
#include <cstdlib>
#include <cmath>
#include "Screen.h"

Player::Player()
{
	position = VGet(0, 200, 0);
	rotation = VGet(0, -0.5f * DX_PI, 0);
	hp = 100;

	isGround = true;
	lastJumpKey = false;
	vy = 0;

	lastMouseX = Screen::WIDTH / 2;
	lastMouseY = Screen::HEIGHT / 2;
	mouseX = mouseY = 0;

	//カメラの表示範囲設定
	SetCameraNearFar(0.1f, 2000.0f);
}

Player::~Player()
{
}

void Player::Start()
{
}

float hitPos = 0;
void Player::Update()
{
	MATRIX rotY = MGetRotY(rotation.y);
	VECTOR move;
	if (CheckHitKey(KEY_INPUT_F)) move = VGet(0, 0, 2) * runSpeed; //走り
	else move = VGet(0, 0, 2);
	VECTOR forward = move * rotY;
	VECTOR right = forward * MGetRotY(-0.5 * DX_PI);
	VECTOR left = forward * MGetRotY(0.5 * DX_PI);

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
		if (pStage->CollLine(position + VGet(0, 100, 0), position + VGet(0, -500, 0), &groundHit))
		{
			hitPos = groundHit.y;
			if (position.y <= groundHit.y)
			{
				isGround = true;
			}
			else isGround = false;
		}
	}
}

const float g = 9.8f; //重力加速度
void Player::Jump()
{
	if (isGround)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			if (!lastJumpKey)
			{
				vy = firstJumpVelocity;
				position.y += vy;
			}
			lastJumpKey = true;
		}
		else lastJumpKey = false;
	}
	
	if (!isGround)
	{
		vy -= g / 60;
		position.y += vy;
	}
}

void Player::ViewPoint() //視点移動
{
	GetMousePoint(&mouseX, &mouseY);

	int moveX = mouseX - lastMouseX;
	int moveY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	rotation.y += moveX * moveSpeed;
	rotation.x += moveY * moveSpeed;

	SetCameraPositionAndAngle(position + VGet(0, 75, 0), rotation.x, rotation.y, 0);
}

void Player::Damage()
{
}

void Player::Debug()
{
	ImGui::Begin("Player");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &position.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::InputFloat("RotX", &rotation.x);
	ImGui::InputFloat("RotY", &rotation.y);
	ImGui::InputFloat("RotZ", &rotation.z);
	ImGui::End();
}