/* ============================================================
 * ShaderProgram.cpp: Implementation of ShaderProgram class.
 * ============================================================*/

#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Pong {
    /* ==================================================
     * =================== CONSTRUCTOR ==================
     * ==================================================*/
	ShaderProgram::ShaderProgram(const char* vertexCode, const char* fragmentCode) {
        char log[1024];
        int success;

        /* --------------- Create vertex shader --------------- */
        //Create vertex shader.
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexCode, NULL);
        glCompileShader(vertexShader);

        //Check if vertex shader is compiled correctly.
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(vertexShader, 1024, NULL, log);

            std::cout << "***** VERTEX COMPILE ERROR *****" << std::endl;
            std::cout << log << std::endl;

            __debugbreak();
        }
        
        /* --------------- Create fragment shader --------------- */
        //Create fragment shader.
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
        glCompileShader(fragmentShader);

        //Check if fragment shader is compiled correctly.
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 1024, NULL, log);

            std::cout << "***** FRAGMENT COMPILE ERROR *****" << std::endl;
            std::cout << log << std::endl;

            __debugbreak();
        }

        /* --------------- Create shader program --------------- */
        //Create shader program.
        m_Id = glCreateProgram();
        glAttachShader(m_Id, vertexShader);
        glAttachShader(m_Id, fragmentShader);
        glLinkProgram(m_Id);

        //Check if program is linked correctly.
        glGetProgramiv(m_Id, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(m_Id, 1024, NULL, log);

            std::cout << "***** PROGRAM LINK ERROR *****" << std::endl;
            std::cout << log << std::endl;

            __debugbreak();
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
	}

    /* ==================================================
     * =================== DESTRUCTOR ===================
     * ================================================== */
    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(m_Id);
    }

    /* ==================================================
     * ================== METHOD use() ==================
     * ================================================== */
    void ShaderProgram::use() {
        glUseProgram(m_Id);
    }

    /* ==================================================
     * ============= METHOD setUniformVec2() ============
     * ================================================== */
    void ShaderProgram::setUniformVec2(const std::string& name, float value1, float value2) {
        int location = glGetUniformLocation(m_Id, name.c_str());
        glUniform2f(location, value1, value2);
    }
}
