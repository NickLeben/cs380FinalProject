#pragma once

class Item
{

};

class Enemy
{

};

class Room
{
public:
    int ParentRoom = -1;
    int NextRoom = -1;
    std::string Description;
    Enemy EnemyInRoom;
    Item ItemInRoom;
    Room() : ParentRoom(-1), NextRoom(-1) {};
};

int InitRoomVector(std::vector<Room>* RoomList, bool start = false);
void GameLoop(std::vector<Room>* RoomList);
