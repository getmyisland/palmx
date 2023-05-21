#ifndef _PE_MESH_H__
#define _PE_MESH_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <vector>
using namespace std;

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

    struct Texture {
        unsigned int mID = 0;
        string mType;
        string mPath;
    };

    class Mesh {
    public:
        // Mesh Data
        vector<Vertex>       mVertices;
        vector<unsigned int> mIndices;
        vector<Texture>      mTextures;
        unsigned int mVAO;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

        void Draw(Shader& _shader);

    private:
        // Render Data 
        unsigned int _VBO, _EBO;

        void SetupMesh();
    };
}

#endif