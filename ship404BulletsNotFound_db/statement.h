#include<string.h>
#include <iostream>
using namespace std;
namespace SQL{
	class statement
	{
	public:			
		~statement();
		enum Data{ TYPE, VALUE };
		int dimensions(bool rowOrccolumns);
		bool readcell(char *cell, int index);
		int cellposition(int col, int rowindex);
		size_t getlenght(int columindex, int rowindex);
		enum COLMN { ONE, TWO, THREE, FOUR, FIVE, SIX };
		void connectTo(char* sql, std::string database);
		void copyrecords(char** query_result, int rows, int columns);
		void createTable(char* sql, const char *tablename, int namelenght);
		void insertIntoTable(char* sql, const char *tablename, int namelenght);
		void deleteRowInTable(char* sql, const char *tablename, int lenght, int column);
		void selectFromTable(char* sql, const char *tablename, int lenght, int column = -1);
		void updateRowInTable(char* sql, const char *tablename, int namelenght, int column = 0);
		statement(std::string directory, int query_size, int max_chars, int max_columns);
		void add(const char* value, int lenght, SQL::statement::Data column, bool addmore = false);


	private:
		int rows;
		int index;
		int columns;
		int indexer;
		int Indexer;
		int dir_size;
		char** types;
		int position;
		char** values;
		int max_chars;
		size_t* sizes;
		char** results;
		bool startOver;
		int query_size;
		char* directory;
		int max_columns;
		int* types_lenght;
		int* values_lenght;
		void clearbuffer();
		char* querychararcters;
		void condition(int column, int valueindex);
		void initcolumns(char*** arr, int max_columns);
		void concantenate(const char *a, int b, const char *c, int d);
	};
}