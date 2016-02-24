
#ifndef _PROGRAM_H
#define _PROGRAM_H

#define GLEW_NO_GLU
#include "GL/glew.h"

#include "vec.h"
#include "mat.h"

//! recompile un shader program.
int reload_program( const GLuint program, const char *filename );
//! cree un shader program, charge un seul fichier, les shaders sont separes par #ifdef VERTEX_SHADER / #endif et #ifdef FRAGMENT_SHADER / #endif.
GLuint read_program( const char *filename );

//! recompile un shader program + definitions #define what value\n.
int reload_program_definitions( const GLuint program, const char *filename, const char *definitions );
//! cree un shader program, charge un seul fichier, les shaders sont separes par #ifdef VERTEX_SHADER / #endif et #ifdef FRAGMENT_SHADER / #endif + definitions #define what value\n.
GLuint read_program_definitions( const char *filename, const char *definitions );

//! recompile un shader program.
int reload_program_definitions( const GLuint program, const char *vertex_filename, const char *fragment_filename, const char *definitions );
//! cree un shader program, a partir des sources vertex et fragment et des definitions #define what value\n.
GLuint read_program_definitions( const char *vertex_filename, const char *fragment_filename, const char *definitions );

//! recompile un shader program.
int reload_program( const GLuint program, const char *vertex, const char *fragment );
//! cree un shader program, a partir des sources vertex et fragment 
GLuint read_program( const char *vertex, const char *fragment );

//! renvoie l'indice d'un attribut declare dans le vertex shader.
GLint program_attribute( const GLuint program, const char *attribute );

//! affecte une valeur a un uniform du shader program.
void program_uniform( const GLuint program, const char *uniform, const unsigned int v );
void program_uniform( const GLuint program, const char *uniform, const int v );
void program_uniform( const GLuint program, const char *uniform, const float v );
void program_uniform( const GLuint program, const char *uniform, const vec2& v );
void program_uniform( const GLuint program, const char *uniform, const vec3& v );
void program_uniform( const GLuint program, const char *uniform, const Point& v );
void program_uniform( const GLuint program, const char *uniform, const Vector& v );
void program_uniform( const GLuint program, const char *uniform, const vec4& v );
void program_uniform( const GLuint program, const char *uniform, const Transform& v );

//! configure le pipeline et le shader program pour utiliser une texture.
void program_use_texture( const GLuint program, const char *sampler, const int unit, const GLuint texture );

#endif
