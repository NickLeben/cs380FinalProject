#include "EnemyManager.h"
#include <random>
#include <iostream>

void EnemyManager::Init()
{
	winPerc = 0.0f;
	wins = 0.0f;
	ties = 0.0f;

	goalWinLoss = .33f;
}

void EnemyManager::CalculateWinPerc()
{
	if (totalBattles > 0)
	{
		winPerc = (float)wins / ((float)totalBattles - (float)ties);
	}
}

void EnemyManager::AssignStats(Enemy* enemy, Player* player)
{
	//for every 5% off add 1 skill point

	CalculateWinPerc();

	if (winPerc == 0)
	{
		enemy->SetDam(player->GetDam());
		enemy->SetDef(player->GetDef());
		enemy->SetEva(player->GetEva());
		enemy->SetHealth(player->GetHealth());
	}
	else if (winPerc < goalWinLoss)
	{
		float diffmod = (winPerc - goalWinLoss)*10;
		int pointchange = diffmod / 1;
		//make enemy strong
		enemy->SetDam(player->GetDam());
		enemy->SetDef(player->GetDef());
		enemy->SetEva(player->GetEva());
		enemy->SetHealth(player->GetHealth());

		if (pointchange > 0)
		{
			for (int i = 0; i < pointchange; ++i)
			{
				IncStatRand(enemy);
			}
		}
	}
	else if (goalWinLoss < winPerc)
	{
		float diffmod = (goalWinLoss - winPerc) * 10;
		int pointchange = diffmod / 1;
		for (int i = 0; i > pointchange; --i)
		{
			DecStatRand(enemy);
		}
		
	}

	if (goalWinLoss < 0.4f && goalWinLoss < winPerc)
	{
		enemy->SetDam(5);
		enemy->SetDef(5);
		enemy->SetEva(5);
	}

	std::cout << "Gobo stats: Dam " << enemy->GetDam() << ". Def " << enemy->GetDef() << ". Eva " << enemy->GetEva() << ". Hp" << enemy->GetHealth() << "\n";

}

float EnemyManager::GetWinLoss()
{
	return winPerc;
}

void EnemyManager::IncStatRand(Enemy* enmy)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> DescRand(0, 3);

	int rando = DescRand(gen);

	if (rando == 0)
	{
		enmy->SetDam(enmy->GetDam() + 1);
	}
	else if (rando == 1)
	{
		enmy->SetDef(enmy->GetDef() + 1);
	}
	else if (rando == 2)
	{
		enmy->SetEva(enmy->GetEva() + 1);
	}
}

void EnemyManager::DecStatRand(Enemy* enmy)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> DescRand(0, 3);

	int rando = DescRand(gen);

	if (rando == 0)
	{
		enmy->SetDam(enmy->GetDam() - 1);
	}
	else if (rando == 1)
	{
		enmy->SetDef(enmy->GetDef() - 1);
	}
	else if (rando == 2)
	{
		enmy->SetEva(enmy->GetEva() - 1);
	}
}