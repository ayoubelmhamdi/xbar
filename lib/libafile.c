#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80

void readFirstLine(char *file, char *line) {
  FILE *fp = NULL;
  fp = fopen(file, "r");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  fscanf(fp, "%[^\n]", line);
  fclose(fp);
}

void readOneLine(char *file, char *s, int N) {
  FILE *fp = NULL;
  fp = fopen(file, "r");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  char line[MAXLINE];
  int i = 0;
  int x = 0;

  while (fgets(line, sizeof(line), fp)) {
    i++;
    if (i == N) {
      sscanf(line, "%*s %d", &x);
      strcpy(s, line);
    }
  }
  fclose(fp);
}

int fgetint(char *file) {
  FILE *fp = NULL;
  fp = fopen(file, "r");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  char line[MAXLINE];
  int i = 0;
  int x = 0;

  fgets(line, sizeof(line), fp);
  sscanf(line, "%d", &x);
  fclose(fp);
  return x;
}

void fgetString(char *file, char *s) {
  FILE *fp = NULL;
  fp = fopen(file, "r");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  fgets(s, sizeof(s), fp);
  fclose(fp);
}

// run shell command and get first output from stdout
void stdoutOneline(char *file, char *s) {
  FILE *popen(const char *command, const char *mode);
  int pclose(FILE * stream);
  FILE *fp = NULL;
  fp = popen(file, "r");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  fgets(s, sizeof(s), fp);
  pclose(fp);
}

void writeIntToFile(char *file, int *x) {
  FILE *fp = NULL;
  fp = fopen(file, "w");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%d\n", *x);
  fclose(fp);
}

void writeTowIntToFile(char *file, int *x, int *y) {
  FILE *fp = NULL;
  fp = fopen(file, "w");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%d %d\n", *x, *y);
  fclose(fp);
}

void writeSixIntToFile(char *file, int *x1, int *x2, int *x3, int *x4, int *x5, int *x6) {
  FILE *fp = NULL;
  fp = fopen(file, "w");
  if (fp == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%d %d %d %d %d %d\n", *x1, *x2, *x3, *x4, *x5, *x6);
  fclose(fp);
}
