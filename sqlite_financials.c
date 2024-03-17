/**
  * @file sqlite_financials.c
  */

#include "sqlite_financials.h"

void version() {
        printf("%s\n", sqlite3_libversion());
}
