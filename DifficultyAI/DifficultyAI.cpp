// DifficultyAI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "DifficulryAI.h"
#include "Player.h"
#include "Enemy.h"
#include <string.h>
#include <random>

int main()
{
    std::cout << "Hello World!\n";
    Player* mainGuy = new Player;
    std::vector<Room> RoomList;
    InitRoomVector(&RoomList, -1, true);
    std::cout << RoomList[0].Description;

    int location = 0;
    bool exit = false;
    std::string input;
    while (!exit)
    {
        std::cin >> input;
        if (input == "north" || input == "forwards")
        {
            if (RoomList[location].ForwardsRoom == -2)
            {
                std::cout << std::string("Thats a wall...");
            }
            else if (RoomList[location].ForwardsRoom == -1)
            {
                int oldloc = location;
                location = InitRoomVector(&RoomList,location);
                RoomList[oldloc].ForwardsRoom = location;
                std::cout << RoomList[location].Description;
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
                std::cout << std::string("Thats a wall...");
            }
            else if (RoomList[location].rightRoom == -1)
            {
                int oldloc = location;
                location = InitRoomVector(&RoomList, location);
                RoomList[oldloc].rightRoom = location;
                std::cout << RoomList[location].Description;
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
                std::cout << std::string("Thats a wall...");
            }
            else if (RoomList[location].LeftRoom == -1)
            {
                int oldloc = location;
                location = InitRoomVector(&RoomList, location);
                RoomList[oldloc].LeftRoom = location;
                std::cout << RoomList[location].Description;
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

    //use algorithm for items/
    NewRoom.ParentRoom = Parent;
    return NewRoom;
}
