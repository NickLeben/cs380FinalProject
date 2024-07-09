// DifficultyAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "DifficulryAI.h"
#include "Player.h"
#include "Enemy.h"
#include <string.h>

int main()
{
    std::cout << "Hello World!\n";
    Player* mainGuy = new Player;
    std::vector<Room> RoomList;
    InitRoomVector(&RoomList, true);
    std::cout << RoomList[0].Description;

    int location = 0;
    bool exit = false;
    std::string input;
    while (!exit)
    {
        std::cin >> input;
        if (input == "north" && RoomList[location].NextRoom == -1)
        {
            location = InitRoomVector(&RoomList);
            //std::stringstream locstring;
            //locstring << "at pos " << location;
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

int InitRoomVector(std::vector<Room>* RoomList, bool start = false)
{
    Room StartRoom;
    if (start)
    {
        StartRoom.Description = std::string("Blah Blah Blah you are at the entrance, type north to go into the dungeon");
        RoomList->push_back(StartRoom);
        return 0;
    }
    else
    {
        StartRoom.Description = std::string("you in room, type north to go to the next room");
        RoomList->push_back(StartRoom);
        return RoomList->size() - 1;
    }
}
