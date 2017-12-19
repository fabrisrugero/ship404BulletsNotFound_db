#include <ios>
#include <iostream>
#include "statement.h"
#include "sqlite3.h"
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{

	int rc = 0;
	srand(time(0));
	const char* sqlcommand;
	char querystatement[300];
	sqlcommand = querystatement;
	std::string database = "MyDb";
	std::string directory = "..\\Debug\\";
	SQL::statement *query = new SQL::statement(directory, 300, 50, 4);
	char *error;
	// Open Database
	std::cout << "Opening MyDb.db ..." << endl;
	sqlite3 *db;
	query->connectTo(querystatement, database);
	rc = sqlite3_open(sqlcommand, &db);
	if (rc){
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_close(db);
		return 1;
	}
	else
		std::cout << "Opened MyDb.db." << endl << endl;
	
	query->add("startX", 6, query->VALUE, true);
	query->add("startY", 6, query->VALUE, true);
	query->add("constX", 6, query->VALUE, true);
	query->add("constY", 6, query->VALUE);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE);
	query->createTable(querystatement, "MyTable", 7);
	rc = sqlite3_exec(db, sqlcommand, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Created MyTable." << endl << endl;
	
	std::cout << "Inserting a value into MyTable ..." << endl;
	query->add('\0', 0, query->VALUETOTYPE, true);
	query->add('\0', 0, query->VALUETOTYPE, true);
	query->add('\0', 0, query->VALUETOTYPE, true);
	query->add('\0', 0, query->VALUETOTYPE);
	query->add(&std::to_string(rand() % 98652 + 24589)[0], 5, query->VALUE, true);
	query->add(&std::to_string(rand() % 98652 + 24589)[0], 5, query->VALUE, true);
	query->add(&std::to_string(rand() % 98652 + 24589)[0], 5, query->VALUE, true);
	query->add(&std::to_string(rand() % 98652 + 24589)[0], 5, query->VALUE);
	query->insertIntoTable(querystatement, "MyTable", 7);
	rc = sqlite3_exec(db, sqlcommand, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Inserted a value into MyTable." << endl << endl;

	std::cout << "Retrieving values in MyTable ..." << endl;
	query->selectFromTable(querystatement, "MyTable", 7);
	char **results = NULL;
	int rows, columns;
	sqlite3_get_table(db, sqlcommand, &results, &rows, &columns, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else{
		char contents[50];
		query->copyrecords(results, rows, columns);
		for (int row = 0; row <= rows; ++row){
			for (int colCtr = 1; colCtr <= query->FOUR; ++colCtr){
				std::cout.width(12);
				std::cout.setf(ios::left);
				query->readcell(contents,
					query->cellposition(query->FOUR - colCtr, row));
				std::cout << contents<< " ";
			}
			std::cout << endl;
			if (0 == row){
				for (int colCtr = 0; colCtr < columns; ++colCtr)
				{
					std::cout.width(12);
					std::cout.setf(ios::left);
					std::cout << "~~~~~~~~~~~~ ";
				}
				std::cout << endl;
			}
		}
	}

	sqlite3_free_table(results);
	std::cout << "Closing MyDb.db ..." << endl;
	sqlite3_close(db);
	std::cout << "Closed MyDb.db" << endl << endl;
	std::cout << "Please press any key to exit the program ..." << endl;
	delete query;
	std::cin.get();
	return 0;
}