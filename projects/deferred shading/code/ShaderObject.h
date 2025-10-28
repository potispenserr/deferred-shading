#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
#include "Matrix4D.h"
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderObject {
public:
	ShaderObject(const char* vertexPath, const char* fragmentPath);

	ShaderObject();

	~ShaderObject();

	void use();

	void setMat4(std::string name, Matrix4D matrix);

	void setVec4(std::string name, Vector4D vector);

	void setVec3(std::string name, Vector4D vector);

	void setFloat(std::string name, float number);

	void setInt(std::string name, int number);

	unsigned int ID = 0;

};