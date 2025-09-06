//
// Created by Marcilio on 20/11/2024.
//

#include "Texture.hpp"
#include <iostream>
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/stb/stb_image.h"

void Texture::loadTexture(const std::string& filePath) {
    const unsigned char *imgData =
        stbi_load(filePath.c_str(), &width, &height, &channels, 4);

    if (!imgData) {std::cerr << "Error loading image: " << filePath << std::endl; return;}

    glGenTextures(1, &id);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, imgData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unbind();

    stbi_image_free(const_cast<unsigned char*>(imgData));
}

void Texture::loadCubemap(const std::vector<std::string>& faces) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int width, height, channels;
    for (GLuint i = 0; i < faces.size(); i++) {
        if (unsigned char* data = stbi_load(faces[i].c_str(),
            &width, &height, &channels, 0)) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load cubemap texture: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


Texture::Texture(): id(0), width(0), height(0), channels(0) {
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
