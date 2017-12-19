#include "statement.h"

SQL::statement::~statement(){
	for (this->indexer = 0; this->indexer <= this->max_columns; ++this->indexer){
		delete[] this->values[this->indexer]; delete[] this->types[this->indexer++];}
	this->max_columns = this->rows*this->columns;
	for (this->Indexer = 0; this->Indexer <= this->max_columns; ++this->Indexer)
		delete[] this->results[this->Indexer++];
	delete[] this->types;
	delete[] this->sizes;
	delete[] this->values;
	delete[] this->results;
	delete[] this->directory;
	delete[] this->types_lenght;
	delete[] this->values_lenght;
	delete[] this->querychararcters;
};
void SQL::statement::clearbuffer(){
	this->position = 0;
	for (this->indexer = 0; this->indexer <= this->query_size; ++this->indexer) 
		this->querychararcters[this->indexer] = '\0';
};
SQL::statement::statement(std::string directory, int query_size, int max_chars, int max_columns){
	this->indexer = 0;
	this->max_chars = max_chars;
	this->query_size = query_size;
	this->max_columns = max_columns;
	this->dir_size = directory.length();
	this->types_lenght = new int[max_chars + 1];
	this->initcolumns(this->types, max_columns);
	this->values_lenght = new int[max_chars + 1];
	this->initcolumns(this->values, max_columns);
	this->querychararcters = new char[query_size + 1];
	this->directory = new char[directory.length() + 1];
	for (this->indexer = 0; this->indexer <= this->dir_size; ++this->indexer)
		this->directory[this->indexer] = directory[this->indexer]; 
};
void SQL::statement::connectTo(char* sql, std::string database){
	this->clearbuffer();
	this->concantenate(this->directory, this->dir_size, &database[0], 0);
	this->concantenate(&database[0], database.length(), ".db", 3); this->indexer = -1;
	for (this->indexer = 0; this->indexer <= this->query_size; ++this->indexer) 
		sql[this->indexer] = this->querychararcters[this->indexer]; this->indexer = 0;
};
int SQL::statement::dimensions(bool rowOrccolumn){
	if (rowOrccolumn) return this->rows;
	else return this->columns;
};
void SQL::statement::copyrecords(char** query_results, int rows, int columns){
	this->rows = rows;
	this->columns = columns;
	this->sizes = new size_t[rows*columns + 1];
	this->initcolumns(this->results, rows*columns);
	for (this->Indexer = 0; this->Indexer <= rows; ++this->Indexer){
		for (this->indexer = 0; this->indexer < columns; ++this->indexer){
			int cellPosition = (this->Indexer * columns) + this->indexer;
			this->sizes[cellPosition] = sizeof(query_results[cellPosition]) / sizeof(query_results[cellPosition][0]);
			for (size_t i = 0; i < this->sizes[cellPosition]; i++) this->results[cellPosition][i] = query_results[cellPosition][i];}}
}
bool SQL::statement::readcell(char *cell, int index){
	if (index < (this->rows*this->columns) + this->max_columns)
		for (this->Indexer = 0; this->Indexer < this->sizes[index]; ++this->Indexer)
			cell[this->Indexer] = this->results[index][this->Indexer];
	return this->Indexer;
};
void SQL::statement::selectFromTable(char* sql, const char *tablename, int lenght){
	this->clearbuffer();
	this->concantenate("SELECT (", 8, tablename, 0);
	for (int row = 0; row <= this->max_columns; row++)
		this->concantenate(this->types[row], this->types_lenght[row], ", ", 2);
	this->position -= 2;
	this->concantenate(")", 1, " FROM ", 6);
	this->concantenate(tablename, lenght, ";", 1);
	for (this->indexer = 0; this->indexer <= this->query_size; ++this->indexer) 
		sql[this->indexer] = this->querychararcters[this->indexer++]; 
};
void SQL::statement::insertIntoTable(char* sql, const char *tablename, int namelenght){
	this->clearbuffer();
	this->concantenate("INSERT INTO ", 12, tablename, 0);
	this->concantenate(tablename, namelenght, " (", 2);
	for (this->Indexer = 0; this->Indexer <= this->max_columns; this->Indexer++)
		this->concantenate(this->types[this->Indexer], this->types_lenght[this->Indexer], ", ", 2);
	this->position -= 2;
	this->concantenate(") VALUES (", 10, tablename, 0);
	for (this->Indexer = 0; this->Indexer <= this->max_columns; this->Indexer++)
		this->concantenate(this->values[this->Indexer], this->values_lenght[this->Indexer], ", ", 2);
	this->position -= 2;
	this->concantenate(");", 2, tablename, 0);
	for (this->indexer = 0; this->indexer <= this->query_size; ++this->indexer) 
		sql[this->indexer] = this->querychararcters[this->indexer++]; 
};
void SQL::statement::createTable(char* sql, const char *tablename, int namelenght){
	this->clearbuffer();
	this->concantenate("CREATE TABLE ", 13, tablename, 0);
	this->concantenate(tablename, namelenght, " (id INTEGER PRIMARY KEY", 24);
	for (this->Indexer = 0; this->Indexer <= this->max_columns; this->Indexer++){
		this->concantenate(", ", 2, this->values[this->Indexer], this->values_lenght[this->Indexer]);
		this->concantenate(" ", 1, this->types[this->Indexer], this->types_lenght[this->Indexer]);}
	this->concantenate(");", 2, tablename, 0);
	for (this->indexer = 0; this->indexer <= this->query_size; ++this->indexer) 
		sql[this->indexer] = this->querychararcters[this->indexer++];
};
void SQL::statement::concantenate(const char *a, int b, const char *c, int d){
	for (this->indexer = this->position; this->indexer <= this->query_size && this->indexer < b; ++this->indexer)
	//while (this->position + this->indexer < this->query_size && this->indexer < b)
		this->querychararcters[this->position + this->indexer] = a[this->indexer++];
	//this->position = this->indexer; 
	for (this->indexer; this->indexer <= this->query_size && this->indexer < d; ++this->indexer)
	//while (this->position + this->indexer < this->query_size && this->indexer < d)
		this->querychararcters[this->position + this->indexer] = c[this->indexer++];
	this->position = this->indexer;
};
void SQL::statement::add(const char* value, int lenght, SQL::statement::Data column, bool addmore){
	if (this->index < this->max_columns && column == VALUE)
		/*while (this->indexer < this->max_chars && indexer < lenght)*/
		for (this->indexer = 0; this->indexer <= this->max_chars && this->indexer < lenght; ++this->indexer)
			this->values[this->index][this->indexer] = value[this->indexer++];
	else if (this->index < this->max_columns && column == TYPE)
		//while (this->indexer < this->max_chars && indexer < lenght)
		for (this->indexer = 0; this->indexer <= this->max_chars && this->indexer < lenght; ++this->indexer)
			this->types[this->index][this->indexer] = value[this->indexer++];
	else if (this->index < this->max_columns && column == VALUETOTYPE)
		//while (this->indexer < this->max_chars && indexer < this->values_lenght[this->index])
		for (this->indexer = 0; this->indexer <= this->max_chars && this->indexer < this->values_lenght[this->index]; ++this->indexer)
			this->types[this->index][this->indexer] = this->values[this->index][this->indexer++];
	if (column == TYPE) this->types_lenght[this->index++] = lenght;
	else if (column == VALUE) this->values_lenght[this->index++] = lenght;
	else if (column == VALUETOTYPE) this->types_lenght[this->index] = this->values_lenght[this->index];
	if (addmore) this->index++;
	else this->index = 0;
	this->indexer = 0;
};
void SQL::statement::initcolumns(char** arr, int max_columns){
	arr = new char*[max_columns + 1];
	for (this->indexer = 0; this->indexer <= max_columns; ++this->indexer)
		arr[this->indexer++] = new char[this->max_chars + 1];
};

