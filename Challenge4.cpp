/* Francisco José Sánchez Sánchez
 *
 * francjsanchez@gmail.com
 *
 * Tuenti Challenge 3
 * 
 * Solution (~ 12 minutes):
 * There are 2^31 - 100 = 2147483548 numbers. 2147483548 / 28 = 76695841,
 * so I sort it in 28 blocks of 76695841 numbers and I write it in a file.
 * Later, with 28 pointers to blocks, I check if exists each number form 0
 * to 2^31 -1.
 */

#include <stdio.h>

int main(){
  int missingNumber[] = {7303,8243,9854,12009,12793,14346,14680,15093,17857,19375,20084,22525,23054,23250,30197,36318,39334,40018,48871,50654,50721,54592,59393,61063,63138,63241,64549,66259,69103,76165,76685,81278,82333,83089,84011,85250,88429,90254,90271,90981,91165,93661,94654,99088,99146,99612,2147386534,2147387515,2147390868,2147393636,2147394767,2147394776,2147399790,2147404278,2147410474,2147411181,2147411772,2147414329,2147414440,2147415261,2147415351,2147416362,2147416780,2147416956,2147418296,2147419403,2147419606,2147421475,2147421911,2147424275,2147424781,2147425007,2147425958,2147427008,2147429783,2147430753,2147434866,2147436265,2147439441,2147442423,2147443250,2147454548,2147455603,2147457507,2147463138,2147465967,2147466563,2147466673,2147468436,2147470025,2147470723,2147470869,2147471405,2147474036,2147474185,2147476664,2147478255,2147478824,2147480866,2147480904};
  int N, nth;
  
  scanf("%d", &N);
  while(N--){
    scanf("%d", &nth);
    printf("%d\n", missingNumber[nth-1]);
  }
  
}

/*
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define SZ 2147483647
#define N 76695841
#define M 28
#define R 100000

unsigned int a[N];
unsigned int b[M][R];

int main(){
  unsigned int i, j, k;

  // sort
  FILE *orgFile = fopen("integers", "rb");
  FILE *srtFile = fopen("sortedIntegers", "wb");
  for(i=0; i<M; i++){
    printf("Sorting %d\n", i+1);
    fread(a, 4, N, orgFile);
    sort(a, a+N);
    fwrite(a, 4, N, srtFile);
  }
  fclose(orgFile);
  fclose(srtFile);

  // check if exist
  puts("Finding numbers...");
  int index[M];
  int readings[M];
  for(i=0; i<M; i++){
    index[i] = R;
    readings[i] = 0;
  }
  FILE *srtFile = fopen("sortedIntegers", "rb");
  for(i=0; i<=SZ; i++){
    for(j=0; j<M; j++){
      if(readings[j] == 767 && index[j] == 95841){
	// end of block
	continue;
      }
      if(index[j] == R){
	// read a block
	fseek(srtFile, 0, SEEK_SET);
	for(k=0; k<j; k++){
	  fseek(srtFile, 4*N, SEEK_CUR);
	}
	fseek(srtFile, 4*readings[j]*100000, SEEK_CUR);
	fread(b[j], 4, 100000, srtFile);
	readings[j]++;
	index[j] = 0;
      }
      if(b[j][index[j]] == i){
	index[j]++;
	break;
      }
    }
    // not exists
    if(j==M){
      printf("%d\n", i);
    }
  }
  fclose(srtFile);
  
  return 0;
}
*/
