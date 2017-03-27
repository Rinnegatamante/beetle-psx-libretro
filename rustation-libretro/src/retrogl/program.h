#ifndef RETROGL_PROGRAM_H
#define RETROGL_PROGRAM_H

#include "shader.h"
#include "error.h"

#include <glsm/glsmsym.h>

#include <map>
#include <string>

#define program_bind(x) (glUseProgram((x)->id))

#define program_uniform1i(x, name, i) \
{ \
   program_bind(x); \
   GLint u = (x)->uniform(name); \
   glUniform1i(u, i); \
}

#define program_uniform1ui(x, name, i) \
{ \
   program_bind(x); \
   GLint u = (x)->uniform(name); \
   glUniform1ui(u, i); \
}

typedef std::map<std::string, GLint> UniformMap;

class Program {
public:
    GLuint id;
    /// Hash map of all the active uniforms in this program
    UniformMap uniforms;

    Program(Shader* vertex_shader, Shader* fragment_shader);
    ~Program();
    GLint find_attribute(const char* attr);
    GLint uniform(const char* name);
    void uniform2i(const char* name, GLint a, GLint b);
    void uniform2ui(const char* name, GLuint a, GLuint b);

    char *info_log;
};


// Return a hashmap of all uniform names contained in `program` with
// their corresponding location.
UniformMap load_program_uniforms(GLuint program);

#endif
