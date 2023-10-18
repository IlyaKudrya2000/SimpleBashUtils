#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 100
void rea(char **flags, int *nFLUGS, int optind, int argc);
void what_is_flag(int argc, char **flags, char *file_name, int *nFLUGS);
int main(int argc, char **flags) {
  int *nFLUGS = malloc(sizeof(int) * 6);
  char *file_name = malloc(sizeof(char) * SIZE);
  for (int i = 0; i < SIZE; i++) {
    file_name[i] = 0;
  }
  for (int i = 0; i < 6; i++) {
    nFLUGS[i] = 0;
  }
  what_is_flag(argc, flags, file_name, nFLUGS);

  rea(flags, nFLUGS, optind, argc);

  free(nFLUGS);
  free(file_name);

  return 0;
}
void what_is_flag(int argc, char **flags, char *file_name, int *nFLUGS) {
  int count = 0;
  char flag = 0;
  while (flag != -1) {
    flag = getopt(argc, flags, "evtnbs");
    if (flag == 'n') {
      nFLUGS[0] = 1;
      count++;
    }
    if (flag == 's') {
      nFLUGS[1] = 1;
      count++;
    }
    if (flag == 't') {
      nFLUGS[2] = 1;
      count++;
    }
    if (flag == 'e') {
      nFLUGS[3] = 1;
      count++;
    }
    if (flag == 'b') {
      nFLUGS[4] = 1;
      count++;
    }
  }
  strcpy(file_name, flags[optind]);
}

void rea(char **flags, int *nFLUGS, int optind, int argc) {
  char *str = malloc(sizeof(char) * SIZE);
  for (int i = 0; i < SIZE; i++) {
    str[i] = 0;
  }
  for (int i = optind; i < argc; i++) {
    FILE *fp;

    fp = fopen(flags[i], "r");

    if (fp == NULL) {
      perror("");
    } else {
      char c;
      char *secand = malloc(sizeof(char) * 2);
      for (int i = 0; i < 2; i++) {
        secand[i] = 0;
      }
      secand[0] = '\n';
      int Bcount = 1;
      int Ncount = 1;
      int firstONE = 1;
      int pecat = 1;
      int tFUK = 0;
      char tmpN = 0;
      char tub = 9;
      while (!feof(fp)) {
        if ((c = fgetc(fp)) != EOF) {
          if (tmpN == '\n') {
            firstONE = 1;
          }
          if (nFLUGS[1] == 1) {
            if ((secand[0] != '\n' || secand[1] != '\n' || c != '\n')) {
              pecat = 1;
            } else {
              pecat = 0;
            }
            secand[1] = secand[0];
            secand[0] = c;
          }

          if (nFLUGS[4] == 1) {
            if (c != '\n' && firstONE == 1) {
              firstONE = 0;
              if (Bcount < 10) {
                printf("     %d%c", Bcount, tub);
              } else {
                printf("    %d%c", Bcount, tub);
              }
              Bcount++;
            }
          }
          if ((nFLUGS[0] == 1 && (nFLUGS[1] != 1 || pecat == 1)) &&
              nFLUGS[4] == 0) {
            if (firstONE == 1) {
              firstONE = 0;
              if (Ncount < 10) {
                printf("     %d%c", Ncount, tub);
              } else {
                printf("    %d%c", Ncount, tub);
              }
              Ncount++;
            }
          }
          if (nFLUGS[3] == 1) {
            if (c == '\n' && pecat == 1) {
              printf("$");
            }
          }
          if (nFLUGS[2] == 1) {
            if (c == '\t' && pecat == 1) {
              printf("^I");
              tFUK = 1;
            }
          }
          tmpN = c;
          if (pecat == 1 && tFUK != 1) {
            printf("%c", c);
          }
          tFUK = 0;
        }
      }
      free(secand);
      fclose(fp);
    }

    free(str);
  }
}