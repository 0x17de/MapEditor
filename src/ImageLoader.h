#ifndef IMAGELOADER_H_INCLUDED
#define IMAGELOADER_H_INCLUDED


#include <string>

class Image;
class ImageLoader
{
public:
    ImageLoader();
    ~ImageLoader();

    Image load(const std::string &filePath);

private:
    int &getInstanceCount();
};


#endif // IMAGELOADER_H_INCLUDED
