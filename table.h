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
			switch (colDef->getType()) {
				case INTEGER:
					sql += "INT"; 
					break;
				case BOOL:
					sql += "BOOL"; 
					break;
				case DOUBLE:
					sql += "DOUBLE";
					break;
				case CHAR:
					sql += "CHAR";
					break;
				case VARCHAR:
					sql += "VARCHAR";
					break;
				default:
					// should not reach default case
					break;
			}	

			if (colDef->getNotNull()) sql += " NOT NULL";
			
			if (colDef->getHasDefault()) { 
				sql += " DEFAULT";
				switch (colDef->getType()) {
					case BOOL: 
						if (dynamic_cast<TypedColumnDef<bool> *>(colDef.get())->getDefaultValue()) sql += " TRUE"; 
						else sql += " False";
						break;
					default: 
//						sql += " " + colDef->getDefaultValue();
						break;
				}	
			}	

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
//	std::vector<std::unordered_map<std::string,Column>> table; // this will probably end up being a b-tree, but no quite sure yet
};
#endif
