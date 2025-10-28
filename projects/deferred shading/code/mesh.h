#pragma once
#include <vector>
#include "Matrix4D.h"
#include "Vector4D.h"
#include "core/app.h"
#include "render/window.h"
#include "config.h"
#include <map>
#include "tiny_gltf.h"


struct Vertex {
    Vector4D position;
    Vector4D meshNorm;
    Vector4D texCoord;
    Vertex(Vector4D newPos, Vector4D newNorm, Vector4D newTexCoord) :
        position(newPos), meshNorm(newNorm), texCoord(newTexCoord) {}
	bool operator < (const Vertex rhs) const noexcept {
		return memcmp((void*) this, (void*)& rhs, sizeof(Vertex)) > 0;
	}
};

struct Texture {
    unsigned int id;
    std::string type;
};

class MeshResource {
public:
	MeshResource() {
	}

	~MeshResource() {
	}
    

    std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	unsigned int vertexarray = 0;
	unsigned int vertexbuffer = 0;
	unsigned int indexbuffer = 0;
    unsigned int textureBuffer = 0;

	tinygltf::Model glTFModel;

	bool isGLTF = false;
	std::vector<GLuint> vbos;
	std::vector<GLuint> vaos;
	std::vector<std::vector<GLuint>> meshIndexToVAORange;

	void setattrib();

	void loadObj(std::string pathToFile);
	void loadGLTF(std::string pathToFile);

	void genGLTFVertexArray();

	void genvertexarray();

	void genvertexbuffer();

	void indexVertices(const std::vector<Vertex>& verts);

    void setVertices(const std::vector<Vertex>& newVertices);

	bool findMatchingVertexInMap(const Vertex& vertToFind, const std::map<Vertex, unsigned int>& vertMap, unsigned int& resultingIndex);

};