#pragma once
#include "Vector4D.h"
#include "GraphicsNode.h"
class LightNode
{
public:

	LightNode(std::shared_ptr<ShaderObject>& lighting);
	~LightNode();
	Vector4D lightPos;
	Vector4D lightColor;
	//intensity ranges from 0 - 1
	float intensity = 0;
	std::shared_ptr<ShaderObject> lightShader;
	unsigned int lightVAO = -1;


	void setupLighting();

	void updateLighting(Camera cam, Matrix4D projection, GraphicsNode& lightCube);



private:

};

