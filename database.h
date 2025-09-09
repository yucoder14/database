#include "table.h"
#include "parser.h"

// DatabaseSystem is responsible for parsing, interpreting queries before passing the data 
// onto the Table class
class DatabaseSystem {
public: 
	void runQuery(std::string s) {
		QueryObject q = parser.parse(s);
		switch (q.mode) {
			case CREATE: 
				// create new table
				tables[q.tableName] = Table(colDefList);
				break;
			case SELECT: 
				if (tables.find(q.name) == tables.end()) 
					throw std::runtime_error("table not found");
				else 
					tables[q.tableName].selectFromTable(colList, where_clause, order_clause);
				break;
			case INSERT: 
				if (tables.find(q.name) == tables.end()) 
					throw std::runtime_error("table not found");
				else 
					tables[q.tableName].insertIntoTable(colList, valList);
				break;
			case DELETE: 
				if (tables.find(q.name) == tables.end()) 
					throw std::runtime_error("table not found");
				else 
					tables[q.tableName].deleteFromTable(where_clause);
				break;
			default: 
				break;
		}	
	}	
private: 
	std::unordered_map<std::string, Table> tables;
	Parser parser;
};
