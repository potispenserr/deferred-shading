#include "LightNode.h"
#include <stb_image.h>
LightNode::LightNode(std::shared_ptr<ShaderObject>& lighting)
{
	lightShader = lighting;

}

LightNode::~LightNode()
{

}


void LightNode::setupLighting()
{	

	lightShader.get()->use();
	lightShader.get()->setVec3(std::string("lightColor"), lightColor);
	lightShader.get()->setFloat(std::string("ambientIntensity"), 0.1f);

	lightShader.get()->setInt(std::string("material.textureDiffuse"), 0);
	lightShader.get()->setVec3(std::string("material.textureSpecular"), Vector4D(0.5f, 0.5f, 0.5f));
	lightShader.get()->setFloat(std::string("material.shininess"), 64.0f);

	lightShader.get()->setVec3(std::string("light.ambient"), Vector4D(0.2f, 0.2f, 0.2f));
	lightShader.get()->setVec3(std::string("light.diffuse"), Vector4D(0.5f, 0.5f, 0.5f));
	lightShader.get()->setVec3(std::string("light.specular"), Vector4D(1.0f, 1.0f, 1.0f));

	


}

void LightNode::updateLighting(Camera cam, Matrix4D projection, GraphicsNode& lightCube)
{
	lightCube.setTransform(Matrix4D::translation(lightPos));
	lightCube.updateTransform(Matrix4D::scale(Vector4D(0.2f, 0.2f, 0.2f)));

	
}


