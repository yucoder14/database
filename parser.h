#include <vector>
#include <string>
#include <memory>

enum Mode {
	CREATE, 
	INSERT,
	DELETE,
	SELECT
}

enum TokenType {
}

class Parser {
public:
	void tokenize(std::string& s);
	void parseStatements();
private:
	void peekToken();
	void getToken();
	void dropToken();

	void parseStatement();
	void parseCreatePhrase();
	void parseInsertPhrase();
	void parseDeletePhrase();
	void parseSelectPhrase();
	void parseWhereClause();
	void parseOrderClause();
	void parseExpr();
	void parseColList();
	void parseVarList();
	void parseFactor();	
}
// STATEMENTS    = STATEMENT*
// STATEMENT     = CREATE CREATE_PHRASE ";" | 
// 			       INSERT INSERT_PHRASE ";" | 
// 			       SELECT SELECT_PHRASE ";" | 
// 			       DELETE DELETE_PHRASE ";"
// 
// CREATE_PHRASE = TABLE table_name "(" COLUMN_DEF ("," COLUMN_DEF)* ")"
// COLUMN_DEF    = col_name DATA_TYPE [NOT NULL]
// 
// INSERT_PHRASE = INTO table_name "(" COL_LIST ")" VALUES "(" VAL_LIST ")"
// 
// COL_LIST      = col_name ("," col_name)*
// VAL_LIST      = FACTOR ("," FACTOR)*
// 
// SELECT_PHRASE = (COL_LIST | "*") FROM table_name [WHERE WHERE_CLAUSE] [ORDER ORDER_CLAUSE]
// 
// ORDER_CLAUSE  = BY col_name [ASC | DESC]
// 
// DELETE_PHRASE = FROM table_name WHERE WHERE_CLAUSE
// 
// WHERE_CLAUSE  = EXPR ( (AND | OR) EXPR )*
// EXPR          = col_name COMPARISON_OP FACTOR | 
// 				   col_name BETWEEN FACTOR AND FACTOR
//
// COMPARISON_OP = ">" | "<" | "=" 
// 
// FACTOR        = INTEGER | STRING | BOOL | DOUBLE

