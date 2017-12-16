#include <ios>
#include <iostream>
#include "statement.h"
#include "sqlite3.h"

using namespace std;

int main()
{

	int rc = 0;
	const char* sqlcommand;
	char querystatement[300];
	sqlcommand = querystatement;
	std::string database = "MyDb.db";
	std::string directory = "..\\Debug\\";
	SQL::statement *query = new SQL::statement(directory, 50, 8);
	//cout << querystatement << endl;
	//query->add("startX", 6, query->VALUE);
	//query->add("startY", 6, query->VALUE);
	//query->add("constX", 6, query->VALUE);
	//query->add("constY", 6, query->VALUE);
	//query->add("maxX", 4, query->VALUE);
	//query->add("maxY", 4, query->VALUE);
	//query->add("\0", 0, query->NUULL);
	//for (int r = 0; r < 6; r++) query->add("REAL", 4, query->TYPE);
	//query->createTable(querystatement, "circle", 6);
	//cout << querystatement << endl;
	//rc = query->dimensions(false);
	//query->add("\0", 0, query->NUULL);
	//for (int r = 0; r < rc; r++) query->add("\0", 0, query->VALUETOTYPE);
	//query->add("\0", 0, query->NUULL);
	//query->add("12356.23", 8, query->VALUE);
	//query->add("45628", 5, query->VALUE);
	//query->add("78956.126", 9, query->VALUE);
	//query->add("002153.2356", 11, query->VALUE);
	//query->add("85", 2, query->VALUE);
	//query->add("4", 1, query->VALUE);
	//query->insertIntoTable(querystatement, "circle", 6);
	//cout << querystatement << endl;
	//query->selectFromTable(querystatement, "circle", 6);
	//cout << querystatement << endl;
	//delete query;
	//----------------------------------------------------------------------------
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
	//const char *sqlCreateTable = "CREATE TABLE MyTable (id INTEGER PRIMARY KEY, value STRING);";
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
	//const char *sqlInsert = "INSERT INTO MyTable VALUES(NULL, 'A Value');"
	query->add('\0', 0, SQL::statement::NUULL);
	query->add()
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