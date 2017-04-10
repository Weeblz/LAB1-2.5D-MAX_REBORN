#pragma once
#include "sqlite3.h"
#include "Figure.h"
#include <vector>

class DataBase {
public:
	DataBase();
	virtual ~DataBase();

	void createTable();
	void dropTable();
	void clearTable();
	void insertData();
	void extractData();

private:
	sqlite3* db;
};