#include "Camera.h"
#include "Screen.h"

Camera::Camera()
{
	lastMouseX = Screen::WIDTH / 2;
	lastMouseY = Screen::HEIGHT / 2;
	mouseX = mouseY = 0;

	//�J�����̕\���͈͐ݒ�
	SetCameraNearFar(0.1f, cameraRange);

	player = ObjectManager::FindGameObject<Player>();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	playerPos = player->GetPosition();
	playerRot = player->GetRotation();

	position = playerPos + relativePos;
	ViewPoint();
}

void Camera::Draw()
{
}

void Camera::ViewPoint()
{
	//�}�E�X�̍��W���擾
	GetMousePoint(&mouseX, &mouseY);

	//�}�E�X�̈ړ��ʂ���J�����̉�]�p�x���Z�o�E�ݒ肷��
	int moveX = mouseX - lastMouseX;
	int moveY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// �v���C���[��]
	player->ViewRotate(moveX * moveSpeed, moveY * moveSpeed);

	SetCameraPositionAndAngle(position, playerRot.x, playerRot.y, 0);
}
