#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//Read shaders and load it 
	_shaderReader.open(vertexPath);
	if (_shaderReader.is_open())
	{
		_vertexStream << _shaderReader.rdbuf();
		_vertexString = _vertexStream.str();
		_vertexSource = _vertexString.c_str();
		_shaderReader.close();
	}
	else
	{
		ConsoleLog::GetInstance()->AddLog("[ERROR] Vertex shader is not found\n");
		return;
	}

	_shaderReader.open(fragmentPath);
	if (_shaderReader.is_open())
	{
		_fragmentStream << _shaderReader.rdbuf();
		_fragmentString = _fragmentStream.str();
		_fragmentSource = _fragmentString.c_str();
		_shaderReader.close();
	}
	else
	{
		ConsoleLog::GetInstance()->AddLog("[ERROR] Fragment shader is not found\n");
		return;
	}

	_vertex = glCreateShader(GL_VERTEX_SHADER);
	_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_vertex, 1, &_vertexSource, NULL);
	glShaderSource(_fragment, 1, &_fragmentSource, NULL);
	glCompileShader(_vertex);
	glCompileShader(_fragment);

	//Check shader compilation
	int success = 0;
	char logError[512];
	glGetShaderiv(_vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		ConsoleLog::GetInstance()->AddLog("[ERROR] Vertex shader compilation failed\n");
		glGetShaderInfoLog(_vertex, sizeof(logError), NULL, logError);
		ConsoleLog::GetInstance()->AddLog(logError);
		ConsoleLog::GetInstance()->AddLog("\n");
	}

	glGetShaderiv(_fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		ConsoleLog::GetInstance()->AddLog("[ERROR] Fragment shader compilation failed\n");
		glGetShaderInfoLog(_fragment, sizeof(logError), NULL, logError);
		ConsoleLog::GetInstance()->AddLog(logError);
		ConsoleLog::GetInstance()->AddLog("\n");
	}

	_program = glCreateProgram();
	glAttachShader(_program, _vertex);
	glAttachShader(_program, _fragment);
	glLinkProgram(_program);
	glDetachShader(_program, _vertex);
	glDetachShader(_program, _fragment);
	glDeleteShader(_vertex);
	glDeleteShader(_fragment);
    glUseProgram(_program);
}

unsigned int Shader::GetProgram() const noexcept
{
	return _program;
}