/**
  * @file sqlite_financials.c
  */

#include "sqlite_financials.h"


sqlite3 *db;
char *err_msg = 0;
int rc;

void open_database() {

	rc = sqlite3_open("corporate_financials.db", &db);

	if (rc != SQLITE_OK) {
	  fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
	}

	char *statement = "DROP TABLE IF EXISTS Q1_2023;"
			  "CREATE TABLE Q1_2023(cik TEXT, Net_Income INT);";

	rc = sqlite3_exec(db, statement, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {

	  fprintf(stderr, "SQL error in open_database(): %s\n", err_msg);

	  sqlite3_free(err_msg);
	}
}

void add_net_income(int year, int quarter, int value) {

	char statement[150];

	sprintf(statement, "CREATE TABLE IF NOT EXISTS Q%d_%d(cik TEXT, Net_Income INT);"
			   "INSERT INTO Q%d_%d VALUES(56873, %d);", quarter, year, quarter, year, value);

	rc = sqlite3_exec(db, statement, 0, 0, &err_msg);

	if (rc != SQLITE_OK) {
	  fprintf(stderr, "SQL error: %s\n", err_msg);

	  sqlite3_free(err_msg);
	}
}

void print_quarter(int year, int quarter) {

	char statement[150];

	sprintf(statement, "SELECT * FROM Q%d_%d;", quarter, year);

	rc = sqlite3_exec(db, statement, callback, 0, &err_msg);

	if (rc != SQLITE_OK) {

	  fprintf(stderr, "Failed to select data\n");
	  fprintf(stderr, "SQL error: %s\n", err_msg);

	  sqlite3_free(err_msg);
	}
}


int callback(void *NotUsed, int argc, char **argv, char **azColName) {

	NotUsed = 0;

	for (int i = 0; i < argc; i++) {
	  printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	return 0;
}


void close_database() {

	sqlite3_close(db);
}
