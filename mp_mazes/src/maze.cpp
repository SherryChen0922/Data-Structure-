/* Your code here! */
#include "maze.h"
#include <queue>


int SquareMaze::position(int x, int y) const {
    return y * width_ + x;
}
int SquareMaze::xposition(int input) const {
    return input % width_;
}
int SquareMaze::yposition(int input) const {
    return input / width_;
}
SquareMaze::SquareMaze() {
    width_ = 0;
    height_ = 0;
    ending = 0;
}
void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    wall_.resize(width_*height_);
    for(int i = 0; i < width_*height_;i++) {
        wall_[i].resize(2);
        wall_[i][0] = true;
        wall_[i][1] = true;
    }
    maze_.addelements(width_*height_);
    int count = 0;
    while(count < width_*height_-1) {
        int x = rand() % width_;
        int y = rand() % height_;
        int dir = rand() % 2;
        bool change = false;
        if(dir == 0) {
            if(x < width_ -1 && maze_.find(position(x,y)) != maze_.find(position(x,y) + 1)) {
                maze_.setunion(position(x,y), position(x,y) + 1);
                count++;
                setWall(x,y, 0,false);
                change = true;
            }
        } 
        if(change == false){
            if(y < height_ -1 && maze_.find(position(x,y)) != maze_.find(position(x,y+1))) {
                maze_.setunion(position(x,y), position(x,y+1));
                count++;
                setWall(x,y, 1,false);
                change = true;
            }
        }
    }
}
bool SquareMaze::canTravel(int x, int y, int dir) const {
    if(dir == 0) {
        if(x >= width_ - 1) {
           return false;
         }
        return !(wall_[position(x,y)][0]);
    } else if (dir == 1) {
         if(y >= height_ -1) {
           return false;
         }
        return !(wall_[position(x,y)][1]);
    } else if(dir == 2) {
        if(x == 0) {
            return false;
        }
        return !(wall_[position(x,y)-1][0]);
    } else  {
        if(y == 0 ) {
            return false;
        }
        return !(wall_[position(x, y-1)][1]);
    }
}
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if(dir == 0) {
        wall_[y * width_ + x][0] = exists;
    } 
    if(dir == 1) {
        wall_[y * width_ + x][1] = exists;
    }
}
vector<int> SquareMaze::solveMaze() {
    vector<int> output;
    queue<int> q;
    vector<int> direct;
    vector<bool> visited;
    vector<int> step;
    for(int i = 0; i < width_*height_; i++) {
        direct.push_back(-1);
        visited.push_back(false);
        step.push_back(0);
    }
    q.push(0);
    visited[0] = true;
    while(!q.empty()) {
        int curr = q.front();
        int x = xposition(curr);
        int y = yposition(curr);
        if(canTravel(x,y,0) && visited[curr + 1] == false) {
            q.push(curr + 1);
            direct[curr + 1] = 0;
            visited[curr + 1] = true;
            step[curr + 1] = step[curr] + 1;
        }
        if(canTravel(x,y,1) && visited[curr + width_] == false) {
            q.push(curr + width_);
            direct[curr + width_] = 1;
            visited[curr + width_] = true;
            step[curr + width_] = step[curr] + 1;
        }
        if(canTravel(x,y,2) && visited[curr - 1] == false) {
            q.push(curr - 1);
            direct[curr - 1] = 2;
            visited[curr - 1] = true;
            step[curr - 1] = step[curr] + 1;
        }
        if(canTravel(x,y,3) && visited[curr - width_] == false) {
            q.push(curr - width_);
            direct[curr - width_] = 3;
            visited[curr - width_] = true;
            step[curr - width_] = step[curr] + 1;
        }
        q.pop();
    }
    int max = width_*(height_-1);
    for(int i = width_*(height_-1); i < width_*height_;i++) {
        if(step[i] > step[max]) {
            max = i;
        }
    }
    std::cout << step[max] << std::endl;
    ending = max;
    //int total = max;
    for(int i = 0; i < step[ending];i++) {
        output.push_back(direct[max]);
        if(direct[max] == 0) {
            max = max - 1;
        } else if(direct[max] == 1) {
            max = max - width_;
        } else if(direct[max] == 2) {
            max = max + 1;
        } else if (direct[max] == 3) {
            max = max + width_;
        }
    }
    std::cout << output.size() << std::endl;
    vector<int> output1;
    for(unsigned i = 0;i < output.size(); i++) {
        output1.push_back(output[output.size() - i - 1]);
    }
    std::cout << output1.size() << std::endl;
    return output1;
}
PNG* SquareMaze::drawMaze() {
    PNG* output = new PNG(width_*10+1,height_*10+1);
    for(int i = 0; i < width_*10+1; i++) {
        output->getPixel(i, 0).l = 0.0;
    }
    for(int i = 0; i < 10; i++) {
        output->getPixel(i, 0).l = 1.0;
    }
    for(int i = 0; i < height_*10+1; i++) {
        output->getPixel(0, i).l = 0.0;
    }
    for(int i = 0; i < width_; i++) {
        for(int j = 0; j < height_; j++) {
            if(wall_[position(i,j)][0] == true) {
                for(int k = 0; k < 11; k++) {
                    output->getPixel((i + 1) * 10, j*10 + k).l = 0.0;
                }
            }
            if(wall_[position(i,j)][1] == true) {
                for(int k = 0; k < 11; k++) {
                    output->getPixel(i*10 + k, (j+1) *10).l = 0.0;
                }
            }
        }
    }
    return output;
}
PNG* SquareMaze::drawMazeWithSolution() {
    PNG* output = drawMaze();
    vector<int> direct = solveMaze();
    int x = 5;
    int y = 5;
    output->getPixel(x,y).h = 0.0;
    output->getPixel(x,y).s = 1.0;
    output->getPixel(x,y).l = 0.5;
    output->getPixel(x,y).a = 1.0;
    for(unsigned i = 0; i < direct.size();i++) {
        if(direct[i] == 0) {
            for(int j = 0; j < 10; j++) {
                x++;
                output->getPixel(x,y).h = 0.0;
                output->getPixel(x,y).s = 1.0;
                output->getPixel(x,y).l = 0.5;
                output->getPixel(x,y).a = 1.0;
                //x++;
            }
        }
        if(direct[i] == 1) {
            for(int j = 0; j < 10; j++) {
                y++;
                output->getPixel(x,y).h = 0.0;
                output->getPixel(x,y).s = 1.0;
                output->getPixel(x,y).l = 0.5;
                output->getPixel(x,y).a = 1.0;
                //y++;
            }
        }
        if(direct[i] == 2) {
            for(int j = 0; j < 10; j++) {
                x--;
                output->getPixel(x,y).h = 0.0;
                output->getPixel(x,y).s = 1.0;
                output->getPixel(x,y).l = 0.5;
                output->getPixel(x,y).a = 1.0;
                //x--;
            }
        }
        if(direct[i] == 3) {
            for(int j = 0; j < 10; j++) {
                y--;
                output->getPixel(x,y).h = 0.0;
                output->getPixel(x,y).s = 1.0;
                output->getPixel(x,y).l = 0.5;
                output->getPixel(x,y).a = 1.0;
                //y--;
            }
        }
    }
    int endx = xposition(ending);
    int endy = yposition(ending);
//      int endx = xposition(ending);
//    int endy = yposition(ending);
    for(int k = 1; k <= 9; k++) {
        output->getPixel(endx*10+k, (endy+1)*10).l = 1.0;
        //endx++;
    }
    return output;
}