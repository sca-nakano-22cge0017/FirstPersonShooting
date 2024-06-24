#include "Camera.h"
#include "Screen.h"

Camera::Camera()
{
	lastMouseX = Screen::WIDTH / 2;
	lastMouseY = Screen::HEIGHT / 2;
	mouseX = mouseY = 0;

	//カメラの表示範囲設定
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
	//マウスの座標を取得
	GetMousePoint(&mouseX, &mouseY);

	//マウスの移動量からカメラの回転角度を算出・設定する
	int moveX = mouseX - lastMouseX;
	int moveY = mouseY - lastMouseY;

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// プレイヤー回転
	player->ViewRotate(moveX * moveSpeed, moveY * moveSpeed);

	SetCameraPositionAndAngle(position, playerRot.x, playerRot.y, 0);
}
