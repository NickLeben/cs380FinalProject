#pragma once
class Player
{
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

	void CalculateWinLoss();
	void CalculatePower();
	float GetPower();
	void Win();
	void Loss();
	void addDam(int add);
	void addDef(int add);
	void addEva(int add);

private:

	PlayerStats stats;

};

