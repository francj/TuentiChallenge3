/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3, Challenge 5
 * 
 * Solution: Backtracking using DFS and pruning when the current gemsCollected
 * + get the maximum value of gems in the rest of steps < current solution.
 */

#include <stdio.h>
#include <sstream>
#include <string.h>
#include <algorithm>
using namespace std;

int N, M, X, Y, Z, G, maxGemsCollected;
int grid[100][100];
int visited[100][100];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int gemsBound[16000];

void read(){
  int i, x, y, v;
  char line[16000];
  stringstream ss;

  // M,N
  fgets(line, 16000, stdin);
  for(i=0; line[i]!=','; i++);
  line[i] = ' ';
  ss.str(line);
  ss >> M >> N;

  // X,Y
  fgets(line, 16000, stdin);
  for(i=0; line[i]!=','; i++);
  line[i] = ' ';
  ss.str(line);
  ss >> X >> Y;

  // Z
  scanf("%d\n", &Z);

  // G
  scanf("%d\n", &G);

  // grid
  memset(grid, 0, sizeof(grid));
  fgets(line, 16000, stdin);
  for(i=0; line[i]!='\n'; i++){
    if(line[i] == ',' || line[i] == '#'){
      line[i] = ' ';
    }
  }
  ss.str(line);
  i=0;
  while(ss >> x >> y >> v){
    grid[y][x] = v;
    gemsBound[i] = v;
    i++;
  }
}

void dfs(int x, int y, int gemsCollected, int seconds){
  if(seconds == Z+1){
    maxGemsCollected = max(maxGemsCollected, gemsCollected);
  } else if(gemsCollected + gemsBound[max(0, G-(Z+1-seconds))] > maxGemsCollected){
    gemsCollected += grid[y][x];
    visited[y][x] = 1;
    for(int i=0; i<4; i++){
      if(x+dx[i] < M && x+dx[i] >=0 && y+dy[i] < N && y+dy[i] >=0 && visited[y+dy[i]][x+dx[i]] == 0){
	dfs(x+dx[i], y+dy[i], gemsCollected, seconds+1);
      }
    }
    gemsCollected -= grid[y][x];
    visited[y][x] = 0;
  }
}

void solve(){
  sort(gemsBound, gemsBound+G);
  for(int i=G-2; i>=0; i--) gemsBound[i] += gemsBound[i+1];
  memset(visited, 0, sizeof(visited));
  maxGemsCollected = 0;
  dfs(X, Y, 0, 0);
  printf("%d\n", maxGemsCollected);
}

int main(){
 
  int T;
  
  scanf("%d\n", &T);
  while(T--){
    read();
    solve();
  }

  return 0;
}
