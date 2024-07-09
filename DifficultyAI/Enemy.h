#pragma once
class Enemy
{
public:

	struct EnemyStats
	{
		int damMod;
		int defMod;
		int evaMod;
		int health;
	};

	Enemy(int dam, int def, int eva,int health);

	int GetDef();
	int GetDam();
	int GetEva();
	int GetHealth();
	void DoDamage(int doo);
	char Input(int playerAttackVal);

private:
	EnemyStats stats;

};

