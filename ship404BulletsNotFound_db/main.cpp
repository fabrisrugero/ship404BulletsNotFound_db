#include <ios>
#include <iostream>
#include "statement.h"
#include "sqlite3.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
bool opendb(SQL::statement *query,std::string database, char *querystatement, const char *sqlcommand, sqlite3 **db){
	// Open Database
	std::cout << "Opening " << database << ".db ..." << endl;
	query->connectTo(querystatement, database);
	int rc = sqlite3_open(sqlcommand, db);
	if (rc){
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(*db) << endl << endl;
		sqlite3_close(*db);
		return false;
	}
	else
		std::cout << "Opened " << database << ".db." << endl << endl;
	return true;
}
void createTable(SQL::statement *query, std::string table, char *querystatement, const char *sqlcommand, sqlite3 **db, char **error){
	query->add("name", 4, query->VALUE, true);
	query->add("part", 4, query->VALUE, true);
	query->add("radius", 6, query->VALUE, true);
	query->add("partx", 5, query->VALUE, true);
	query->add("party", 5, query->VALUE);
	query->add("STRING", 6, query->TYPE, true);
	query->add("STRING", 6, query->TYPE, true);
	query->add("INTEGER", 7, query->TYPE, true);
	query->add("INTEGER", 7, query->TYPE, true);
	query->add("INTEGER", 7, query->TYPE);
	query->createTable(querystatement, &table[0], table.length());
	int rc = sqlite3_exec(*db, sqlcommand, NULL, NULL, error);
	if (rc)
	{
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(*db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Created " << table << "." << endl << endl;
}
void InsertIntoTable(SQL::statement *query, std::string table, char *querystatement, const char *sqlcommand, sqlite3 **db, char **error)
{
	std::cout << "Inserting a row into " << table << " ..." << endl;
	query->add("name", 4, query->TYPE, true);
	query->add("part", 4, query->TYPE, true);
	query->add("radius", 6, query->TYPE, true);
	query->add("partx", 5, query->TYPE, true);
	query->add("party", 5, query->TYPE);
	query->add("'blue'", 6, query->VALUE, true);
	query->add("'nose'", 6, query->VALUE, true);
	query->add("4", 1, query->VALUE, true);
	query->add("12", 2, query->VALUE, true);
	query->add("45", 2, query->VALUE);
	query->insertIntoTable(querystatement, &table[0], table.length());
	int rc = sqlite3_exec(*db, sqlcommand, NULL, NULL, error);
	if (rc){
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(*db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Inserted a row into " << table << "." << endl << endl;
}
void updateRowInTable(SQL::statement *query, std::string table, char *querystatement, const char *sqlcommand, sqlite3 **db, char **error){
	std::cout << "Updatinging a row in " << table << " ..." << endl;
	query->add("id", 2, query->TYPE, true);
	query->add("outergrad", 9, query->TYPE);
	query->add("2", 1, query->VALUE, true);
	query->add("0.2", 3, query->VALUE);
	query->updateRowInTable(querystatement, &table[0], table.length(), query->ONE);
	int rc = sqlite3_exec(*db, sqlcommand, NULL, NULL, error);
	if (rc){
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(*db) << endl << endl;
		sqlite3_free(error);
	}
	else
		std::cout << "Updated a row in " << table << "." << endl << endl;
}
void deleteFromTable(SQL::statement *query, std::string table, char *querystatement, const char *sqlcommand, sqlite3 **db, char **error){
	std::cout << "Deleting a row from " << table << " ..." << endl;
	query->add("id", 2, query->TYPE);
	query->add("3", 10, query->VALUE);
	query->deleteRowInTable(querystatement, &table[0], table.length(), query->ONE);
	int rc = sqlite3_exec(*db, sqlcommand, NULL, NULL, error);
	if (rc){
		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(*db) << endl << endl;
		sqlite3_free(error);
	}
	else{
		query->add("\0", 0, query->TYPE);
		std::cout << "Deleted a row from " << table << "." << endl << endl;
	}

}
int main()
{
	int rc = 0;
	char *error;
	sqlite3 *db;
	srand(time(0));
	const char* sqlcommand;
	char querystatement[300];
	sqlcommand = querystatement;
	std::string database = "ship404BulletsNotFound";
	std::string directory = "..\\Debug\\";
	std::string table = "gameobj_parts";
	SQL::statement *query = new SQL::statement(directory, 300, 50, 20);
	if (!opendb(query, database, querystatement, sqlcommand, &db)) return 1;
	//createTable(query, table, querystatement, sqlcommand, &db, &error);
	//InsertIntoTable(query, table, querystatement, sqlcommand, &db, &error);
	//updateRowInTable(query, table, querystatement, sqlcommand, &db, &error);
	//deleteFromTable(query, table, querystatement, sqlcommand, &db, &error);
	//sqlite3_exec(db, "ALTER TABLE qaudratic_values RENAME TO gameobj_parts", NULL, NULL, NULL);

	std::cout << "Retrieving rows in " << table << " ..." << endl << endl;
	query->selectFromTable(querystatement, &table[0], table.length());
	char **results = NULL;
	int rows, columns;
	sqlite3_get_table(db, sqlcommand, &results, &rows, &columns, &error);
	if (rc){
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
				else std::cout << std::string(contents, query->getlenght(colCtr, row)) << " ";
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
	std::cout << endl << "Closing " << database << ".db ..." << endl;
	sqlite3_close(db);
	std::cout << "Closed " << database << ".db" << endl << endl;
	std::cout << "Please press any key to exit the program ..." << endl;
	delete query;
	std::cin.get();
	return 0;
}