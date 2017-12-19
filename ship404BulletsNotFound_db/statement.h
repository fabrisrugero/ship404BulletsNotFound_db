#include<string.h>
#include <iostream>
using namespace std;
namespace SQL{
	class statement
	{
	public:			
		~statement();
		int dimensions(bool rowOrccolumns);
		bool readcell(char *cell, int index);
		enum Data{ TYPE, VALUE, VALUETOTYPE };
		int cellposition(int col, int rowindex);
		enum COLMN { ONE, TWO, THREE, FOUR, FIVE, SIX };
		void connectTo(char* sql, std::string database);
		void copyrecords(char** query_result, int rows, int columns);
		void selectFromTable(char* sql, const char *tablename, int lenght);
		void createTable(char* sql, const char *tablename, int namelenght);
		void insertIntoTable(char* sql, const char *tablename, int namelenght);
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
		void initcolumns(char*** arr, int max_columns);
		void concantenate(const char *a, int b, const char *c, int d);
	};
}