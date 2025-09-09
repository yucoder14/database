#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <unordered_map>
#include <memory>

#include "column.h"

// Table is not responsible for parsing user input; assumes that inputs have already been
// parsed when data reaches Table class
class Table {
public:
	Table(std::string name, std::unordered_map<std::string, std::unique_ptr<ColumnDef>>& newSchema) : tableName(name) {
		for (auto& [colName, colDef] : newSchema) {
			schema.emplace(colName, std::move(colDef));		 
		}	
	}	
//	void loadTable(std::ifstream& in) --> or something like this to load table from file
	// assuming that arguments have been read from sql query
	void insertIntoTable() {
	}	

	void selectFromTable() { 
		 
	}	

	void deleteFromTable() {
		 
	}	

	std::string getSchema() {
		std::string sql = "CREATE TABLE " + tableName + "(";
		for (auto& [colName, colDef] : schema) {
			sql += colName + " ";	
			sql += colDef->toString();
			sql += ", ";
		}	
		sql.pop_back();
		sql.pop_back();
		sql += ")";

		return sql;
	}	
private:
	int id = 0; // internal id to keep the rows unique 
	std::string tableName;
	std::unordered_map<std::string, std::unique_ptr<ColumnDef>> schema;
};
#endif
