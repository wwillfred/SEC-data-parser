/**
  * @file sqlite_financials.h
  */

#ifndef _SQLITE_FINANCIALS_H_
#define _SQLITE_FINANCIALS_H_

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void open_database();

void add_net_income(int year, int quarter, int value);

void print_quarter(int year, int quarter);
int callback (void *, int, char **, char **);

void close_database();

#endif // _SQLITE_FINANCIALS_H_
