#include "Enemy.h"

Enemy::Enemy(int dam, int def, int eva, int health)
{
	stats.damMod = dam;
	stats.defMod = def;
	stats.evaMod = eva;
	stats.health = health;
}

int Enemy::GetDef()
{
	return stats.defMod;
}

int Enemy::GetDam()
{
	return stats.damMod;
}

int Enemy::GetEva()
{
	return stats.evaMod;
}

int Enemy::GetHealth()
{
	return stats.health;
}

void Enemy::DoDamage(int doo)
{
	stats.health -= doo;
}

char Enemy::Input(int playerAttackVal)
{
	//return defend for now, at a later date, use w/l of player to decide how smart enemy is, and weight what the player rolled vs possibility of evading

	if (playerAttackVal > stats.evaMod + 6)
	{
		//cannot possibly evade
		return 'd';
	}
	
	return 'e';
}
