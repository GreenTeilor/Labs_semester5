#include "Const.h"

void Const::loadImages()
{
    std::map<Type::Types, std::string> typesAndPaths = Type::getTypesAndPaths();
    for (std::map<Type::Types, std::string>::iterator it = typesAndPaths.begin(); it != typesAndPaths.end(); ++it) {
        std::string fullPath = "assets\\" + it->second + ".bmp";
        images.insert({it->first, (HBITMAP)LoadImageA(NULL, fullPath.c_str(), IMAGE_BITMAP, Const::imgWidth, Const::imgHeight, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE)});
    }
}