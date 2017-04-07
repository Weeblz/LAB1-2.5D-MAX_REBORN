#pragma once
#include "sqlite3.h"
#include "Figure.h"
#include <vector>

class DataBase {
public:
	DataBase();
	virtual ~DataBase();

	void tableCreate();
	void insertData();

private:
	sqlite3* db;
};