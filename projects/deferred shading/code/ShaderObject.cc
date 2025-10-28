#include "ShaderObject.h"

ShaderObject::ShaderObject(const char* vertexPath, const char* fragmentPath)
{
    std::string vertCode;
    std::string fragCode;
    std::ifstream vertShaderFile;
    std::ifstream fragShaderFile;

    vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertShaderFile.open(vertexPath);

		fragShaderFile.open(fragmentPath);


		std::stringstream vertShaderStream;
		std::stringstream fragShaderStream;

		

		vertShaderStream << vertShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vertCode = vertShaderStream.str();
		fragCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure exception)
	{
		std::cout << "Shaders didn't sucessfully load" << "\n";
		std::cout << "Failure reason: " << exception.what() << "\n";
	}

	const char* vertShaderCode = vertCode.c_str();
	const char* fragShaderCode = fragCode.c_str();

	unsigned int vert;
	unsigned int frag;
	int success;
	
	char info[512];

	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertShaderCode, NULL);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vert, 512, NULL, info);
		std::cout << "Vertex shader failed to compile" << "\n";
	}

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragShaderCode, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(frag, 512, NULL, info);
		std::cout << "Fragment shader failed to compile" << "\n";
	}

	ID = glCreateProgram();
	glAttachShader(ID, vert);
	glAttachShader(ID, frag);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "Shader linking failed" << "\n";
	}

	glDeleteShader(vert);
	glDeleteShader(frag);
    
}

ShaderObject::ShaderObject()
{
}

ShaderObject::~ShaderObject()
{
}

void ShaderObject::use()
{
	glUseProgram(ID);
}

void ShaderObject::setMat4(std::string name, Matrix4D matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void ShaderObject::setVec4(std::string name, Vector4D vector)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), vector.x(), vector.y(), vector.z(), vector.w());
}

void ShaderObject::setVec3(std::string name, Vector4D vector)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x(), vector.y(), vector.z());
}

void ShaderObject::setFloat(std::string name, float number)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), number);
}

void ShaderObject::setInt(std::string name, int number)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), number);
}


