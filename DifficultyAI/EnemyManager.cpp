#include "EnemyManager.h"


void EnemyManager::Init()
{
	winPerc = 0.0f;
	wins = 0.0f;
	ties = 0.0f;

	goalWinLoss = .5f;
}

void EnemyManager::CalculateWinPerc()
{
	winPerc = wins/(totalBattles - ties);
}

void EnemyManager::AssignStats(Enemy* enemy, Player* player)
{
	//for every 5% off add 1 skill point

	CalculateWinPerc();

	if (winPerc > goalWinLoss)
	{
		int diffmod = winPerc - goalWinLoss;
		int pointchange = diffmod / 5;
		//make enemy strong
		enemy->SetDam(player->GetDam() + pointchange);
		enemy->SetDef(player->GetDef() + pointchange);
		enemy->SetEva(player->GetEva() + pointchange);
		enemy->SetHealth(player->GetHealth() + pointchange);
	}
	else
	{
		int diffmod = winPerc - goalWinLoss;
		int pointchange = (diffmod / 5);
		//make enemy weak
		enemy->SetDam(player->GetDam() + pointchange);
		enemy->SetDef(player->GetDef() + pointchange);
		enemy->SetEva(player->GetEva() + pointchange);
		enemy->SetHealth(player->GetHealth() + pointchange);
	}
}
