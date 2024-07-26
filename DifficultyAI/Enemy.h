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
	Enemy();

	int GetDef();
	int GetDam();
	int GetEva();
	int GetHealth();
	void DoDamage(int doo);
	char Input(int playerAttackVal);

	void SetDef(int set);
	void SetDam(int set);
	void SetEva(int set);
	void SetHealth(int set);

private:
	EnemyStats stats;

};

