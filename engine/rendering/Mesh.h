#ifndef _PE_MESH_H__
#define _PE_MESH_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace PalmEngine
{
    struct Vertex {
        // position
        glm::vec3 mPosition;
        // normal
        glm::vec3 mNormal;
        // texCoords
        glm::vec2 mTexCoords;
        // tangent
        glm::vec3 mTangent;
        // bitangent
        glm::vec3 mBitangent;
        //bone indexes which will influence this vertex
        int mBoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float mWeights[MAX_BONE_INFLUENCE];
    };

    enum class TextureType
    {
        Albedo,
        Normal
    };

    struct Texture {
        unsigned int mID = 0;
        TextureType mType;
    };

    struct Material {
        Texture mAlbedoTexture;
        Texture mNormalTexture;
    };

    class Mesh {
    public:
        // Mesh Data
        std::vector<Vertex>       mVertices;
        std::vector<unsigned int> mIndices;
        Material mMaterial;

        unsigned int mVAO;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const Material material);

        void Draw(Shader& _shader);

    private:
        // Render Data 
        unsigned int _VBO, _EBO;

        void SetupMesh();
    };
}

#endif