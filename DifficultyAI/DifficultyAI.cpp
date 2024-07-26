// DifficultyAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "DifficulryAI.h"
#include "Player.h"
#include "Enemy.h"
#include <string.h>
#include <random>
#include "EnemyManager.h"
#include <iomanip>

EnemyManager enemyMan;
Player* mainGuy;

int main()
{
    //std::cout << "Hello World!\n";

    mainGuy = new Player;
    std::vector<Room> RoomList;
    InitRoomVector(&RoomList, -1, true);
    std::cout << RoomList[0].Description;

    enemyMan.Init();

    bool AutoTest = false;
    int AutoInc = 0;
    int AutoRoom = 0;
    int AutoLimit = 100;
    int location = 0;
    bool exit = false;
    std::string input;
    while (!exit)
    {
        if (AutoTest)
        {
            if (AutoInc == 0)
            {
                input = "north";
            }
            else if (AutoInc == 1)
            {
                input = "east";
            }
            else
            {
                input = "west";
            }

            if (AutoRoom >= AutoLimit)
            {
                std::cout << std::string("Done!\n");
                std::cin >> input;
            }
            AutoRoom++;
        }
        else
        {
            std::cin >> input;
        }
        if (input == "north" || input == "forwards")
        {
            if (RoomList[location].ForwardsRoom == -2)
            {
                std::cout << std::string("Thats a wall...(n)\n");
                AutoInc = 1;
            }
            else if (RoomList[location].ForwardsRoom == -1)
            {
                int oldloc = location;
                location = InitRoomVector(&RoomList,location);
                RoomList[oldloc].ForwardsRoom = location;
                std::cout << RoomList[location].Description;
                //if (RoomList[location].EnemyInRoom.GetHealth() > 0)
                //{
                Combat(RoomList[location].EnemyInRoom, mainGuy, AutoTest);
                //}
            }
            else
            {
                location = RoomList[location].ForwardsRoom;
                std::cout << RoomList[location].Description;
            }
        }
        else if (input == "west" || input == "right")
        {
            if (RoomList[location].rightRoom == -2)
            {
                std::cout << std::string("Thats a wall...(w)\n");
                AutoInc = 0;
            }
            else if (RoomList[location].rightRoom == -1)
            {
                int oldloc = location;
                location = InitRoomVector(&RoomList, location);
                RoomList[oldloc].rightRoom = location;
                std::cout << RoomList[location].Description;
                Combat(RoomList[location].EnemyInRoom, mainGuy, AutoTest);
            }
            else
            {
                location = RoomList[location].rightRoom;
                std::cout << RoomList[location].Description;
            }
        }
        else if (input == "east" || input == "left")
        {
            if (RoomList[location].LeftRoom == -2)
            {
                std::cout << std::string("Thats a wall...(e)\n");
                AutoInc = 2;
            }
            else if (RoomList[location].LeftRoom == -1)
            {
                int oldloc = location;
                location = InitRoomVector(&RoomList, location);
                RoomList[oldloc].LeftRoom = location;
                std::cout << RoomList[location].Description;
                Combat(RoomList[location].EnemyInRoom, mainGuy, AutoTest);
            }
            else
            {
                location = RoomList[location].LeftRoom;
                std::cout << RoomList[location].Description;
            }
        }
        else if (input == "south" || input == "back")
        {
            if (RoomList[location].ParentRoom == -1)
            {
                std::cout << std::string("No running away coward! \n");
            }
            else
            {
                location = RoomList[location].ParentRoom;
                std::cout << RoomList[location].Description;
            }
        }
        else if (input == "stats")
        {
            //add option to print out stats (keep turn = 0)
            std::cout << std::string("Dam: ") << mainGuy->GetDam() << std::string(", Def: ") << mainGuy->GetDef() << std::string(", Eva: ") << mainGuy->GetEva() << std::string(", Health: ") << mainGuy->GetHealth() << std::string("\n");
        }
        else if (input == "rate")
        {
            enemyMan.CalculateWinPerc();
            std::cout << std::string("Winrate: ") << std::setw(5) << enemyMan.GetWinLoss() << std::string("\n");
        }
        else if (input == "auto")
        {
            AutoTest = true;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

int InitRoomVector(std::vector<Room>* RoomList, int loc, bool start)
{
    Room StartRoom;
    if (start)
    {
        StartRoom.Description = std::string("Blah Blah Blah you are at the entrance, type north or forwards to go into the dungeon \nYou can type left/west or right/east to go to the sides as well.\n");
        StartRoom.ForwardsRoom = -1;
        StartRoom.LeftRoom = -2;
        StartRoom.rightRoom = -2;
        RoomList->push_back(StartRoom);
        return 0;
    }
    else
    {
        StartRoom = GenerateRoom(loc);
        RoomList->push_back(StartRoom);
        return RoomList->size() - 1;
    }
}

Room GenerateRoom(int Parent)
{
    std::random_device rd; 
    std::mt19937 gen(rd()); //Sets up random number generation

    Room NewRoom;

    //list of descriptions, update count with changes or bad things will happen
    #define DescOptions 5
    std::string DescList[DescOptions] = { std::string("mongus room.\n"), std::string("chungus room.\n"), std::string("fungus room.\n"), std::string("word that ends with -ungus room.\n"), std::string("r o o m n a m e.\n") };

    std::uniform_int_distribution<> DescRand(0, DescOptions-1);

    NewRoom.Description = DescList[DescRand(gen)]; //Chose random description

    std::uniform_int_distribution<> CountRand(1, 3);
    int DoorCount = CountRand(gen);
    for (int i = 3; i > DoorCount; i--)
    {
        int choice = CountRand(gen); //can chose a door thats already been selected, whatever
        if (choice == 3)
        {
            NewRoom.rightRoom = -2;
        }
        else if (choice == 2)
        {
            NewRoom.ForwardsRoom = -2;
        }
        else
        {
            NewRoom.LeftRoom = -2;
        }
    }

    //temporary
    NewRoom.EnemyInRoom = Enemy(2,2,2,10);
    enemyMan.AssignStats(&NewRoom.EnemyInRoom, mainGuy);

    //use algorithm for items/
    NewRoom.ParentRoom = Parent;
    return NewRoom;
}

void Combat(Enemy enmy, Player* plyr, bool AutoMode)
{
    int turn = 0;
    std::cout << std::string("Supprise, A goblin! \n");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> TurnRand(0, 1);
    std::uniform_int_distribution<> D6Rand(1, 6);

    if (TurnRand(gen) == 0)
    {
        std::cout << std::string("Goblin goes first!\n");
    }
    else
    {
        std::cout << std::string("You go first!\n");
        turn = 1;
    }

    while (enmy.GetHealth() > 0 && mainGuy->GetHealth() > 0)
    {
        std::string input;
        if (turn == 0)
        {
            //goblin turn
            std::cout << std::string("\nGoblin's turn!\n");
            std::cout << std::string("Do you defend or evade?\n");
            int DmgRoll = std::max(1, D6Rand(gen) + enmy.GetDam());
            std::cout << std::string("They are doing ") << DmgRoll << std::string(" damage.\n");
            if (AutoMode)
            {
                input = "defend";
            }
            else
            {
                std::cin >> input;
            }
            if (input == "defend" || input == "Defend")
            {
                //do dice roll
                int DefRoll = std::max(1, D6Rand(gen) + plyr->GetDef());
                //int DmgRoll = std::max(1, D6Rand(gen) + enmy.GetDam());
                std::cout << std::string("You take ") << std::max(1, DmgRoll-DefRoll) << std::string(" damage!\n");
                plyr->DoDamage(std::max(1, DmgRoll - DefRoll));
            }
            else if (input == "evade" || input == "Evade")
            {
                int EvaRoll = std::max(1, D6Rand(gen) + plyr->GetEva());
                //int DmgRoll = std::max(1, D6Rand(gen) + enmy.GetDam());
                if (DmgRoll > EvaRoll)
                {
                    std::cout << std::string("Evade failed! You take ") << enmy.GetDam() << std::string(" Damage!\n");
                    plyr->DoDamage(enmy.GetDam());
                }
                else
                {
                    std::cout << std::string("Evade sucseded!\n");
                }
                turn = 1;
            }
            else
            {
                std::cout << std::string("Due to your innability to spell words, you fumble and take double damage!\n");
                std::cout << std::string("You take ") << enmy.GetDam()*2 << std::string(" Damage!\n");
                plyr->DoDamage(enmy.GetDam()*2);
                turn = 1;
            }
        }
        else
        {
            //your turn
            //attack
            std::cout << std::string("\nYou're turn!\n");
            std::cout << std::string("You attack!\n");
            if (enmy.Input(plyr->GetDam()) == 'd')
            {
                int DefRoll = std::max(1, D6Rand(gen) + enmy.GetDef());
                int DmgRoll = std::max(1, D6Rand(gen) + plyr->GetDam());
                std::cout << std::string("Enemy defends!\n");
                std::cout << std::string("You deal ") << (std::max(1, DmgRoll - DefRoll)) << std::string(" damage!\n");
                enmy.DoDamage(std::max(1, DmgRoll - DefRoll));
            }
            else
            {
                std::cout << std::string("Enemy attempts to evade!\n");
                // roll dice
                int EvaRoll = std::max(1, D6Rand(gen) + enmy.GetEva());
                int DmgRoll = std::max(1, D6Rand(gen) + plyr->GetDam());
                if (EvaRoll > DmgRoll)
                {
                    std::cout << std::string("They Evaded!\n");
                }
                else
                {
                    std::cout << std::string("Evade Failed!\n");
                    enmy.DoDamage(DmgRoll);
                    std::cout << std::string("You deal \n") << DmgRoll << std::string(" damage!\n");
                }
            }
            std::cout << std::string("Enemy Has ") << enmy.GetHealth() << std::string(" health.\n");
            turn = 0;
        }
    }

    std::cout << std::string("Combat over!\n");

    if (mainGuy->GetHealth() > 0 && enmy.GetHealth() < 1)
    {
        enemyMan.wins++;
        std::cout << std::string("You Won!\n");
    }
    else
    {
        std::cout << std::string("You Lost!\n");
    }

    enemyMan.totalBattles++;

    mainGuy->IncStatRand();
    mainGuy->HealthRegen();
}
