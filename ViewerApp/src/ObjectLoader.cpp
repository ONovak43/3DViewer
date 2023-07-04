#include "ObjectLoader.hpp"

using TexturesVector = std::vector<std::shared_ptr<VL::ITexture>>;

ObjectLoader::ObjectLoader(VL::Renderer* renderer)
    : m_renderer(renderer), m_model(std::make_shared<VL::Model>()), m_directory()
{
}

std::shared_ptr<VL::Model> ObjectLoader::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << "\n";
        return nullptr;
    }

    m_directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);

    aiVector3D minPoint, maxPoint;
    bool hasBounds = false;

    for (auto& mesh : m_model->getMeshes())
    {
        for (auto& vertex : mesh.m_vertices)
        {
            if (!hasBounds)
            {
                minPoint = maxPoint = aiVector3D(vertex.m_position[0], vertex.m_position[1], vertex.m_position[2]);
                hasBounds = true;
            }
            else
            {
                minPoint.x = std::min(minPoint.x, vertex.m_position[0]);
                minPoint.y = std::min(minPoint.y, vertex.m_position[1]);
                minPoint.z = std::min(minPoint.z, vertex.m_position[2]);

                maxPoint.x = std::max(maxPoint.x, vertex.m_position[0]);
                maxPoint.y = std::max(maxPoint.y, vertex.m_position[1]);
                maxPoint.z = std::max(maxPoint.z, vertex.m_position[2]);
            }
        }
    }

    m_model->setWidth(maxPoint.x - minPoint.x);
    m_model->setHeight(maxPoint.y - minPoint.y);
    m_model->setDepth(maxPoint.z - minPoint.z);

    return m_model;
}

void ObjectLoader::processNode(aiNode* node, const aiScene* scene)
{
    for (auto i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_model->addMesh(processMesh(mesh, scene));
    }

    for (auto i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

VL::Mesh ObjectLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<VL::Vertex> vertices;
    std::vector<uint32_t> indices;    
    TexturesVector textures;

    for (auto i = 0; i < mesh->mNumVertices; i++)
    {
        VL::Vertex vertex;
        vertex.m_position = VL::vec3(
            std::array{ mesh->mVertices[i].x , mesh->mVertices[i].y, mesh->mVertices[i].z }
        );

        if (mesh->HasNormals())
        {
            vertex.m_normal = VL::vec3(
                std::array{ mesh->mNormals[i].x , mesh->mNormals[i].y, mesh->mNormals[i].z }
            );
        }

        if (mesh->mTextureCoords[0])
        {
            vertex.m_uv = VL::vec2(
                std::array{ mesh->mTextureCoords[0][i].x , mesh->mTextureCoords[0][i].y }
            );
        }
        else {
            vertex.m_uv = VL::vec2(
                std::array{ 0.0f, 0.0f }
            );
        }

        vertices.push_back(vertex);
    }

    for (auto i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (auto j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    auto outputMesh = VL::Mesh(vertices, indices);

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    outputMesh.m_texturesDiffuse = loadMaterialTextures(material, aiTextureType_DIFFUSE);

    outputMesh.m_texturesSpecular = loadMaterialTextures(material, aiTextureType_SPECULAR);

    outputMesh.m_texturesNormal = loadMaterialTextures(material, aiTextureType_HEIGHT);

    outputMesh.m_texturesHeight = loadMaterialTextures(material, aiTextureType_AMBIENT);

    return outputMesh;
}


TexturesVector ObjectLoader::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
    TexturesVector textures;
    auto textureCount = mat->GetTextureCount(type);

    for (auto i = 0; i < textureCount; i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string filename = str.C_Str();
        auto path = m_directory + "/" + filename;
        auto texture = m_renderer->loadTexture(path, VL::TEXTURE_TYPE::TEXTURE_2D); 
        texture->generateMipMap(1000);
        textures.emplace_back(texture);
    }
    return textures;
}
