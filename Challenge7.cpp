/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3, Challenge 7
 * 
 * Solution: 1. Find all possible words using DFS and a prefix tree (trie).
 *           2. Select words optimally using dynamic programming, Knapsack problem.
 */

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct Trie{
  struct Trie *next[26];
  int isWord;

  Trie(){
    memset(next, 0, sizeof(next));
    isWord = false;
  }
};

int scoreChar[256], W, N, M;
char line[1000];
char board[50][50];
int cm[50][50];
int wm[50][50];
int dx[] = {1, -1, 0, 0, -1, 1, 1, -1};
int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};

Trie trie;

void read(){
  int i, j, sc;
  char ch;

  // scores
  fgets(line, 1000, stdin);
  for(i=0; line[i]; i++){
    if(line[i] == '{' || line[i] == '}' || line[i] == ',' || line[i] == '\'' || line[i] == ':'){
      line[i] = ' ';
    }
  }
  stringstream ss(line);
  while(ss >> ch >> sc){
    scoreChar[ch] = sc;
  }

  // W n m
  scanf("%d %d %d", &W, &N, &M);

  // board
  char cell[5];
  for(i=0; i<N; i++){
    for(j=0; j<M; j++){
      scanf("%s", cell);
      board[i][j] = cell[0];
      if(cell[1] == '1'){
	cm[i][j] = cell[2]-'0';
	wm[i][j] = 1;
      } else {
	cm[i][j] = 1;
	wm[i][j] = cell[2]-'0';
      }
    }
  }
  scanf("\n");
}

void addWord(char word[]){
  Trie *node = &trie;
  int i;
  for(i=0; word[i]; i++){
    if(node->next[word[i]-'A'] == 0){
      node->next[word[i]-'A'] = new struct Trie;
    }
    node = node->next[word[i]-'A'];
  }
  node->isWord = 1;
}

void makePrefixTree(){
  FILE *file = fopen("boozzle-dict.txt", "r");
  char word[20];
  while(fscanf(file, "%s", word)==1){
    addWord(word);
  }
  fclose(file);
}

bool canMove(int x, int y){
  return x>=0 && y>=0 && x<N && y<M;
}

int visited[50][50];
map<string, int> scoreWord;
char word[20];

void dfs(int x, int y, int depth, Trie *node, int sum, int mxWM){
  word[depth] = board[x][y];
  visited[x][y] = 1;
  if(node->isWord){
    word[depth+1] = '\0';
    string w(word);
    int score = sum * mxWM + depth + 1;
    if(scoreWord[w] < score){
      scoreWord[w] = score;
    }
  }
  int i, j, nX, nY;
  for(i=0; i<8; i++){
    nX = x+dx[i];
    nY = y+dy[i];
    if(canMove(nX, nY) && visited[nX][nY] == 0 && node->next[board[nX][nY]-'A'] != 0){
      dfs(nX, nY, depth+1, node->next[board[nX][nY]-'A'], sum + scoreChar[board[nX][nY]]*cm[nX][nY], max(mxWM, wm[nX][nY]));
    }
  }
  visited[x][y] = 0;
}

void solve(){
  int i, j;

  // find words
  scoreWord.clear();
  memset(visited, 0, sizeof(visited));
  for(i=0; i<N; i++){
    for(j=0; j<M; j++){
      if(trie.next[board[i][j]-'A'] != 0){
	dfs(i, j, 0, trie.next[board[i][j]-'A'], scoreChar[board[i][j]]*cm[i][j], wm[i][j]);
      }
    }
  }

  // select words
  int n = scoreWord.size();
  vector<int> weight(n);
  vector<int> value(n);
  map<string, int>::iterator it;
  for(i=0, it=scoreWord.begin(); it!=scoreWord.end(); it++, i++){
    weight[i] = (*it).first.size() + 1;
    value[i] = (*it).second;
  }

  vector<vector<int> > dp(n+1, vector<int>(W+1, 0));
  for(i=1; i<=n; i++){
    for(j=0; j<=W; j++){
      if(j >= weight[i-1]){
	dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i-1]] + value[i-1]);
      } else {
	dp[i][j] = dp[i-1][j];
      }
    }
  }
  
  printf("%d\n", dp[n][W]);
}

int main(){

  int T;
  scanf("%d\n", &T);
  makePrefixTree();
  while(T--){
    read();
    solve();
  }

  return 0;
}
