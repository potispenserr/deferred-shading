#include "GraphicsNode.h"
#include <stdexcept>

GraphicsNode::GraphicsNode()
{
}

GraphicsNode::GraphicsNode(MeshResource newMesh, TextureResource newTexture, ShaderObject newShader, Matrix4D newTransform)
{
	mesh = std::make_shared<MeshResource>(newMesh);
	texture = std::make_shared<TextureResource>(newTexture);
	shader = std::make_shared<ShaderObject>(newShader);
	transform = newTransform;
}

GraphicsNode::GraphicsNode(GraphicsNode& gn)
{
	mesh = gn.mesh;
	texture = gn.texture;
	shader = gn.shader;
	transform = gn.transform;

}


GraphicsNode::~GraphicsNode()
{
}

std::shared_ptr<MeshResource>& GraphicsNode::getMesh()
{
	return mesh;
}

std::shared_ptr<TextureResource>& GraphicsNode::getTexture()
{
	return texture;
}

std::shared_ptr<ShaderObject>& GraphicsNode::getShader()
{
	return shader;
}

void GraphicsNode::setMesh(std::shared_ptr<MeshResource>& newMesh)
{
	mesh = newMesh;
}

void GraphicsNode::setTexture(std::shared_ptr<TextureResource>& newTexture)
{
	texture = newTexture;
}

void GraphicsNode::setNormalMap(std::shared_ptr<TextureResource>& newNormalMap)
{
	normalMap = newNormalMap;
}

void GraphicsNode::setShader(std::shared_ptr<ShaderObject>& newShader)
{
	shader = newShader;
}

void GraphicsNode::setTransform(Vector4D newTransform)
{
	transform = transform.translation(newTransform);
}
void GraphicsNode::setTransform(Matrix4D newTransform)
{
	transform = newTransform;
}

void GraphicsNode::updateTransform(Matrix4D transformToAdd)
{
	transform = transform * transformToAdd;
}

Matrix4D& GraphicsNode::getTransform()
{
	return transform;
}

void GraphicsNode::initTexture(std::string path) {
	if (this->mesh.get()->isGLTF == true)
	{
		tinygltf::Model model = mesh.get()->glTFModel;
		if(model.textures.size() > 0){
			const int textureImageI = model.textures[0].source;
			std::string textureImageFile = model.images[0].uri;
			texture.get()->loadTex("./resources/" + textureImageFile, false);

			if(model.samplers.size() > 0){

				const int textureSamplerI = model.textures[0].sampler;
				const auto sampler = model.samplers[0];

				texture.get()->setTexParam(sampler.wrapS, sampler.wrapT, sampler.minFilter, sampler.magFilter);

			}
			
			else {
				texture.get()->setTexParam();
				}
			if(model.meshes[0].primitives[0].attributes.find("TANGENT") != model.meshes[0].primitives[0].attributes.end()) {
					const std::string normalMapImage = model.images[2].uri;
					normalMap.get()->loadTex("./resources/" + normalMapImage, false);
					std::cout << "loading normal map as well" << "\n";

			}
			return;
		}
	}
	texture.get()->loadTex(path, true);
	texture.get()->setTexParam();
	

}


void GraphicsNode::draw(Camera& cam, Matrix4D& projection, Vector4D& lightPosition)
{	
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.get()->texID);
	
	if(mesh.get()->isGLTF == true){

		if(normalMap.get() != 0x0){
			if(normalMap.get()->texPictureData != NULL){
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, normalMap.get()->texID);
			}
		}

		for(auto nodeIt = mesh.get()->glTFModel.nodes.begin();  nodeIt != mesh.get()->glTFModel.nodes.end(); ++nodeIt){
			auto node = *nodeIt;
			
			auto model = mesh.get()->glTFModel;

			const auto &glTFmesh = model.meshes[node.mesh];
            const auto vaoRange = mesh.get()->meshIndexToVAORange[node.mesh];
            for (size_t primitiveI = 0; primitiveI < glTFmesh.primitives.size(); primitiveI++) {
              const auto vao = mesh.get()->vaos[vaoRange[0] + primitiveI];
              const auto &primitive = glTFmesh.primitives[primitiveI];
              glBindVertexArray(vao);

              if (primitive.indices >= 0) {
                const auto &accessor = model.accessors[primitive.indices];
                const auto &bufferView = model.bufferViews[accessor.bufferView];
                const auto byteOffset = accessor.byteOffset + bufferView.byteOffset;
                glDrawElements(primitive.mode, accessor.count, 
					accessor.componentType, (void *)byteOffset);
              } else {

                const auto accessorI = (*begin(primitive.attributes)).second;
                const auto &accessor = model.accessors[accessorI];
                glDrawArrays(primitive.mode, 0, accessor.count);
              }
            }
        }
		return;
	}
	glBindVertexArray(mesh.get()->vertexarray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.get()->indexbuffer);
	glDrawElements(GL_TRIANGLES, mesh.get()->indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, mesh.get()->verticies.size());

}



void GraphicsNode::clearMemory()
{
	glDeleteVertexArrays(1, &mesh.get()->vertexarray);
	glDeleteBuffers(1, &mesh.get()->vertexbuffer);
	glDeleteBuffers(1, &mesh.get()->indexbuffer);
}