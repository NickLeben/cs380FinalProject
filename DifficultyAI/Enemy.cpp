#include "Enemy.h"

Enemy::Enemy(int dam, int def, int eva, int health)
{
	stats.damMod = dam;
	stats.defMod = def;
	stats.evaMod = eva;
	stats.health = health;
}

Enemy::Enemy()
{
	stats.damMod = 0;
	stats.defMod = 0;
	stats.evaMod = 0;
	stats.health = 1;
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

	if (playerAttackVal > stats.evaMod + 5)
	{
		//cannot possibly evade
		return 'd';
	}
	
	return 'e';
}

void Enemy::SetDef(int set)
{
	stats.defMod = set;
}

void Enemy::SetDam(int set)
{
	 stats.damMod = set;
}

void Enemy::SetEva(int set)
{
	 stats.evaMod = set;
}

void Enemy::SetHealth(int set)
{
	 stats.health = set;
}