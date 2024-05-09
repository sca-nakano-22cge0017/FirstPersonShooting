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

	//�J�����̕\���͈͐ݒ�
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
			if(!isJumping) // �W�����v���łȂ����
				position = groundHit + playerHeight; // position��n�ʂɍ��킹��

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

void Player::ViewPoint() //���_�ړ�
{
	//�}�E�X�̍��W���擾
	GetMousePoint(&mouseX, &mouseY);

	//�}�E�X�̈ړ��ʂ���J�����̉�]�p�x���Z�o�E�ݒ肷��
	int moveX = mouseX - lastMouseX;
	int moveY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	rotation.y += moveX * moveSpeed;

	//�㉺�����ւ̎��_�ړ��ɐ������|����
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