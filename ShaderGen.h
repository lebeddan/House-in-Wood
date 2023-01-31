//----------------------------------------------------------------------------------------
/**
 * \file    ShaderGen.h
 * \author  Lebedev Daniil
 * \date    2022
 * \brief   A class that load and prepares shader to use
 */
 //----------------------------------------------------------------------------------------


#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/// Class that holds and use info about shaders programs.
class ShaderGen
{
public:
	unsigned int ID;///<ID of a shader program


	/// Constructor
	/**
	  Constructor used vertex path and fragment path

	  \param[in] vertexPath where vertex shader is stored.
	  \param[in] fragmentPath where fragment shader is stored.
	*/
	ShaderGen(const char* vertexPath, const char* fragmentPath);

	
	/// Use/Activate program
	/**
	  Function that activate shader program
	*/
	void use();
};

ShaderGen::ShaderGen(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	// Read vertex and fragment shaders files
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: SHADER FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	int vertexShader, fragmentShader;
	int success;
	char infoLog[512];
	
	// Create vertex shader 
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER VERTEX COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create fragment shader 
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER FRAGMENT COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER PROGRAM LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderGen::use()
{
	glUseProgram(ID);
}



#endif


