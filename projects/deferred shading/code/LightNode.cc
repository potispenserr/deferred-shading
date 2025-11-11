#include "LightNode.h"
#include <stb_image.h>
LightNode::LightNode(std::shared_ptr<ShaderObject>& lighting)
{
	lightShader = lighting;

}

LightNode::~LightNode()
{

}


void LightNode::setupLighting(Vector4D lightPosition)
{	

	lightShader.get()->use();
	lightShader.get()->setInt("gPosition", 0);
	lightShader.get()->setInt("gNormal", 1);
	lightShader.get()->setInt("gAlbedo", 2);

	


}

void LightNode::updateLighting(Camera cam, Matrix4D projection, GraphicsNode& lightCube, Vector4D& color)
{
	lightCube.setTransform(Matrix4D::translation(lightPos));
	lightCube.updateTransform(Matrix4D::scale(Vector4D(0.2f, 0.2f, 0.2f)));
	

	
}


