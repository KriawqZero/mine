//
// Created by Marcilio on 18/11/2024.
//

#include "Sphere.hpp"

#include <cmath>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp>

#include "../../debug/colors.h"

namespace World {
    void Sphere::drawSphere(const GLfloat radius, const GLfloat nStacks, const GLfloat nSectors) {
        std::vector<std::vector<GLuint>> indexes;
        std::vector<glm::vec3> positions;
        constexpr GLfloat PI = 3.14159265358979323846f;

        const GLfloat deltaPhi = PI / nStacks;
        const GLfloat deltaTheta = 2 * PI / nSectors;

        for (GLfloat i = 0; i <= nStacks; i++) {
            const GLfloat phi = -PI / 2 + i * deltaPhi;
            const auto temp = static_cast<GLfloat>(radius * cos(phi));
            auto y = static_cast<GLfloat>(radius * sin(phi));

            std::vector<GLuint> point;

            for (GLfloat j = 0; j < nSectors; j++) {
                const GLfloat theta = j * deltaTheta;
                auto x = static_cast<GLfloat>(temp) * sin(theta);
                auto z = static_cast<GLfloat>(temp) * cos(theta);

                positions.emplace_back(x, y, z);
                GLuint index = positions.size() -1;
                point.push_back(index);
            }
            indexes.push_back(point);
        }



        glColor3fv(laranja);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);

        glFrontFace(GL_CCW);

        glCullFace(GL_BACK);

        for(GLuint i = 0; static_cast<GLfloat>(i) < nStacks; i++) {
            //
            // if(i%3 == 0) glColor3fv(branco);
            // else if (i%3 == 1) glColor3fv(laranja);
            // else glColor3fv(cinza);

            glBegin(GL_TRIANGLE_STRIP);
            for(GLfloat j = 0; j < nSectors; j++) {
                GLuint index = indexes[i][j]; // NOLINT(*-narrowing-conversions)
                glVertex3fv(&positions[index].x);
                index = indexes[i+1][j]; // NOLINT(*-narrowing-conversions)
                glVertex3fv(&positions[index].x);

                if(j == nSectors - 1) {
                    index = indexes[i][0];
                    glVertex3fv(&positions[index].x);
                    index = indexes[i+1][0];
                    glVertex3fv(&positions[index].x);
                }
            }
            glDisable(GL_CULL_FACE);
            glEnd();
        }
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // glColor3f(1.0f, 0.0f, 0.0f);
        // glPointSize(2.5);
        // glBegin(GL_TRIANGLE_STRIP);
        // for (GLuint i = 0; i < positions.size(); i++) {
        //     glVertex3fv(&positions[i].x);
        // }
        // glEnd();
    }
}
