#pragma once
class Player
{
public:
	struct PlayerStats
	{
		int damMod;
		int defMod;
		int evaMod;
		int health;
		float winLossPerc;
		float wins;
		float loss;
		float power;
	};

	Player();
	~Player();

	void CalculateWinLoss();
	void CalculatePower();
	float GetPower();
	void Win();
	void Loss();
	void addDam(int add);
	void addDef(int add);
	void addEva(int add);
	int GetDef();
	int GetDam();
	int GetEva();
	int GetHealth();
	void DoDamage(int doo);
	void IncStatRand();
	void HealthRegen();

private:

	PlayerStats stats;

};

