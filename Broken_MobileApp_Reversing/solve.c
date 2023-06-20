#include<stdio.h>
#include<string.h>

int main(void) {
  unsigned char secret[] = "\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x1f\x75\x25\x25\x25\x25\x05";
  char xorkey[] = "}p}dTZF@vl@RvqZ>T[[[[{~}";
  int i;
  char flag[24];

  for (i = 0; i < 24; i++) {
    flag[i] = secret[i] ^ xorkey[i];
  }
  flag[25] = '\0';

  printf("[!] Found flag: %s\n", flag);

  return 0;
}