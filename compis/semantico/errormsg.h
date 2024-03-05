#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "errormsg.h"

bool anyErrors = 0;

void EM_newline(void) {
  lineNum++;
}

void EM_error(int pos, char *message,...) {
  va_list ap;
  anyErrors = 1;
  fprintf(stderr,"%d: ", pos);
  va_start(ap, message);
  vfprintf(stderr, message, ap);
  va_end(ap);
  fprintf(stderr,"\n");
}