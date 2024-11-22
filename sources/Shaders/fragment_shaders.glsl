#version 330 core
out vec4 FragColor; // Cor final do fragmento (saída do shader)

uniform vec3 objectColor; // Cor do objeto

void main() {
    FragColor = vec4(objectColor, 1.0); // Define a cor do fragmento com transparência 1.0
}
