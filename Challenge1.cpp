#include <stdio.h>
#include <sstream>
#include <vector>
#define BUY_BITCOIN 0
#define BUY_EUROS 1
using namespace std;

long long budget;
char line[100000];
vector<long long> rate;

void read(){
  int i = 0;
  long long r;
  rate = vector<long long>();
  scanf("%Ld\n", &budget);
  fgets(line, 100000, stdin);
  stringstream ss(line);
  while(ss >> r) rate.push_back(r);
}

void solve(){
  int i = 0, action = BUY_BITCOIN;
  long long euros = budget, bitcoins = 0;
  while(i < rate.size()){
    if(action == BUY_BITCOIN){
      // Buy maximum number of bitcoins
      while(i+1 < rate.size() && rate[i+1] <= rate[i]) i++;
      // Only buy bitcoints only if later I can buy euros
      if(i+1 < rate.size()){
	bitcoins = euros / rate[i];
	euros = euros % rate[i];
      }
      action = BUY_EUROS;
    } else {
      // Buy maximum number of euros
      while(i+1 < rate.size() && rate[i+1] >= rate[i]) i++;
      euros += bitcoins * rate[i];
      action = BUY_BITCOIN;
    }
    i++;
  }
  printf("%Ld\n", euros);
}

int main(){
  int T;

  scanf("%d", &T);
  while(T--){
    read();
    solve();    
  }

  return 0;
}
