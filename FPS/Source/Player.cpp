#include "../ImGui/imgui.h"
#include "Player.h"
#include "Stage.h"
using namespace std;

Player::Player()
{
	gun = new PlayersGun(this);
	assert(gun != nullptr);
	
	position = VGet(0, 200, 0);
	rotation = VGet(0, -0.5f * (float)DX_PI, 0);

	vy = 0;
	isGround = false;
	lastJumpKey = false;
	isJumping = false;

	lastHitKey = false;
	elapsedTime = coolTime;

	hp = InitHp;

	hModel = MV1LoadModel("data/Player/Player.mv1");

	//�A�j���[�V����
	string folder = "data/Player/";
	string fileName[] = {
		"Standing Idle"
	};
	for (int i = 0; i < MAX; i++)
	{
		hAnimation[i] = MV1LoadModel((folder + fileName[i] + ".mv1").c_str());
	}
	animation = new Animation();
	animation->SetModel(hModel); //�A�j���[�V������t���郂�f��
	animation->Play(hAnimation[A_IDLE], true);
}

Player::~Player()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
	}
}

void Player::Update()
{
	MV1RefreshCollInfo(hModel); // �R���W�������̍X�V

	GroundCheck();
	Jump();
	Move();
	Attack();

	Debug();
}

void Player::Draw()
{
	if (hModel != -1)
	{
		MV1SetPosition(hModel, position + VGet(0, -100, 0));
		MV1SetRotationXYZ(hModel, VGet(0, rotation.y + DX_PI, 0));
		MV1DrawModel(hModel);
	}
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

void Player::Move()
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
}

void Player::GroundCheck()
{
	VECTOR nearHitPos = position - VGet(0, -500, 0);
	bool hit = false;

	objects = ObjectManager::FindGameObjects<StageObjects>();
	for (StageObjects* o : objects)
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

void Player::Attack()
{
	if (gun == nullptr) return;

	elapsedTime += 1.0f / 60.0f;

	if (elapsedTime >= coolTime)
	{
		//���N���b�N�Ŕ��C
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//�������u�ԂȂ�
			if (!lastHitKey)
			{
				lastHitKey = true;
				gun->Fire();
				elapsedTime = 0;
			}
		}
		else lastHitKey = false;
	}
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