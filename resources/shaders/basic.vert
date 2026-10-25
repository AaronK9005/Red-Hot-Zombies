#version core 330
in vec3 aPosition;

int main()
{
    gl_Position = vec4(aPosition, 1.0f);
}