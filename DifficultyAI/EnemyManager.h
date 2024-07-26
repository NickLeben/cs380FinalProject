#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"

class EnemyManager
{
	public:

		void Init();
		void CalculateWinPerc();
		void AssignStats(Enemy* enemy, Player* player);
		float GetWinLoss();

		int totalBattles;
		int wins;
		int ties;

	private:
		float winPerc = 0;
		float goalWinLoss = 0;
		std::vector<Enemy> EnemyList;
};

