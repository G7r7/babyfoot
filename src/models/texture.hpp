#ifndef TEXH
#define TEXH

class Texture
{
private:
    int width, height, nbChannels;
    unsigned char *data;
public:
    Texture(char* path);
    int getWidth();
    int getHeight();
    int getNbChannels();
    unsigned char* getData();
    ~Texture();
};

#endif