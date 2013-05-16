/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3
 */

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

#define BLOCK 20

// Index to access to vector of suggestions
map<string, int> indexMap;

// Groups with the same letters
vector<vector<string> > suggest;

// Suggest processed
vector<bool> processed;

// Suggestion numbers
int N;

void read(){
  int index = 1, i;
  char line[100];
  string na, file, originalWord, sortedWord;

  cin.getline(line, 100);
  cin >> file;
  cin.getline(line, 100);
  cin.getline(line, 100);
  cin >> N;
  cin.getline(line, 100);
  cin.getline(line, 100);

  fstream f(file.c_str(), fstream::in);

  while(f >> originalWord){
    sortedWord = originalWord;
    sort(sortedWord.begin(), sortedWord.end());
    i = indexMap[sortedWord];

    // Not in indexMap
    if(i == 0){
      i = index;
      indexMap[sortedWord] = i;
      suggest.push_back(vector<string>());
      index++;
    }

    suggest[i-1].push_back(originalWord);
  }

  processed = vector<bool>(indexMap.size(), false);
}

void processSuggestion(int index){
  vector<string>::iterator it;
  
  // In alphabetical order
  sort(suggest[index].begin(), suggest[index].end());

  // Remove duplicates
  it = unique(suggest[index].begin(), suggest[index].end());
  suggest[index].resize(distance(suggest[index].begin(), it));

  processed[index] = true;
}

void solve(){
  int i, index;
  string originalWord, sortedWord;
  while(N--){
    cin >> originalWord;
    sortedWord = originalWord;
    sort(sortedWord.begin(), sortedWord.end());
    index = indexMap[sortedWord] -1;

    if(index == -1){
      // Not in indexMap, therefore no suggestion
      cout << originalWord << " ->" << endl;
    } else {
      // Suggestions
      if(!processed[index]){
	processSuggestion(index);
      }
      cout << originalWord << " ->";
      for(i=0; i<suggest[index].size(); i++){
	if(originalWord != suggest[index][i]){
	  cout << " " << suggest[index][i];
	}
      }
      cout << endl;
    }
  }
}

using namespace std;
int main(){

  read();
  solve();

  return 0;
}
