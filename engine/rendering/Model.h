#ifndef _PE_MODEL_H__
#define _PE_MODEL_H__

#include "Mesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace PalmEngine
{
    class Model
    {
    public:
        Model();
        Model(std::string path);
        void Draw(Shader& _shader);

    private:
        // Model Data
        vector<Mesh> _meshes;
        string _directory;

        void LoadModel(string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
            string typeName);
    };
}

#endif