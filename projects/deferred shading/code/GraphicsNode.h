#pragma once
#include "core/app.h"
#include "render/window.h"
#include "config.h"
#include "mesh.h"
#include "TextureResource.h"
#include "ShaderObject.h"
#include "Matrix4D.h"
#include "Camera.h"
#include <memory>


class GraphicsNode
{
public:
	GraphicsNode();
	GraphicsNode(MeshResource newMesh, TextureResource newTexture, ShaderObject newShader, Matrix4D newTransform);
	GraphicsNode(GraphicsNode& gn);



	~GraphicsNode();

	std::shared_ptr<MeshResource>& getMesh();
	std::shared_ptr<TextureResource>& getTexture();
	std::shared_ptr<ShaderObject>& getShader();

	void setMesh(std::shared_ptr<MeshResource>& newMesh);
	void setTexture(std::shared_ptr<TextureResource>& newTexture);
	void setNormalMap(std::shared_ptr<TextureResource>& newNormalMap);
	void setShader(std::shared_ptr<ShaderObject>& newShader);

	void setTransform(Vector4D newTransform);
	void setTransform(Matrix4D newTransform);
	void updateTransform(Matrix4D transformToAdd);
	Matrix4D& getTransform();

	void initTexture(std::string path);


	void draw(Camera& cam, Matrix4D& projection, Vector4D& lightPosition);


	void clearMemory();


	

private:
	std::shared_ptr<MeshResource> mesh;
	std::shared_ptr<TextureResource> texture;
	std::shared_ptr<TextureResource> normalMap;
	std::shared_ptr<ShaderObject> shader;
	Matrix4D transform;


};
