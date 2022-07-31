#include "util.h"
#include "ayoub/file.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int ram() {
  FILE *file = fopen("/proc/meminfo", "r");
  char sfile[256];
  // (tot - free - (buf + cach+srec))
  int total = 0;
  int free = 0;
  int buffuer = 0;
  int cache = 0;
  int shem = 0;
  int srec = 0;

  int i = 0;
  while (fgets(sfile, sizeof(sfile), file)) {
    i++;
    /* if (i == 3) { */
    /*   sscanf(sfile, "%*s %d", &x); */
    /* } */

    switch (i) {
    case 1:
      sscanf(sfile, "%*s %d", &total);
      break;
    case 2:
      sscanf(sfile, "%*s %d", &free);
      break;
    case 4:
      sscanf(sfile, "%*s %d", &buffuer);
      break;
    case 5:
      sscanf(sfile, "%*s %d", &cache);
      break;
    case 21:
      sscanf(sfile, "%*s %d", &shem);
      break;
    case 24:
      sscanf(sfile, "%*s %d", &srec);
      break;
    }
  }

  fclose(file);
  return (total - free - (buffuer + cache + srec)) / 1024;
}

int cpu() {
  // https://rosettacode.org/wiki/Linux_CPU_utilization
  char new[MAX], old[MAX];

  readFirstLine("/tmp/ayoub/cpu", old);
  int old_total, old_idle;
  sscanf(old, "%d %d", &old_total, &old_idle);

  readFirstLine("/proc/stat", new);
  int a2, a3, a4, a5, a6, a7;
  sscanf(new, "%*[^0-9] %d %d %d %d %d %d %%[^\n]", &a2, &a3, &a4, &a5, &a6, &a7);

  int total = 0, idle = a5;
  total = a2 + a3 + a4 + a5 + a6 + a7;
  writeTowIntToFile("/tmp/ayoub/cpu", &total, &idle);
  return (1 - (float)(idle - old_idle) / (total - old_total)) * 100;
}

void date(char *s) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  /* printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec); */
  strcpy(s, "");

  char hour[80], min[80], sec[80], day[80], month[80];
  sprintf(hour, "%02d", tm.tm_hour);
  sprintf(min, "%02d", tm.tm_min);
  sprintf(sec, "%02d", tm.tm_sec);
  sprintf(day, "%02d", tm.tm_mday);
  sprintf(month, "%02d", tm.tm_mon);
  strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(s, day), "/"), month), "/2020 "), hour), ":"), min), ":"), sec);
}

int pbattery() {
  char file[MAX] = "/sys/class/power_supply/axp288_fuel_gauge/capacity";
  return fgetint(file);
}

void sbattery(char *s) {
  //     
  char s2[MAX];
  fgetString("/sys/class/power_supply/axp288_fuel_gauge/status", s2);
  if (strncmp(s2, "F", 1) == 0) {
    strcpy(s, "F");
  } else if (strncmp(s2, "D", 1) == 0) {
    strcpy(s, "N");
  } else if (strncmp(s2, "C", 1) == 0) {
    strcpy(s, "Y");
  } else {
    strcpy(s, "x");
  }
}

void nvim() {
  //     
  char s_in[MAX] = "pgrep nvim";
  char s_out[MAX];
  stdoutOneline(s_in, s_out);

  if (s_out[0] != '\0') {
    printf("nvim |");
  }
}

void ip() {
    char s[15];
    myip(s);
    printf(" %s ", s);
}

void output() {
  char s[200];
  char old[200];

  readFirstLine("/tmp/ayoub/status", old);
  int a = strlen(s) < 100 ? strlen(old) : 100;
  strncpy(s,old, a);
  printf("%10s | ",s);
}

