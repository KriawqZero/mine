//
// Created by Marcilio on 20/11/2024.
//

#ifndef TEXTURA_H
#define TEXTURA_H
#include <iostream>
#include <vector>

class Texture {
    unsigned int id;
    int width, height, channels;
    public:
        Texture();
        ~Texture();

        void loadTexture(const std::string& filePath);
        void loadCubemap(const std::vector<std::string>& faces);

        void bind() const;
        static void unbind();
};

#endif //TEXTURA_H
