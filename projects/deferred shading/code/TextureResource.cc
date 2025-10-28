#include "TextureResource.h"
#include "stb_image.h"
#include <iostream>

TextureResource::TextureResource(std::string pathToFile)
{
	loadTex(pathToFile, false);
}

// sets all texture parameters
void TextureResource::setTexParam(int wrapS, int wrapT, int minFilter, int magFilter) {
	if( minFilter && magFilter == -1){
		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
	}
	//texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}


///loads texture data from stbi and generates mipmaps
void TextureResource::loadTex(std::string path, bool inverted) {
	stbi_set_flip_vertically_on_load(inverted);
	glGenTextures(1, &texID);

	texPictureData = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
	if (texPictureData) {
		if (this->nChannels == 3) {
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texPictureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (this->nChannels == 4) {
			glBindTexture(GL_TEXTURE_2D, texID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texPictureData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		std::cout << "Hey you actually hit something" << "\n";
	}
	else {
		std::cout << stbi_failure_reason() << "\n";
		std::cout << "Nice shootin' Tex" << "\n";
	}
	stbi_image_free(texPictureData);
	
}

