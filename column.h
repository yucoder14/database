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

/*** ColumnDef Structs **********************************************************/

class ColumnDef {
public: 
	virtual DataType getType() const = 0;
	virtual bool getNotNull() const = 0; 
	virtual bool getHasDefault() const = 0;
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

	void setDefaultValue(T data) { defaultData = data; }
	T getDefaultValue() const { return defaultData; };
private:
	DataType type; 
	size_t size; 
	bool notNull;
	bool hasDefault; 
	T defaultData;
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
