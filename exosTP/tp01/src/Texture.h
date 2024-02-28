#pragma once

#include "stbimage/stb_image.h"
#include <glad/glad.h>
#include <string>



class Texture
{
public:
	Texture();
	Texture(std::string fileLoc);
	~Texture();

	void LoadTexture();
	void UseTexture();
	void ClearTexture();



private:
	GLuint textureID;
	int width, height, bitDepth;
	std::string fileLocation;
};

