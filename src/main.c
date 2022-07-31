#include "util.h"
#include <stdio.h>

int main(int argv, char *argc[]) {
  view_output();
  view_nvim();
  // view_pbattery();
  // view_sbattery();    printf("|");
  view_ip();
  printf("|");
  view_cpu();
  printf("|");
  view_ram();
  printf("|");
  view_time();

  return 0;
}
