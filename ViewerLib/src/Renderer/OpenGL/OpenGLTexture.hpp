#pragma once
#include "Renderer/Texture.hpp"

namespace VL
{
	namespace OpenGL
	{
		class OpenGLTexture
			: public VL::ITexture
		{
		public:
			OpenGLTexture(const std::string& path, TEXTURE_TYPE type);
			OpenGLTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type);
			~OpenGLTexture() override;
			void bind() const override;
			void bind(uint32_t slot) const override;
			void unbind() const override;
			void generateMipMap(int32_t maxLOD) override;
			void setData(const void* data, size_t size) override;

			uint32_t getWidth() const override;
			uint32_t getHeight() const override;
			[[nodiscard]] uint32_t getId() const override;
			[[nodiscard]] TEXTURE_TYPE getType() const override;

		private:
			void prepareCubeMapTexture(const std::string& imagesPath = NULL);
			void prepare2DTexture(const std::string& imagePath = NULL);
			void create2DTexture();
			void createCubeMap();
			void setParameteri(GLenum parameterName, GLenum parameterValue);
			GLenum typeToGLenum(TEXTURE_TYPE type);


		private:
			GLuint m_id;
			uint32_t m_width;
			uint32_t m_height;
			GLenum m_type;
		};
	}
}
