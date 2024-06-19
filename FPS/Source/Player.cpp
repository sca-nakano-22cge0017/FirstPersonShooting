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

	//F�L�[���������ňړ����x�㏸
	if (CheckHitKey(KEY_INPUT_F)) move = VGet(0, 0, speed) * runSpeedTimes;
	else move = VGet(0, 0, speed);

	VECTOR forward = move * rotY;
	VECTOR right = forward * MGetRotY(-0.5 * DX_PI);
	VECTOR left = forward * MGetRotY(0.5 * DX_PI);

	//WASD�ړ�
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

	//�㉺�����ւ̎��_�ړ��ɐ������|����
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
		if (!isJumping) // �W�����v���łȂ����
			position = nearHitPos + playerHeight; // position��n�ʂɍ��킹��

		if (position.y <= nearHitPos.y + playerHeight.y)
		{
			isGround = true;
			isJumping = false;
		}
		else isGround = false;
	}
	else isGround = false;
}

const float g = 9.8f; //�d�͉����x
void Player::Jump()
{
	//�ڒn���Ă�����
	if (isGround)
	{
		//�X�y�[�X�L�[����������
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			isJumping = true;

			//�O�t���[���ŉ�����Ă����Ԃ���Ȃ������� = �������u�Ԃ�������
			if (!lastJumpKey)
			{
				//�㏸
				vy = firstJumpVelocity;
				position.y += vy;
			}
			lastJumpKey = true;
		}
		else lastJumpKey = false;
	}

	//�ڒn���Ă��Ȃ�������
	else
	{
		//���R����
		vy -= g / 60;
		position.y += vy;
	}
}

void Player::Damage()
{
}

void Player::Debug()
{
	//�v���C���[�̍��W�E�p�x�Ȃǂ�\��
	ImGui::Begin("Player");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &position.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::InputFloat("RotX", &rotation.x);
	ImGui::InputFloat("RotY", &rotation.y);
	ImGui::InputFloat("RotZ", &rotation.z);
	ImGui::End();
}