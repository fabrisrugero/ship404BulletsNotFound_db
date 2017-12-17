#include <ios>
#include <iostream>
#include "statement.h"
#include "sqlite3.h"

using namespace std;

int main()
{

	int rc = 0;
	const char* sqlcommand;
	char querystatement[70];
	sqlcommand = querystatement;
	std::string database = "MyDb";
	std::string directory = "..\\Debug\\";
	SQL::statement *query = new SQL::statement(directory, 70, 9);
	char *error;
	// Open Database
	cout << "Opening MyDb.db ..." << endl;
	sqlite3 *db;
	query->initcolumns(1); 
	query->connectTo(querystatement, database);
	rc = sqlite3_open(querystatement, &db);
	if (rc)
	{
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_close(db);
		return 1;
	}
	else
	{
		cout << "Opened MyDb.db." << endl << endl;
	}
	//----------------------------------------------------------------------------
	// Execute SQL
	query->add("value", 5, query->VALUE);
	query->add("STRING", 6, query->TYPE);
	query->createTable(querystatement, "MyTable", 7);
	rc = sqlite3_exec(db, querystatement, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
	{
		cout << "Created MyTable." << endl << endl;
	}
	//----------------------------------------------------------------------------
	// Execute SQL
	cout << "Inserting a value into MyTable ..." << endl;
	query->add('\0', 0, query->VALUETOTYPE);
	query->add("A value", 7, query->VALUE);
	query->insertIntoTable(querystatement, "MyTable", 7);
	delete query;
	rc = sqlite3_exec(db, querystatement, NULL, NULL, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
	{
		cout << "Inserted a value into MyTable." << endl << endl;
	}
	//----------------------------------------------------------------------------
	// Display MyTable
	cout << "Retrieving values in MyTable ..." << endl;
	const char *sqlSelect = "SELECT * FROM MyTable;";
	char **results = NULL;
	int rows, columns;
	sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
	}
	else
	{
		// Display Table
		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				// Determine Cell Position
				int cellPosition = (rowCtr * columns) + colCtr;

				// Display Cell Value
				cout.width(12);
				cout.setf(ios::left);
				cout << results[cellPosition] << " ";
			}

			// End Line
			cout << endl;

			// Display Separator For Header
			if (0 == rowCtr)
			{
				for (int colCtr = 0; colCtr < columns; ++colCtr)
				{
					cout.width(12);
					cout.setf(ios::left);
					cout << "~~~~~~~~~~~~ ";
				}
				cout << endl;
			}
		}
	}
	sqlite3_free_table(results);

	// Close Database
	cout << "Closing MyDb.db ..." << endl;
	sqlite3_close(db);
	cout << "Closed MyDb.db" << endl << endl;
	// Wait For User To Close Program
	cout << "Please press any key to exit the program ..." << endl;
	cin.get();

	return 0;
}