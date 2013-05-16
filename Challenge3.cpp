/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3
 */

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

char line[1000000];
vector<char> symbol;
vector<pair<int, string> > scenes;
map<string, int> idScene;


void processScript(){
  int i, j, id;

  symbol.clear();
  scenes.clear();
  idScene.clear();

  fgets(line, 1000000, stdin);

  symbol.push_back(line[0]);
  j=1;

  for(i=2; line[i] != '\n'; i++){
    if(line[i] == '.' || line[i] == '<' || line[i] == '>'){
      symbol.push_back(line[i]);
      string scene(line+j, line+i);
      id = idScene[scene];
      if(id == 0){
	id = idScene.size();
	idScene[scene] = id;
      }
      scenes.push_back(pair<int, string>(id-1, scene));
      j=i+1;
    }
  }

  string scene(line+j, line+i);
  id = idScene[scene];
  if(id == 0){
    id = idScene.size();
    idScene[scene] = id;
  }
  scenes.push_back(pair<int, string>(id-1, scene));
}

void solve(){
  if(symbol[0] != '.'){
    puts("invalid");
    return ;
  }

  int i;
  bool valid = true;
  bool unique = true;
  bool canBefore = false;
  vector<bool> canAfter(scenes.size(), false);
  vector<bool> isBefore(scenes.size(), false);

  for(i=1; valid && i<symbol.size(); i++){
    if(scenes[i].first == scenes[i-1].first){
      valid = false;
    }
  }

  isBefore[0] = true;
  for(i=1; valid && i<symbol.size(); i++){
    if(symbol[i] == '<'){
      if(i > 1 && !canBefore){
	valid = false;
      }
      if(i > 1 && isBefore[scenes[i].first]){
	if(!canAfter[scenes[i].first]){
	  valid = false;
	}
	if(scenes[i-2].first != scenes[i].first){
	  unique = false;
	}
      }
      isBefore[scenes[i].first] = true;
      swap(scenes[i], scenes[i-1]);
    } else if(symbol[i] == '>'){
      canBefore = true;
      if(isBefore[scenes[i].first]){
	valid = false;
      }
      isBefore[scenes[i].first] = true;
      canAfter[scenes[i].first] = true;
    } else {
      if(isBefore[scenes[i].first]){
	valid = false;
      }
      isBefore[scenes[i].first] = true;
    }
  }

  if(!valid){
    puts("invalid");
  } else if(!unique){
    puts("valid");
  } else {
    for(i=0; i<scenes.size(); i++){
      if(i == 0){
	printf("%s", scenes[i].second.c_str());
      } else if(scenes[i].first != scenes[i-1].first){
	printf(",%s", scenes[i].second.c_str());
      }
    }
    puts("");
  }
}

int main(){
  int i, N;
  
  scanf("%d\n", &N);
  while(N--){
    processScript();
    solve();
  }

  return 0;
}
