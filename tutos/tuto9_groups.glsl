//! \file tuto9_groups.glsl

#version 330

#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;

uniform mat4 mvpMatrix;

void main( )
{
    gl_Position= mvpMatrix * vec4(position, 1);
}

#endif


#ifdef FRAGMENT_SHADER
out vec4 fragment_color;
uniform vec4 material_color;

void main( )
{
    fragment_color= material_color;
}

#endif
