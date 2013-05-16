/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3, Challenge 9
 * 
 * Solution: Check how long I will survive with n soldiers, 0 <= n <= W.
 * Tc = (W*H-W)/(W-n)+1 is the time I have before the Zorg invade me, so
 * every Tc seconds I use the Crematorium as long as I have gold enough.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;

long long W, H, S, C, G;

void read(){
  scanf("%Ld %Ld %Ld %Ld %Ld", &W, &H, &S, &C, &G);
}

void solve(){
  long long i, t, ans = 0, crematorium;
  
  if(W*S<=G){
    puts("-1");
  } else {
    for(i=0; i*S <= G; i++){
      crematorium = 0;
      for(t=0; C <= (G-i*S-C*crematorium); t += (W*H-W)/(W-i)+1 ){
	crematorium++;
      }
      t += (W*H-W)/(W-i)+1;
      ans = max(ans, t);
    }
    printf("%Ld\n", ans);
  }
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
