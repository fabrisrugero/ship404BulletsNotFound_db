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
	std::string database = "ship404BulletsNotFound";
	std::string directory = "..\\Debug\\";
	std::string table = "circle_values";
	SQL::statement *query = new SQL::statement(directory, 300, 50, 9);
	char *error;
	// Open Database
	std::cout << "Opening " << database << ".db ..." << endl;
	sqlite3 *db;
	query->connectTo(querystatement, database);
	rc = sqlite3_open(sqlcommand, &db);
	if (rc){
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_close(db);
		return 1;
	}
	else
		std::cout << "Opened " << database << ".db." << endl << endl;
	query->add("startx", 6, query->VALUE, true);
	query->add("starty", 6, query->VALUE, true);
	query->add("constx", 6, query->VALUE, true);
	query->add("consty", 6, query->VALUE, true);
	query->add("maxx", 4, query->VALUE, true);
	query->add("maxy", 4, query->VALUE, true);
	query->add("innergrad", 9, query->VALUE, true);
	query->add("outergrad", 9, query->VALUE, true);
	query->add("exponent", 8, query->VALUE);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE, true);
	query->add("REAL", 4, query->TYPE);
	query->createTable(querystatement, &table[0], table.length());
	rc = sqlite3_exec(db, sqlcommand, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Created " << table << "." << endl << endl;
	
	std::cout << "Inserting a value into " << table << " ..." << endl;
	for (int cols = 0; cols < 9; cols++) query->add('\0', 0, query->VALUETOTYPE, cols != 8);
	query->add("-2700", 5, query->VALUE, true);
	query->add("30000", 5, query->VALUE, true);
	query->add("29000", 5, query->VALUE, true);
	query->add("2700", 4, query->VALUE, true);
	query->add("1000", 4, query->VALUE, true);
	query->add("2236", 4, query->VALUE, true);
	query->add("1", 1, query->VALUE, true);
	query->add("0.2", 3, query->VALUE, true);
	query->add("2", 1, query->VALUE);
	query->insertIntoTable(querystatement, &table[0], table.length());
	rc = sqlite3_exec(db, sqlcommand, NULL, NULL, &error);

	if (rc){
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Inserted a row into " << table << "." << endl << endl;

	std::cout << "Retrieving rows in " << table << " ..." << endl;
	query->selectFromTable(querystatement, &table[0], table.length());
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
		columns = query->dimensions(false);
		rows = query->dimensions(true);
		for (int row = 0; row <= rows; ++row){
			for (int colCtr = 0; colCtr < columns; ++colCtr){
				std::cout.width(10);
				std::cout.setf(ios::left);
				query->readcell(contents,
					query->cellposition(colCtr, row));
				if (row == 0) std::cout << std::string(contents, query->getlenght(colCtr, row)) << " ";
				else std::cout << atof(contents) << " ";
			}
			std::cout << endl;
			if (0 == row){
				for (int colCtr = 0; colCtr < columns; ++colCtr){
					std::cout.width(10);
					std::cout.setf(ios::left);
					std::cout << "---------- ";
				}
				std::cout << endl;
			}
		}
	}

	sqlite3_free_table(results);
	std::cout << "Closing " << database << ".db ..." << endl;
	sqlite3_close(db);
	std::cout << "Closed " << database << ".db" << endl << endl;
	std::cout << "Please press any key to exit the program ..." << endl;
	delete query;
	std::cin.get();
	return 0;
}