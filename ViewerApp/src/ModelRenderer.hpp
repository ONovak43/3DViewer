#pragma once
#include <vector>
#include "Scene/Model.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Buffer.hpp"
#include <Renderer/IShaderProgram.hpp>
#include <Renderer/Renderer.hpp>

class ModelRenderer
{
public:
	ModelRenderer(const std::string& modelPath, VL::Renderer* renderer);
	~ModelRenderer() = default;
	void draw(std::shared_ptr<VL::IShaderProgram>& program);

private:
	void prepareMesh(const VL::Mesh& mesh);
	void prepareTextures(std::vector<VL::Mesh>& meshes, uint32_t meshId, std::shared_ptr<VL::IShaderProgram>& program);

private:
	std::shared_ptr<VL::Model> m_model;
	VL::Renderer* m_renderer;
	std::vector<std::shared_ptr<VL::IVertexArray>> m_vertexArray;
};

