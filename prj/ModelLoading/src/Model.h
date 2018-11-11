#ifndef MODEL_H
#define MODEL_H

#include "learnopengl/Shader.h"
#include "Mesh.h"

#include <vector>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
    Model(char* path);

public:
    void Draw(Shader shader);

private:
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    // 模型数据
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
};

#endif