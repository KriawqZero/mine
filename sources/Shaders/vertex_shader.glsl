#version 330 core
layout(location = 0) in vec3 aPos; // Posição do vértice (entrada do shader)

uniform mat4 model;      // Matriz de transformação do modelo
uniform mat4 view;       // Matriz de visualização (câmera)
uniform mat4 projection; // Matriz de projeção (perspectiva)

void main() {
    // Calcula a posição final do vértice no espaço da tela
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
