//  Copyright © 2017 Dougy Ouyang. All rights reserved.

#include <iostream>

using namespace std;
int n, m, k;
int mat[50][50];
bool mat2[50][50], fi=false;

void print()
{
    int i, j;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(mat2[i][j])
                cout << i+1 << " " << j+1 << endl;
        }
    }
}

void mark(int x, int y, int dir)
{
    if(x<0 || y<0 || x>=n || y>=m)
        return;
    if(!dir)
        mat[x][y]--;
    else{
        mat[x][y]++;
    }
}

void rec(int x, int y, int mine, bool firsthalf)
{
    int i, j;
    bool finish=true;
    //base case
    if(fi)
        return;
        
    if (x>0 && x<n && y>0 && y<m)
        if(mat[x-1][y-1]!=0)
            return;

    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(mat[i][j]>0)
                finish=false;
            if(mat[i][j]<0)
                return;
        }
    }

    if(mine==k && finish){
        print(), fi=true;
        return;
    }
    if(mine>=k)
        return;
    //advanced cutting algorithm and greedy searching
    y++;
    if(y==m/2 && firsthalf)
        y=0, x++;
    if(y==m)
        y=m/2, x++;
    if(x==n && firsthalf)
        x=0, y=m/2, firsthalf=false;
    if(x==n && !firsthalf)
        return;
    //mark mine and mark surroundings
    mat2[x][y]=true, mark(x, y, 0);
    mark(x+1, y, 0), mark(x-1, y, 0), mark(x, y+1, 0), mark(x, y-1, 0);
    mark(x+1, y+1, 0), mark(x+1, y-1, 0), mark(x-1, y+1, 0), mark(x-1, y-1, 0);
    //search
    rec(x, y, mine+1, firsthalf);
    //undo
    mat2[x][y]=false, mark(x, y, 1);
    mark(x+1, y, 1), mark(x-1, y, 1), mark(x, y+1, 1), mark(x, y-1, 1);
    mark(x+1, y+1, 1), mark(x+1, y-1, 1), mark(x-1, y+1, 1), mark(x-1, y-1, 1);
    //search
    rec(x, y, mine, firsthalf);
}

int main()
{
    int i, j;
    
    cin >> n >> m >> k;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            cin >> mat[i][j];
        }
    }
    
    rec(0, -1, 0, true);
    
    if(!fi)
        cout << "NO SOLUTION" << endl;
    
    return 0;
}
