#include "DataBase.h"
#include "Bar.h"
#include <iostream>
#include <sstream>
#include <string>

DataBase::DataBase() {
	if (sqlite3_open("save.db", &db) != SQLITE_OK) {
		std::cerr << "Error opening db file." << std::endl;
		this->~DataBase();
	}
	createTable();
}

DataBase::~DataBase() {
	sqlite3_close(db);
}

void DataBase::clearTable() {
	char* errmsg;
	const char* sql_clear_table = "DELETE FROM objects";
	if (sqlite3_exec(db, sql_clear_table, NULL, NULL, &errmsg)) {
		std::cerr << "Error clearing table." << std::endl;
		sqlite3_free(errmsg);
	}
}

void DataBase::createTable() {
	char* errmsg;
	const char* sql_create_table = "CREATE TABLE IF NOT EXISTS objects(essence INTEGER, isActive INTEGER, color_r REAL, color_g REAL, color_b REAL, color_a REAL, positionX REAL, positionY REAL, positionZ REAL, rotationX REAL, rotationY REAL, rotationZ REAL, scaleX REAL, scaleY REAL, scaleZ REAL);";
	if (sqlite3_exec(db, sql_create_table, NULL, NULL, &errmsg)) {
		std::cerr << "Error executing statement." << std::endl;
		sqlite3_free(errmsg);
	}
}

int callback(void* notUsed, int argc, char** argv, char**azColName) {
	notUsed = 0;
	
	figureType essence;
	bool isActive;
	glm::vec3 position, rotation, scale;
	glm::vec4 color;

	essence = (figureType)(atoi(argv[0]));
	isActive = (argv[1][0] == '1');
	color = glm::vec4(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
	position = glm::vec3(atof(argv[6]), atof(argv[7]), atof(argv[8]));
	rotation = glm::vec3(atof(argv[9]), atof(argv[10]), atof(argv[11]));
	scale = glm::vec3(atof(argv[12]), atof(argv[13]), atof(argv[14]));

	objects.push_back(Figure(essence, isActive, color, position, rotation, scale));

	return 0;
}

void DataBase::extractData() {
	char* errmsg;
	objects.clear();
	const char* sql_get_data = "SELECT * FROM objects";
	if (sqlite3_exec(db, sql_get_data, callback, NULL, &errmsg)) {
		std::cerr << "Error getting data." << std::endl;
		sqlite3_free(errmsg);
	}
}

void DataBase::insertData() {
	clearTable();
	glm::vec4 tempColor;
	Transform tempTransform;
	char* errmsg;

	std::stringstream toInsert;
	toInsert << "INSERT INTO objects(essence, isActive, color_r, color_g, color_b, color_a, positionX, positionY, positionZ, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ) VALUES";
	for (int i = 0; i < objects.size(); i++) {
		tempColor = objects[i].getColor();
		tempTransform = objects[i].getTransformation();
		toInsert << "(";
		toInsert << (int)objects[i].getType() << "," << (int)objects[i].isActive() << "," 
			<< tempColor.r << "," << tempColor.g << "," << tempColor.b << "," << tempColor.a << "," 
			<< tempTransform.getPosition().x << "," << tempTransform.getPosition().y << "," << tempTransform.getPosition().z << "," 
			<< tempTransform.getRotation().x << "," << tempTransform.getRotation().y << "," << tempTransform.getRotation().z << "," 
			<< tempTransform.getScale().x << "," << tempTransform.getScale().y << "," << tempTransform.getScale().z;
		if (i != objects.size() - 1) toInsert << "),";
		else toInsert << ");";
	}
	const std::string tmp = toInsert.str();
	std::cout << tmp << std::endl;
	const char* cstr = tmp.c_str();
	if (sqlite3_exec(db, cstr, NULL, NULL, &errmsg)) {
		std::cerr << "Error executing statement [AFTER PARSING OBJECTS]" << std::endl;
	}
}