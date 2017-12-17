#include "statement.h"

SQL::statement::~statement(){
	this->Indexer = 0;
	while (this->indexer < this->max_columns){
		delete[] this->values[this->indexer];
		delete[] this->types[this->indexer++];}
	delete[] this->types;
	delete[] this->values;
	delete[] this->directory;
	delete[] this->types_lenght;
	delete[] this->values_lenght;
	delete[] this->querychararcters;
};
void SQL::statement::clearbuffer(){
	this->indexer = this->position = 0;
	while (this->indexer < this->query_size)
		this->querychararcters[this->indexer++] = '\0';
	this->indexer = 0;
};
SQL::statement::statement(std::string directory, int query_size, int max_chars){
	this->indexer = -1;
	this->max_chars = max_chars;
	this->query_size = query_size;
	this->dir_size = directory.length();
	this->types_lenght = new int[max_chars + 1];
	this->values_lenght = new int[max_chars + 1];
	this->querychararcters = new char[query_size + 1];
	this->directory = new char[directory.length() + 1];
	while (this->indexer++ < this->dir_size) this->directory[this->indexer] = directory[this->indexer]; this->indexer = 0;
};
void SQL::statement::connectTo(char* sql, std::string database){
	this->clearbuffer();
	this->concantenate(this->directory, this->dir_size, &database[0], 0);
	this->concantenate(&database[0], database.length(), ".db", 3); this->indexer = -1;
	while (this->indexer++ < this->query_size) sql[this->indexer] = this->querychararcters[this->indexer]; this->indexer = 0;
};
int SQL::statement::dimensions(bool rowOrccolumn){
	if (rowOrccolumn) return this->rows;
	else return this->columns;
};
void SQL::statement::extractRecord(char** query_result, int row){


}
void SQL::statement::selectFromTable(char* sql, const char *tablename, int lenght){
	this->clearbuffer();
	this->concantenate("SELECT (", 8, tablename, 0);
	for (int row = 0; row < this->max_columns; row++)
		this->concantenate(this->types[row], this->types_lenght[row], ", ", 2);
	this->position -= 2;
	this->concantenate(")", 1, " FROM ", 6);
	this->concantenate(tablename, lenght, ";", 1);
	while (this->indexer < this->query_size) sql[this->indexer] = this->querychararcters[this->indexer++]; this->indexer = 0;
};
void SQL::statement::insertIntoTable(char* sql, const char *tablename, int namelenght){
	this->clearbuffer();
	this->concantenate("INSERT INTO ", 12, tablename, 0);
	this->concantenate(tablename, namelenght, " (", 2);
	for (int row = 0; row < this->max_columns; row++)
		this->concantenate(this->types[row], this->types_lenght[row], ", ", 2);
	this->position -= 2;
	this->concantenate(") VALUES (", 10, tablename, 0);
	for (int row = 0; row < this->max_columns; row++)
		this->concantenate(this->values[row], this->values_lenght[row], ", ", 2);
	this->position -= 2;
	this->concantenate(");", 2, tablename, 0);
	while (this->indexer < this->query_size) sql[this->indexer] = this->querychararcters[this->indexer++]; this->indexer = 0;
};
void SQL::statement::createTable(char* sql, const char *tablename, int namelenght){
	this->clearbuffer();
	this->concantenate("CREATE TABLE ", 13, tablename, 0);
	this->concantenate(tablename, namelenght, " (id INTEGER PRIMARY KEY", 24);
	for (int row = 0; row < this->max_columns; row++){
		this->concantenate(", ", 2, this->values[row], this->values_lenght[row]);
		this->concantenate(" ", 1, this->types[row], this->types_lenght[row]);}
	this->concantenate(");", 2, tablename, 0);
	while (this->indexer < this->query_size) sql[this->indexer] = this->querychararcters[this->indexer++]; this->indexer = 0;
};
void SQL::statement::concantenate(const char *a, int b, const char *c, int d){
	while (this->position + this->indexer < this->query_size && this->indexer < b)
		this->querychararcters[this->position + this->indexer] = a[this->indexer++];
	this->position += this->indexer; this->indexer = 0;
	while (this->position + this->indexer < this->query_size && this->indexer < d)
		this->querychararcters[this->position + this->indexer] = c[this->indexer++];
	this->position += this->indexer; this->indexer = 0;
};
void SQL::statement::add(const char* value, int lenght, SQL::statement::Data column, bool addmore){
	if (this->index < this->max_columns && column == VALUE)
		while (this->indexer < this->max_chars && indexer < lenght)
			this->values[this->index][this->indexer] = value[this->indexer++];
	else if (this->index < this->max_columns && column == TYPE)
		while (this->indexer < this->max_chars && indexer < lenght)
			this->types[this->index][this->indexer] = value[this->indexer++];
	else if (this->index < this->max_columns && column == VALUETOTYPE)
		while (this->indexer < this->max_chars && indexer < this->values_lenght[this->index])
			this->types[this->index][this->indexer] = this->values[this->index][this->indexer++];
	if (column == TYPE) this->types_lenght[this->index++] = lenght;
	else if (column == VALUE) this->values_lenght[this->index++] = lenght;
	else if (column == VALUETOTYPE) this->types_lenght[this->index] = this->values_lenght[this->index++];
	if (addmore) this->columns = this->index;
	else if (!addmore) this->index = 0;
	this->indexer = 0;
};
void SQL::statement::initcolumns(int max_columns){
	this->values = new char*[max_columns + 1];
	while (this->indexer < max_columns)
		this->values[this->indexer++] = new char[this->max_chars + 1];
	this->indexer = 0;
	this->types = new char*[max_columns + 1];
	while (this->indexer < max_columns)
		this->types[this->indexer++] = new char[this->max_chars + 1];
	this->max_columns = max_columns;
	this->max_chars = max_chars;
	this->indexer = 0;
};

void SQL::statement::quotevalues(int starts, int ends){

};

