#include <dirent.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define SIZE 1000

void rea(char *name, int *nFLUGS, char *pattern);
void what_is_flag(int argc, char **flags, char *file_name, int *nFLUGS,
                  char *pattern);

int main(int argc, char **flags) {
  if (argc != 1) {
    int *nFLUGS = malloc(sizeof(int) * 20);
    char *file_name = malloc(sizeof(char) * SIZE);
    char *pattern = malloc(sizeof(char) * SIZE);
    for (int i = 0; i < SIZE; i++) {
      pattern[i] = 0;
    }
    for (int i = 0; i < SIZE; i++) {
      file_name[i] = 0;
    }
    for (int i = 0; i < 20; i++) {
      nFLUGS[i] = 0;
    }
    what_is_flag(argc, flags, file_name, nFLUGS, pattern);
    free(nFLUGS);
    free(file_name);
    free(pattern);
  }
  return 0;
}
void what_is_flag(int argc, char **flags, char *file_name, int *nFLUGS,
                  char *pattern) {
  struct option opts;
  opts.flag = 0;
  opts.has_arg = 0;
  opts.name = 0;
  opts.val = 0;
  int tmpL = 0;
  char flag = 0;
  int Ecount = 0;
  int opterr = 0;
  char tmpF[100];
  int countF = 0;
  int i = 0;

  while (flag != -1) {
    flag = getopt_long(argc, flags, "cvtnlfbihose", &opts, NULL);

    if (flag == 'n') {
      nFLUGS[0] = 1;
    }
    if (flag == 's') {
      nFLUGS[1] = 1;
    }
    if (flag == 't') {
      nFLUGS[2] = 1;
    }
    if (flag == 'e') {
      nFLUGS[3] = 1;
      strcat(pattern, flags[optind]);
      strcat(pattern, "|");
      Ecount++;
    }
    if (flag == 'b') {
      nFLUGS[4] = 1;
    }
    if (flag == 'i') {
      nFLUGS[5] = 1;
    }
    if (flag == 'v') {
      nFLUGS[6] = 1;
    }
    if (flag == 'c') {
      nFLUGS[7] = 1;
    }
    if (flag == 'l') {
      nFLUGS[9] = 1;
    }
    if (flag == 'h') {
      nFLUGS[10] = 1;
    }
    if (flag == 's') {
      nFLUGS[11] = 1;
    }
    if (flag == 'f') {
      nFLUGS[12] = 1;
      strcat(tmpF, flags[optind]);
      countF = 1;
    }
    if (flag == 'o') {
      nFLUGS[13] = 1;
    }
    i++;
  }
  if (argc == 0) {
    perror("");
  } else {
    if (nFLUGS[12] == 0) {
      if (nFLUGS[3] == 0) {
        strcat(pattern, flags[optind]);
        optind++;
      } else {
        pattern[strlen(pattern) - 1] = '\0';
      }
    } else {
      tmpL = 1;
      FILE *fpPattern;
      fpPattern = fopen(tmpF, "r");
      if (fpPattern != NULL) {
        char *strPattenr = malloc(sizeof(char) * SIZE);
        while (!feof(fpPattern)) {
          if (fgets(strPattenr, SIZE, fpPattern) != NULL) {
            strcat(pattern, strPattenr);
            if (pattern[strlen(pattern) - 1] == '\n') {
              pattern[strlen(pattern) - 1] = '|';
            }
          }
        }
        free(strPattenr);
        fclose(fpPattern);
      } else {
        perror("");
      }
    }
    if (pattern[strlen(pattern) - 1] == '|') {
      pattern[strlen(pattern) - 1] = '\0';
    }
    if (argc - optind - Ecount > 1 + tmpL && nFLUGS[10] != 1) {
      nFLUGS[8] = 1;
    }
    FILE *fpPattern;
    int x = 0;
    if (Ecount >= 1 && countF >= 1) {
      Ecount = Ecount - 1;
      x = 1;
    }
    for (int i = optind + Ecount + tmpL; i < argc - x; i++) {
      fpPattern = fopen(flags[i], "r");
      if (fpPattern != NULL) {
        rea(flags[i], nFLUGS, pattern);

        fclose(fpPattern);
      } else {
        perror(flags[i]);
      }
    }
  }
}

