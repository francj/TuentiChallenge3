/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3, Challenge 6
 * 
 * Solution: transform the map into a graph and run Dijkstra's algorithm.
 */

#include <stdio.h>
#include <string.h>
#include <vector>
#include <math.h>

using namespace std;

struct node{
  int x, y;
  double cost;
};


typedef vector<struct node> v;
typedef vector<v> vv;
typedef vector<vv> vvv;

int W, H, S, T, startX, startY, exitX, exitY;
char cave[10000][10000];
vvv graph;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

void read(){
  int i, j, k;

  scanf("%d %d %d %d\n", &W, &H, &S, &T);
  for(i=0; i<H; i++){
    fgets(cave[i], 10000, stdin);
    for(k=j=0; j<W; j++){
      if(cave[i][k] != '#' && cave[i][k] != 'X' && cave[i][k] != 'O'){
	cave[i][j] = '.';
	k+=2;
      } else {
	cave[i][j] = cave[i][k];
	k++;
      }
    }
  }
}

bool canMove(int x, int y){
  return y < H && y >=0 && x < W && x >=0;
}

void makeGraph(){
  int i, j, k, x, y, cost;
  graph = vvv(H, vv(W, v()));
  for(i=0; i<H; i++){
    for(j=0; j<W; j++){
      if(cave[i][j] == '.'){
	for(k=0; k<4; k++){
	  if(canMove(j+dx[k], i+dy[k]) && cave[i+dy[k]][j+dx[k]] == '#'){
	    break;
	  }
	}
	if(k<4){
	  for(k=0; k<4; k++){
	    if(canMove(j+dx[k], i+dy[k]) && cave[i+dy[k]][j+dx[k]] != '#'){
	      x = j;
	      y = i;
	      cost = 0;
	      while(canMove(x, y) && cave[y][x] == '.'){
		x += dx[k];
		y += dy[k];
		cost++;
	      }
	      if(canMove(x, y) && cave[y][x] != 'X'){
		struct node n;
		if(cave[y][x] == 'O'){
		  n.x = x;
		  n.y = y;
		} else {
		  cost--;
		  n.x = x - dx[k];
		  n.y = y - dy[k];
		}
		n.cost = double(T) + double(cost)/double(S);
		graph[i][j].push_back(n);
	      }
	    }
	  }
	}
      } else if(cave[i][j] == 'X'){
	startX = j;
	startY = i;
	for(k=0; k<4; k++){
	  if(canMove(j+dx[k], i+dy[k]) && cave[i+dy[k]][j+dx[k]] != '#'){
	    x = j + dx[k];
	    y = i + dy[k];
	    cost = 1;
	    while(canMove(x, y) && cave[y][x] == '.'){
	      x += dx[k];
	      y += dy[k];
	      cost++;
	    }
	    if(canMove(x, y)){
	      struct node n;
	      if(cave[y][x] == 'O'){
		n.x = x;
		n.y = y;
	      } else {
		cost--;
		n.x = x - dx[k];
		n.y = y - dy[k];
	      }
	      n.cost = double(T) + double(cost)/double(S);
	      graph[i][j].push_back(n);
	    }
	  }
	}
      } else if(cave[i][j] == 'O'){
	exitX = j;
	exitY = i;
      }
    }
  }
}

int dijkstra(){
  vector<vector<double> > d(H, vector<double>(W, 1e16-1));
  vector<vector<bool> > mk(H, vector<bool>(W, 0));
  int i, j, k, l, nextX, nextY;
  double mx;
  d[startY][startX] = 0.0;
  for(k=0; k<W*H; k++){
    mx = 1e16;
    for(i=0; i<H; i++){
      for(j=0; j<W; j++){
	if(!mk[i][j] && d[i][j]<mx){
	  mx = d[i][j];
	  nextX = j;
	  nextY = i;
	}
      }
    }
    mk[nextY][nextX] = true;
    for(l=0; l<graph[nextY][nextX].size(); l++){
      for(i=0; i<H; i++){
	if(graph[nextY][nextX][l].y == i){
	  for(j=0; j<W; j++){
	    if(graph[nextY][nextX][l].x == j){
	      if(d[i][j] > d[nextY][nextX] + graph[nextY][nextX][l].cost){
		 d[i][j] = d[nextY][nextX] + graph[nextY][nextX][l].cost;
	      }
	    }
	  }
	}
      }
    }
  }
  return int(floor(0.5 + d[exitY][exitX]));
}

void solve(){
  makeGraph();
  printf("%d\n", dijkstra());
}

int main(){
 
  int N;
  
  scanf("%d\n", &N);
  while(N--){
    read();
    solve();
  }

  return 0;
}
