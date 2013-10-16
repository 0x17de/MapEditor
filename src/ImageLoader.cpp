#include <SDL2/SDL_image.h>
#include "ImageLoader.h"
#include "Image.h"


ImageLoader::ImageLoader()
{
    if ((++getInstanceCount()) == 1)
        IMG_Init(IMG_InitFlags::IMG_INIT_PNG);
}

ImageLoader::~ImageLoader()
{
    if ((--getInstanceCount()) == 0)
        IMG_Quit();
}

int &ImageLoader::getInstanceCount()
{
    static int numberOfInstances = 0;
    return numberOfInstances;
}

Image ImageLoader::load(const std::string &filePath)
{
    return Image(IMG_Load(filePath.c_str()));
}
