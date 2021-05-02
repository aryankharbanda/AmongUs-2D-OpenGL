#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 fragLocation;

// output data
out vec3 color;

uniform int status;

float light_intensity = 0.5;
vec3 light_color = vec3(0.999, 0.999, 0.999);
vec3 ambience = vec3(0.3, 0.3, 0.3);

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    color = fragColor;
    if(status == 0)
    {
        float distance = distance(vec2(0, 0), fragLocation.xy);
        if(distance > 0.5)
            color = vec3(242.0/256.0, 241.0/256.0, 239.0/256.0);
        else
        {
            float diffuse = 0.0;
            if(distance <= light_intensity)
                diffuse = 1.0 - abs(distance / light_intensity);
            color = vec3(min(color.rgb * ((light_color * diffuse) + ambience), color.rgb));        
        }
    }
}
