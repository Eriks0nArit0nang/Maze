#include "Map.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <queue>
#include <fstream>

using namespace std;

Map *Map::instance = 0;

Map::Map(int size):map(new int*[size]),size(size),knownMap(new bool*[size]),distFromPlayer(new int*[size])
{
    for (int j = 0; j < size; j++)
    {
        map[j] = new int[size];
        distFromPlayer[j] = new int[size];
        knownMap[j] = new bool[size];
        for (int i = 0; i < size; i++)
            knownMap[j][i] = false;
    }
    srand(time(0));
}

Map::~Map()
{
    for (int i = 0; i < size; i++)
    {
        delete [] map[i];
        delete [] knownMap[i];
        delete [] distFromPlayer[i];
    }
    delete [] map;
    delete [] knownMap;
    delete [] distFromPlayer;
    instance = 0;
}

Map *Map::GetInstance()
{
    if (!instance)
        instance = new Map();
    return instance;
}

int **Map::GetGrid() const
{
    return map;
}

int Map::GetGridSize() const
{
    return size;
}

void Map::SetGrid(int **map, int size, std::pair<int,int> startPoint, std::pair<int,int> endPoint)
{
    if (size > 0)
    {
        this->map = map;
        this->size = size;
        startLoc = startPoint;
        endLoc = endPoint;
    }
}

void Map::RemoveInstance()
{
    delete instance;
}

std::pair<int, int> Map::GetEndLoc() const
{
    return endLoc;
}

std::pair<int, int> Map::GetStartLoc() const
{
    return startLoc;
}

void Map::Save(string filename)
{
    ofstream o;
    o.open (filename.c_str());
    o << size << " ";
    o << startLoc.first << " ";
    o << startLoc.second << " ";
    o << endLoc.first << " ";
    o << endLoc.second << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            o << map[i][j] << " ";
        o << endl;
    }
    o.close();
}

void Map::Load(string filename)
{
    ifstream in;
    in.open (filename.c_str());
    if (!in.is_open())
    {
       cerr << "Error: File did not load correctly\n";
       return;
    }
    for (int i = 0; i < size; i++)
    {
        delete [] map[i];
        delete [] distFromPlayer[i];
        delete [] knownMap[i];
    }
    delete [] map;
    delete [] distFromPlayer;
    delete [] knownMap;
    in >> size;
    map = new int*[size];
    distFromPlayer = new int*[size];
    knownMap = new bool*[size];
    for (int i = 0; i < size; i++)
    {
        map[i] = new int[size];
        distFromPlayer[i] = new int[size];
        knownMap[i] = new bool[size];
        for (int j = 0; j < size; j++)
            knownMap[i][j] = false;
    }
        
    in >> startLoc.first;
    in >> startLoc.second;
    in >> endLoc.first;
    in >> endLoc.second;
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            in >> map[i][j];
    }
    in.close();
}

bool Map::Fog(int x, int y) const
{
    if (x < size && x >= 0 && y < size && y >= 0)
        return knownMap[x][y];
    cerr << "Error: Invalid bounds passed to Map::Fog (" << x << ") (" << y << ")\n";
    return false;
}

int **Map::GetDistFromPlayer() const
{
    return distFromPlayer;
}

void Map::UpdateDistFromPlayer(int gridX, int gridY)
{
    pair <queue <int>,queue <int> > q;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (map[i][j] == 1)
               distFromPlayer[i][j] = -1;
            else if (i == gridX && j == gridY)
            {
                distFromPlayer[i][j] = 1;
                q.first.push(i);
                q.second.push(j);
            }
            else
                distFromPlayer[i][j] = 0;
    int i,j;
    while (!q.second.empty())
    {
        i = q.first.front();
        j = q.second.front();
        if (distFromPlayer[i][j] == 30)
            break;
        if (distFromPlayer[i-1][j] == 0)
        {
            distFromPlayer[i-1][j] = distFromPlayer[i][j]+1;            
            q.first.push (i-1);
            q.second.push (j);
        }
        if (distFromPlayer[i+1][j] == 0)
        {
            distFromPlayer[i+1][j] = distFromPlayer[i][j]+1;
            q.first.push (i+1);
            q.second.push (j);
        }
        if (distFromPlayer[i][j-1] == 0)
        {
            distFromPlayer[i][j-1] = distFromPlayer[i][j]+1;
            q.first.push (i);
            q.second.push (j-1);
        }
        if (distFromPlayer[i][j+1] == 0)
        {
            distFromPlayer[i][j+1] = distFromPlayer[i][j]+1;
            q.first.push (i);
            q.second.push (j+1);
        }
        q.first.pop();
        q.second.pop();
     }
}

struct Prim_Values
{
       public:
              int x;
              int y;
              int x2;
              int y2;
              int weight;
};

struct comp{
bool operator()(Prim_Values x, Prim_Values y)
{
     return x.weight > y.weight;
}};

