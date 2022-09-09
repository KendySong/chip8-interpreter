#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <glad/glad.h>

#pragma once
class Shader
{
	//Attributes and properties
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

public : 
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int GetProgram() const noexcept;
};