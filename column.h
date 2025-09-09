#ifndef COLUMN_H
#define COLUMN_H
#include <string>

/*** DataType Enum **************************************************************/

enum DataType {
	INTEGER,
	BOOL,
	DOUBLE,
	CHAR,
	VARCHAR
};

std::vector<std::string> DataTypeString = { 
	"INTEGER",
	"BOOL",
	"DOUBLE",
	"CHAR",
	"VARCHAR"
};

/*** ColumnDef Structs **********************************************************/

class ColumnDef {
public: 
	virtual DataType getType() const = 0;
	virtual bool getNotNull() const = 0; 
	virtual bool getHasDefault() const = 0;
	virtual std::vector<int> getParameters() const = 0;

	virtual void setParameters(std::vector<int> _parameters) = 0;

	virtual std::string toString() const = 0;

	virtual ~ColumnDef() = default;
};	

template <class T>
class TypedColumnDef : public ColumnDef { 
public:
	TypedColumnDef(DataType _type, bool _notNull, bool _hasDefault) : 
		type(_type), notNull(_notNull), hasDefault(_hasDefault) {
	}

	DataType getType() const override { return type; }
	bool getNotNull() const override { return notNull; }	
	bool getHasDefault() const override { return hasDefault; }	
	std::vector<int> getParameters() const override { return parameters; }
	T getDefaultValue() const { return defaultData; };

	void setParameters(std::vector<int> _parameters) override {
		parameters = std::move(_parameters);	 
	}	

	std::string toString() const override {
		std::string stringified = DataTypeString[type];		 
		if (parameters.size()) {
			stringified += "(";
			for (auto &parameter : parameters) {
				stringified += std::to_string(parameter) + ", ";
			}	
			stringified.pop_back();
			stringified.pop_back();
			stringified += ")";
		}	

		if (notNull) stringified += " NOT NULL";
		if (hasDefault) {
			stringified += " DEFAULT ";
			stringified += stringify(defaultData); 
		}	
		return stringified;
	}	

	void setDefaultValue(T data) { defaultData = data; }
private:
	DataType type; 
	size_t size; 
	bool notNull;
	bool hasDefault; 
	T defaultData;
	std::vector<int> parameters;

	std::string stringify(const T& data) const {
		if constexpr (std::is_same_v<T, std::string>)
			return data;
		else if constexpr (std::is_same_v<T, bool>)
			return data ? "TRUE" : "FALSE";
		else
			return std::to_string(data);
	}	
};	


/*** Column Classes *************************************************************/

class Column {
public:
	virtual DataType getType() const = 0;
	virtual ~Column() = default;
};

template <class T> 
class TypedColumn : public Column {
public:
	TypedColumn(T _data) : data(_data) {}

	DataType getType() const override { return type; }	
	T getData() const { return data; }	

	void setData(int _data) { data = _data; }	
	
private:	
	int data;
	DataType type;
};	
#endif