void Map::CreateAuto()
{
    for (int i = 0; i < size; i++)
    {
        delete [] knownMap[i];
        delete [] map[i];
        delete [] distFromPlayer[i];
    }
    delete [] knownMap;
    delete [] map;
    delete [] distFromPlayer;
    
    pair <int[4],int[GRID_SIZE][GRID_SIZE]> level;
    bool tocheck[GRID_SIZE][GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
        {
            tocheck[i][j] = false;
            level.second[i][j] = 1;
        }
    int t,t2;
    Prim_Values vals [(int)floor(GRID_SIZE/2)-5][(int)floor(GRID_SIZE/2)-5][4];
    do {
        for (int i = 0; i < 4; i++)
            level.first[i] = (rand () % ((int)floor(GRID_SIZE/2)-7))*2+7;
    } while (level.first[0] == level.first[2] && level.first[1] == level.first[3]);
    priority_queue <Prim_Values,vector <Prim_Values>,comp> nums;
    for (int i = 0; i < (int)floor(GRID_SIZE/2)-5; i++)
        for (int j = 0; j < (int)floor(GRID_SIZE/2)-5; j++)
            for (int k = 0; k < 4; k++)
            {
                vals[i][j][k].weight = rand () % 100000;
                vals[i][j][k].x = i*2+5;
                vals[i][j][k].y = j*2+5;
                if (k % 2 == 0)
                {
                    vals[i][j][k].x2 = i*2+5;
                    vals[i][j][k].y2 = j*2+3+k*2;//up left down right
                }
                else
                {
                    vals[i][j][k].x2 = i*2+1+k*2;
                    vals[i][j][k].y2 = j*2+5;
                }
                level.second[i*2+5][j*2+5] = 0;
            }
    level.second[level.first[0]][level.first[1]] = 2;
    level.second[level.first[2]][level.first[3]] = 3;
    for (int i = 0; i < 4; i++)
        nums.push(vals[(level.first[0]-5)/2][(level.first[1]-5)/2][i]);
    while (!nums.empty())
    {
        if (!(tocheck[nums.top().x2][nums.top().y2]))
        {
            tocheck[nums.top().x2][nums.top().y2] = true;
            level.second[(nums.top().x2+nums.top().x)/2][(nums.top().y2+nums.top().y)/2] = 0;
            t = (nums.top().x2-5)/2;
            t2 = (nums.top().y2-5)/2;
            nums.pop();
            for (int i = 0; i < 4; i++)
                if (t >= 0 && t < (int)floor(GRID_SIZE/2)-5 && t2 >= 0 && t2 < (int)floor(GRID_SIZE/2)-5)
                {
                    if (!(t == 0&&i==1)&&!(t==(int)floor(GRID_SIZE/2)-6&&i==3)&&!(t2==0&&i==0)&&!(t2==(int)floor(GRID_SIZE/2)-6&&i==2))
                        nums.push (vals[t][t2][i]);
                }
        }
        else
            nums.pop();
    }
     
    size = GRID_SIZE;
    map = new int *[size];
    knownMap = new bool *[size];
    distFromPlayer = new int *[size];
    for (int i = 0; i < size; i++)
    {
        map[i] = new int[size];
        knownMap[i] = new bool[size];
        distFromPlayer[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            map[i][j] = level.second[i][j];
            knownMap[i][j] = false;
        }
    }
    startLoc.first = level.first[0];
    startLoc.second = level.first[1];
    endLoc.first = level.first[2];
    endLoc.second = level.first[3];
    if (!VerifyLevel())
        cerr << "Error: Level created is not winnable.  Please alert the developer to this\n";
    
}

bool Map::VerifyLevel ()
{
    pair <queue <int>,queue<int> > que;
    que.first.push(startLoc.first);
    que.second.push(startLoc.second);
    int p[size][size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            p[i][j] = map[i][j];
            
    while (!que.first.empty())
    {
        if (p[que.first.front()][que.second.front()] != 1)
        {
            if (p[que.first.front()][que.second.front()] == 3)
                return true;
            p[que.first.front()][que.second.front()] = 1;
            if (p[que.first.front()+1][que.second.front()] == 0 || p[que.first.front()+1][que.second.front()] == 3)
            {
                que.first.push(que.first.front()+1);
                que.second.push(que.second.front());
            }
            if (p[que.first.front()-1][que.second.front()] == 0 || p[que.first.front()-1][que.second.front()] == 3)
            {
                que.first.push(que.first.front()-1);
                que.second.push(que.second.front());
            }
            if (p[que.first.front()][que.second.front()+1] == 0 || p[que.first.front()][que.second.front()+1] == 3)
            {
                que.first.push(que.first.front());
                que.second.push(que.second.front()+1);
            }
            if (p[que.first.front()][que.second.front()-1] == 0 || p[que.first.front()][que.second.front()-1] == 3)
            {
                que.first.push(que.first.front());
                que.second.push(que.second.front()-1);
            }
        }
        que.first.pop();
        que.second.pop();
    }
    return false;
}

void Map::UpdateFog(int x, int y)
{
    for (int i = -5; i <= 5; i++)
        for (int j = -5; j <= 5; j++)
            if (x+i >= 0 && x+i < size && y+j >= 0 && y+j < size)
                knownMap[x+i][y+j] = true;
}
        
