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
	int num = rand() % 98652 + 24589;
	std::string database = "MyDb";
	std::string directory = "..\\Debug\\";
	std::string example = std::to_string(num);
	SQL::statement *query = new SQL::statement(directory, 300, 50, 1);
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
	
	//----------------------------------------------------------------------------
	// Execute SQL
	query->add("value", 5, query->VALUE);
	query->add("STRING", 6, query->TYPE);
	query->createTable(querystatement, "MyTable", 7);
	rc = sqlite3_exec(db, sqlcommand, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Created MyTable." << endl << endl;
	
	//----------------------------------------------------------------------------
	// Execute SQL
	std::cout << "Inserting a value into MyTable ..." << endl;
	example.insert(0, "'");
	example.insert(example.length(), "'");
	query->add('\0', 0, query->VALUETOTYPE);
	query->add(&example[0], example.length(), query->VALUE);
	query->insertIntoTable(querystatement, "MyTable", 7);
	rc = sqlite3_exec(db, sqlcommand, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Inserted a value into MyTable." << endl << endl;
	

	
	//----------------------------------------------------------------------------
	// Display MyTable
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
		query->copyrecords(results, rows, columns);
		// Display Table
		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				// Determine Cell Position
				int cellPosition = (rowCtr * columns) + colCtr;

				// Display Cell Value
				std::cout.width(12);
				std::cout.setf(ios::left);
				std::cout << results[cellPosition] << " ";
			}

			// End Line
			std::cout << endl;

			// Display Separator For Header
			if (0 == rowCtr)
			{
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
	// Close Database
	std::cout << "Closing MyDb.db ..." << endl;
	sqlite3_close(db);
	std::cout << "Closed MyDb.db" << endl << endl;
	// Table extraction test
	rows = 0;
	char cell[50];
	while (query->readcell(cell, rows++)) std::cout << cell << endl;
	// Wait For User To Close Program
	std::cout << "Please press any key to exit the program ..." << endl;
	delete query;
	std::cin.get();
	return 0;
}