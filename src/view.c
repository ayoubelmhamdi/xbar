/* util.c build principal function */
/* view.c build theme with %03s */

#include "util.h"
#include <stdio.h>
#include <string.h>

void view_ram() {
  char s[MAX];
  sprintf(s, "%d", ram());
  printf(" %04sMb ", s);
}

void view_cpu() {
  char s[MAX];
  sprintf(s, "%d", cpu());
  printf("%03s%% ", s);
}

void view_time() {
  char s[MAX];
  date(s);
  printf(" %s ", s);
}

void view_pbattery(){
  char s[MAX];
  sprintf(s, "%d", pbattery());
  printf("%03s%%", s);
}

void view_sbattery(){
  char s[MAX];
  sbattery(s);
  printf(" %01s ", s);
}

void view_ip(){
  ip();
}

void view_nvim(){
  nvim();
}

void view_output(){
  output();
}

