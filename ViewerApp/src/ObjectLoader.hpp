#pragma once
#include "Scene/Model.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Texture.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <string>
#include <vector>

class ObjectLoader
{
	using TexturesVector = std::vector<std::shared_ptr<VL::ITexture>>;
public:
	ObjectLoader(VL::Renderer* renderer);
	std::shared_ptr<VL::Model> loadModel(const std::string& path);
private:
	void processNode(aiNode* node, const aiScene* scene);
	VL::Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	TexturesVector loadMaterialTextures(aiMaterial* mat, aiTextureType type);
private:
	std::string m_directory;
	std::shared_ptr<VL::Model> m_model;
	VL::Renderer* m_renderer;
};

