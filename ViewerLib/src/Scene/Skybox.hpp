#pragma once
#include <Renderer/Renderer.hpp>
namespace VL
{
	class Skybox
	{
	public:
		Skybox(const std::string& shaderPath, 
			const std::string& texturesPath, 
			Renderer* renderer, 
			const std::string& uniformName = "cubeMap");
		~Skybox() = default;
		void render();
	private:
		const std::array<float, 24> m_skyboxVertices
		{
			-1.f, -1.f,  1.f,
			 1.f, -1.f,  1.f,
			 1.f, -1.f, -1.f,
			-1.f, -1.f, -1.f,
			-1.f,  1.f,  1.f,
			 1.f,  1.f,  1.f,
			 1.f,  1.f, -1.f,
			-1.f,  1.f, -1.f,
		};

		const std::vector<uint32_t> m_skyboxIndices =
		{
			// Right
			1, 2, 6,
			6, 5, 1,
			// Left
			0, 4, 7,
			7, 3, 0,
			// Top
			4, 5, 6,
			6, 7, 4,
			// Bottom
			0, 3, 2,
			2, 1, 0,
			// Back
			0, 1, 5,
			5, 4, 0,
			// Front
			3, 7, 6,
			6, 2, 3,
		};
		std::string m_uniformName;
		Renderer* m_renderer;
		std::shared_ptr<IVertexArray> m_vertexArray;
		std::shared_ptr<ITexture> m_texture;
		std::shared_ptr<IShaderProgram> m_program;
	};
}

