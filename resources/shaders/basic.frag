#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform bool useColor;
uniform bool darken;
uniform vec3 color;
uniform sampler2D texture1;

void main()
{
    if (useColor)
        FragColor = vec4(color, 1.0f);
    else
        FragColor = texture(texture1, TexCoords);
    
    if (darken)
    {
        FragColor.rgb = max(FragColor.rgb - vec3(0.1f), vec3(0.0f));
    }
}