#include <iostream>
#include <string>

//#include "database.h"
//#include "column.h"
#include "table.h"

int main() {
	std::unordered_map<std::string, std::unique_ptr<ColumnDef>> testSchema;
	testSchema["name"] = std::make_unique<TypedColumnDef<std::string>>(CHAR, false, false);
	testSchema["age"] = std::make_unique<TypedColumnDef<int>>(INTEGER, false, false);
	testSchema["required"] = std::make_unique<TypedColumnDef<bool>>(BOOL, false, true);
	testSchema["nevernull"] = std::make_unique<TypedColumnDef<double>>(DOUBLE, true, false);

	Table testTable = Table("dummy", testSchema);
	std::cout << testTable.getSchema();

	return 0;
}	
