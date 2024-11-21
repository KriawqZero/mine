//
// Created by Marcilio on 21/11/2024.
//

#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include <glm/vec3.hpp>

#include "../../Texture/Texture.hpp"

namespace World {
    class Primitive {
        protected:
            unsigned int primitiveID;
            glm::vec3 worldPosition;
            Texture texture;

        public:
            explicit Primitive(glm::vec3 worldPosition);
            ~Primitive();
            void setPosition(glm::vec3 newPosition);
            void Render() const;

            std::string getPosition() const;
    };
}

#endif //PRIMITIVE_HPP
