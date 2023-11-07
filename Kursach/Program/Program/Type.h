#pragma once
#include <map>
#include <string>
#include <vector>

class Type
{
public:
	enum class Types
	{
		BOMB = -5, BOMB_BOOM, EMPTY, CLOSED, FLAG, WRONG_FLAG,
		NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, 
		NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8
	};

private:
	static inline std::map<Types, std::string> typeImagePath =
	{
		{Types::BOMB, "9"},
		{Types::BOMB_BOOM, "10"},
		{Types::EMPTY, "empty"},
		{Types::CLOSED, "0"},
		{Types::FLAG, "17"},
		{Types::WRONG_FLAG, "17"},
		{Types::NUMBER_1, "1"},
		{Types::NUMBER_2, "2"},
		{Types::NUMBER_3, "3"},
		{Types::NUMBER_4, "4"},
		{Types::NUMBER_5, "5"},
		{Types::NUMBER_6, "6"},
		{Types::NUMBER_7, "7"},
		{Types::NUMBER_8, "8"},
	};
	Types m_type;
	std::string m_imagePath;

public:
	Type(Types type);
	operator std::string() const;
	operator Types() const;
	bool operator == (const Type& type);
	bool operator == (const Types& type);
	bool operator != (const Type& type);
	bool operator != (const Types& type);
	Type& operator = (const Types& type);
	static std::map<Types, std::string> getTypesAndPaths();
};