void rea(char *file_name, int *nFLUGS, char *pattern) {
  char *str = malloc(sizeof(char) * SIZE);
  char *COPYstr = malloc(sizeof(char) * SIZE);
  regex_t reg;
  regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE);
  if (nFLUGS[5] == 1) {
    regfree(&reg);
    regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE | REG_ICASE);
  }
  regmatch_t pmatch[10];
  size_t nmatch = 1;
  FILE *fp;
  int count = 0;

  int Regexcount = 0;
  int stutas;

  nFLUGS[19] = 0;

  fp = fopen(file_name, "r");
  if (fp == NULL) {
    if (nFLUGS[11] == 0) {
      perror(file_name);
    }
  } else {
    while (!feof(fp)) {
      if (fgets(str, SIZE, fp) != NULL) {
        count++;
        stutas = regexec(&reg, str, nmatch, pmatch, 0);
        int stttt;
        if (stutas == 0 && nFLUGS[6] != 1) {
          nFLUGS[19] = 1;
          Regexcount++;
          if (nFLUGS[7] == 0) {
            if (nFLUGS[8] == 1 && nFLUGS[13] == 0 && nFLUGS[9] == 0) {
              printf("%s", file_name);

              if (nFLUGS[10] == 0) {
                printf(":");
              }
            }
            if (nFLUGS[0] == 1 && nFLUGS[9] == 0 && nFLUGS[13] == 0) {
              printf("%d:", count);
            }

            if (nFLUGS[9] == 0) {
              if (nFLUGS[13] == 0) {
                printf("%s", str);
                if (str[strlen(str) - 1] != '\n') {
                  printf("\n");
                }

              } else {
                for (int j = 0; j < SIZE; j++) {
                  stttt = regexec(&reg, str, nmatch, pmatch, 0);

                  if (stttt == 0) {
                    if (nFLUGS[8] == 1) {
                      printf("%s", file_name);

                      if (nFLUGS[10] == 0) {
                        printf(":");
                      }
                    }
                    if (nFLUGS[0] == 1 && nFLUGS[9] == 0) {
                      printf("%d:", count);
                    }
                    for (int i = pmatch->rm_so; i < pmatch->rm_eo; i++) {
                      printf("%c", str[i]);
                    }
                    printf("\n");
                    for (int i = 0; i < pmatch->rm_eo; i++) {
                      str[i] = ' ';
                    }
                  }
                }
              }
            } else {
              if (nFLUGS[10] == 0 && nFLUGS[9] == 0) {
                printf("\n");
              }
            }
          }
        }

        if (nFLUGS[6] == 1) {
          if (stutas != 0) {
            nFLUGS[19] = 1;
            Regexcount++;
            if (nFLUGS[13] == 0) {
              if (nFLUGS[7] == 0) {
                if (nFLUGS[8] == 1 && nFLUGS[9] == 0) {
                  printf("%s", file_name);
                }
                if (nFLUGS[10] == 0 && nFLUGS[8] == 1 && nFLUGS[9] == 0) {
                  printf(":");
                }
                if (nFLUGS[0] == 1 && nFLUGS[9] == 0) {
                  printf("%d:", count);
                }
                if (nFLUGS[9] == 0) {
                  printf("%s", str);
                  if (str[strlen(str) - 1] != '\n') {
                    printf("\n");
                  }
                } else {
                  if (nFLUGS[9] == 0) {
                    printf("\n");
                  }
                }
              }
            }
          }
        }
      }
    }
    if ((nFLUGS[9] == 1 && nFLUGS[19] == 1) ||
        (nFLUGS[8] == 1 && nFLUGS[7] == 1 && nFLUGS[19] == 1) ||
        (nFLUGS[8] == 1 && nFLUGS[7] == 1 && nFLUGS[19] == 0 &&
         nFLUGS[9] == 0)) {
      printf("%s", file_name);
    }
    if (nFLUGS[9] == 1 && nFLUGS[19] == 1) {
      printf("\n");
    }
    if ((nFLUGS[10] == 0 && nFLUGS[8] == 1 && nFLUGS[19] == 1 &&
         nFLUGS[9] == 0 && nFLUGS[13] == 0 && nFLUGS[7] == 1) ||
        (nFLUGS[9] == 0 && nFLUGS[7] == 1 && nFLUGS[10] == 0 &&
         nFLUGS[8] == 1)) {
      printf(":");
    }
    if (nFLUGS[7] == 1 && nFLUGS[9] == 0) {
      printf("%d\n", Regexcount);
    }
    fclose(fp);
    regfree(&reg);
  }
  free(str);
  free(COPYstr);
}