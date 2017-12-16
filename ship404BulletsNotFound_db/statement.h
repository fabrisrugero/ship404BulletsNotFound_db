#include<string.h>
#include <iostream>
using namespace std;
namespace SQL{
	class statement
	{
	public:			
		~statement();
		enum Data{ TYPE, VALUE, NUULL };
		void initcolumns(int max_columns);
		int dimensions(bool rowOrccolumns);
		void connectTo(char* sql, std::string database);
		void extractRecord(char** query_result, int row);
		statement(std::string directory, int query_size, int max_chars);
		void selectFromTable(char* sql, const char *tablename, int lenght);
		void createTable(char* sql, const char *tablename, int namelenght);
		void add(const char* value, int lenght, SQL::statement::Data column);
		void insertIntoTable(char* sql, const char *tablename, int namelenght);


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
		bool startOver;
		int query_size;
		char* directory;
		int max_columns;
		int* types_lenght;
		int* values_lenght;
		void clearbuffer();
		char* querychararcters;
		void concantenate(const char *a, int b, const char *c, int d);
	};
}