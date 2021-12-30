#include <iostream>
#include <vector>

#define R 14
#define C 17

using namespace std;

class PathFinder{
public:
    pair<int,int>start;
    pair<int,int>goal;
    vector<vector<pair<int,int>>>parents;
    vector<vector<char>>maze;
    pair<int,int>unvisited = {-1,-1};

    PathFinder(vector<vector<char>>m,pair<int,int>s,pair<int,int>g){
        start = s;
        goal = g;
        maze = m;

        for(int i = 0; i < R; i++){
            parents.emplace_back(C,unvisited);
        }
        parents[start.first][start.second] = {-111,-111};
    }
    bool isVisited(pair<int,int>curr){
        if(parents[curr.first][curr.second] == unvisited)return false;
        return true;
    }

    bool isValid(pair<int,int>curr){
        if (curr.first < 0 || curr.first >= R || curr.second < 0 || curr.second >= C || maze[curr.first][curr.second] == 'x')
            return false;
        return true;
    }



    void DFS(pair<int,int>curr){

        pair<int,int>down = {curr.first+1, curr.second};
        pair<int,int>right =     {curr.first, curr.second + 1};
        pair<int,int>up =     {curr.first-1, curr.second};
        pair<int,int>left =     {curr.first, curr.second - 1};

        //Go DRUL

        //DOWN
        if(isValid(down) && !isVisited(down) && !isVisited(goal)){
            parents[down.first][down.second] = curr;
            DFS(down);
        }


        //RIGHT
        if(isValid(right) && !isVisited(right) && !isVisited(goal)){
            parents[right.first][right.second] = curr;
            DFS(right);
        }

        //UP
        if(isValid(up) && !isVisited(up) && !isVisited(goal)){
            parents[up.first][up.second] = curr;
            DFS(up);
        }

        //LEFT
        if(isValid(left) && !isVisited(left) && !isVisited(goal)){
            parents[left.first][left.second] = curr;
            DFS(left);
        }

    }

    void DFS(){
        DFS(start);

        if(!isVisited(goal)){
            cout << "NO PATH!";
        }
        else{
            pair<int,int>curr = parents[goal.first][goal.second];
            while(curr != start){
                maze[curr.first][curr.second] = '*';
                curr = parents[curr.first][curr.second];
            }
            for (int row = 0; row < R; row++){
                for (int col = 0; col < C; col++){
                    cout << maze[row][col];
                }
                cout << endl;
            }
        }
    }
};

int main()
{

    vector<vector<char>>maze;

    string input;
    for(int i = 0; i < R; i++){
        getline(cin,input);
        vector<char>tmp;
        for (int j = 0; j < C; j++){
            char x = input[j];
            tmp.push_back(x);
        }maze.push_back(tmp);
    }

    pair<int,int>start;pair<int,int>goal;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (maze[i][j] == 'S'){
                start = make_pair(i,j);
            }
            else if (maze[i][j] == 'G'){
                goal = make_pair(i, j);
            }
        }
    }

    PathFinder f(maze,start,goal);
    f.DFS();
    return 0;
}
