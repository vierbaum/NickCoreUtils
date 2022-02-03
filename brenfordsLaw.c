#include <stdio.h>

int main(){
  int numbers[9] = {0};
  int c;
  char comma = 1;

  while ((c = getchar()) != EOF){
    if(comma == 1){
      numbers[c - 49] += 1;
      comma = 0;
      //printf("N: C:%c, C-:%i NUM:%i\n", c, c -49, numbers[c - 49]);
    }
    if (c == ',')
      comma = 1;
  }


  for(int i = 0; i <= 8; i++)
    printf("%i:%i\n", i + 1, numbers[i]);
  return 0;
}
