#include "UI.h"
#include "Screen.h"
#include <assert.h>

/// <summary>
/// UI
/// </summary>
UI::UI()
{
	player = ObjectManager::FindGameObject<Player>();
	assert(player != nullptr);

	gun = ObjectManager::FindGameObject<PlayersGun>();
	assert(player != nullptr);

	hp = player->GetHp();
	fullBullets = gun->GetFullBullets();
	restBullets = gun->GetRestBullets();
}

UI::~UI()
{
}

void UI::Update()
{
	hp = player->GetHp();
	fullBullets = gun->GetFullBullets();
	restBullets = gun->GetRestBullets();
}

void UI::Draw()
{
	DrawString(0, Screen::HEIGHT - 50, "Push [T]Key To Title", GetColor(255, 255, 255));

	//HP�\��
	DrawFormatString(Screen::WIDTH - 200, Screen::HEIGHT - 50, GetColor(39, 136, 52), "HP:%2d", hp);

	//�c�e���\��
	DrawFormatString
	(Screen::WIDTH - 200, Screen::HEIGHT - 75, GetColor(255, 255, 255), "�c�e��:%2d", restBullets);

	//���e�B�N���\��
	SetFontSize(64);
	DrawString(Screen::WIDTH / 2 - 16, Screen::HEIGHT / 2 - 32, "+", GetColor(255, 255, 255));
	SetFontSize(16);
}
