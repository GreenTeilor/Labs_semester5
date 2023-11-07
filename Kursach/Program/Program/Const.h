#pragma once
#include <map>
#include <string>
#include "framework.h"
#include "Type.h"

class Const
{
public:
	static inline int imgWidth = 20;
	static inline int imgHeight = 20;
	static inline std::map<Type::Types, HBITMAP> images{};
	static void loadImages();
};

