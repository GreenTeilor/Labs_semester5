#pragma once
#include <map>
#include <string>

class Type
{
public:
	enum class Types
	{
		BOMB = -4, EMPTY, CLOSED, FLAG, WRONG_FLAG,
		NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, 
		NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8
	};

private:
	static std::map<Types, std::string> typeImagePath;
	Types m_type;
	std::string m_imagePath;

public:
	Type(Types type);
	operator std::string() const;
	bool operator == (const Type& type);
	bool operator == (const Types& type);
	bool operator != (const Type& type);
	bool operator != (const Types& type);
	Type& operator = (const Types& type);
};

