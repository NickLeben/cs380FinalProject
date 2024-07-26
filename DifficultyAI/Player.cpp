#include "Player.h"
#include <random>

int playerStartingHealth = 10;

Player::Player()
{
	stats.health = playerStartingHealth;
	stats.wins = 0.0f;
	stats.loss = 0.0f;
	stats.damMod = 0;
	stats.defMod = 0;
	stats.evaMod = 0;
}

void Player::CalculateWinLoss()
{
	stats.winLossPerc = stats.wins / stats.loss;
}

void Player::CalculatePower()
{
	stats.power = ((stats.damMod + stats.defMod + stats.evaMod) / 3) * stats.winLossPerc;
}

float Player::GetPower()
{
	return stats.power;
}

void Player::Win()
{
	++stats.wins;
}

void Player::Loss()
{
	++stats.loss;
}

void Player::addDam(int add)
{
	stats.damMod += add;
}

void Player::addDef(int add)
{
	stats.defMod += add;
}

void Player::addEva(int add)
{
	stats.evaMod += add;
}

int Player::GetDef()
{
	return stats.defMod;
}

int Player::GetDam()
{
	return stats.damMod;
}

int Player::GetEva()
{
	return stats.evaMod;
}

int Player::GetHealth()
{
	return stats.health;
}

void Player::DoDamage(int doo)
{
	stats.health -= doo;
}

void Player::IncStatRand()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> DescRand(0, 4);

	int rando = DescRand(gen);

	if (rando == 0)
	{
		addDam(1);
	}
	else if (rando == 1)
	{
		addDef(1);
	}
	else if (rando == 2)
	{
		addEva(1);
	}
}
