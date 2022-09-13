#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

#include "../Gui/ConsoleLog.hpp"

#pragma once

/**
 * @brief Load, create and use shader
 * 
 */
class Shader
{
public : 
	/**
	 * @brief Create shader program and bind it
	 * 
	 * @param vertexPath 
	 * @param fragmentPath 
	 */
	Shader(const char* vertexPath, const char* fragmentPath);

	/**
	 * @brief Get the shader program id
	 * 
	 * @return shader program id
	 */
	unsigned int GetProgram() const noexcept;

private :
	unsigned int _vertex;
	unsigned int _fragment;
	unsigned int _program;

	std::ifstream _shaderReader;
	std::stringstream _vertexStream;
	std::stringstream _fragmentStream;
	std::string _vertexString;
	std::string _fragmentString;
	const char* _vertexSource = "";
	const char* _fragmentSource = "";
};