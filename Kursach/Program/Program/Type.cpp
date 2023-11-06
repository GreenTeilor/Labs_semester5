#include "Type.h"

std::map<Type::Types, std::string> Type::typeImagePath = 
{
	{Types::BOMB, "assets/bomb.png"},
	{Types::EMPTY, "assets/empty.png"},
	{Types::CLOSED, "assets/closed.png"},
	{Types::FLAG, "assets/flag.png"},
	{Types::WRONG_FLAG, "assets/wrongFlag.png"},
	{Types::NUMBER_1, "assets/number1.png"},
	{Types::NUMBER_2, "assets/number2.png"},
	{Types::NUMBER_3, "assets/number3.png"},
	{Types::NUMBER_4, "assets/number4.png"},
	{Types::NUMBER_5, "assets/number5.png"},
	{Types::NUMBER_6, "assets/number6.png"},
	{Types::NUMBER_7, "assets/number7.png"},
	{Types::NUMBER_8, "assets/number8.png"},
};

Type::Type(Types type) : m_type{ type }, m_imagePath{ typeImagePath.at(type) }
{

}

Type::operator std::string() const 
{
	return m_imagePath;
}

bool Type::operator == (const Type& type)
{
	return m_type == type.m_type;
}

bool Type::operator == (const Types& type)
{
	return m_type == type;
}

bool Type::operator != (const Type& type)
{
	return m_type != type.m_type;
}

bool Type::operator != (const Types& type)
{
	return m_type != type;
}

Type& Type::operator = (const Types& type)
{
	m_type = type;
	m_imagePath = typeImagePath.at(type);
	return *this;
}