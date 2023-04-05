/* Your code here! */
#include "dsets.h"
#include <iostream>
#include <vector>
#include "cs225/PNG.h"
using namespace std;
using namespace cs225;
class SquareMaze {
    public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze();
    PNG* drawMazeWithSolution();
    private:
    int position(int x, int y) const;
    int xposition(int input) const;
    int yposition(int input) const;
    int ending;
    int width_;
    int height_;
    vector<vector<bool>> wall_;
    DisjointSets maze_;
};