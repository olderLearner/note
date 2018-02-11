#include <stdio.h>
int main() {

  short a = 10;
  int b = 100;
  long c = 1000;
  char d = 'X';

  int a_l = sizeof a;
  int b_l = sizeof b;

  printf("\"short int length\" = %d, \"int length\" = %d, \"long int length\" = %d, \"char length\" = %d\n", a_l, b_l, (int) sizeof(c), (int) sizeof(char));

  // 0000 0000 0000
  int type = 3;
  int volume = 5;
  int state = 1;
  int bs = state << 8 | volume << 4 | type;
  printf("type = %d, volume = %d, state = %d, bs = %d, hex = %x\n", type, volume, state, bs, bs);
  printf("t: %d, v: %d, s: %d\n", (bs & 0xf00) >> 8, (bs & 0x0f0) >>4, bs & 0xf);
  printf("t: %d, v: %d, s: %d\n", bs & 0xf, (bs >> 4)& 0xf, (bs >> 8) & 0xf);

  printf("div: %d\n", 40/3);

  int seq = 1024;
  int aw = 2;
  printf("ret = %d, seq = %d, ar = %d\n", seq << 2 | aw & 0x3, seq, aw);
	

  return 0;

}
