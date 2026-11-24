#include "platform/debug.hpp"

GLenum glCheckError_(const char* file, const char* function, int line)
{
    GLenum error_code;
    while ((error_code = glGetError() != GL_NO_ERROR))
    {
        std::string_view err_sv;
        switch (error_code)
        {
        case GL_INVALID_ENUM:                   err_sv = "GL_INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                  err_sv = "GL_INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:              err_sv = "GL_INVALID_OPERATION"; break;
        // case GL_STACK_OVERFLOW:                 err_sv = "GL_STACK_OVERFLOW"; break;
        // case GL_STACK_UNDERFLOW:                err_sv = "GL_STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                  err_sv = "GL_OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  err_sv = "INVALID_FRAMEBUFFER_OPERATION"; break;
        
        default: err_sv = "UNKNOWN_ERROR_CODE"; break;
        }

        std::cout << std::format("{} ({})| {}, {}, line {}", err_sv, error_code, file, function, line);
    }
    
    return error_code;
}
