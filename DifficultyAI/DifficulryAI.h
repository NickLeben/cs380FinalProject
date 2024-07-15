#pragma once
#include "Enemy.h"

class Item
{

};

class Room
{
public:
    int ParentRoom = -1;
    int ForwardsRoom = -1; //-1 = No position i.e ERROR, -2 = No exit
    int LeftRoom = -1;
    int rightRoom = -1;
    std::string Description;
    Enemy EnemyInRoom;
    Item ItemInRoom;
    Room() : ParentRoom(-1), ForwardsRoom(-1), LeftRoom(-1), rightRoom(-1) {};
};

int InitRoomVector(std::vector<Room>* RoomList, int loc, bool start = false);
Room GenerateRoom(int ParentRoom);
