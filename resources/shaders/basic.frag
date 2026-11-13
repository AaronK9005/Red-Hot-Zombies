#version 330 core
out vec4 FragColor;

uniform vec3 player_color;

void main()
{
    FragColor = vec4(player_color, 1.0f);
}