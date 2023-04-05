#include "Client/Client.hpp"
#include "Core/Base.hpp"
#include "Event/Events.hpp"
#include "Assets/AssetManager.hpp"
#include "Renderer/OpenGL/OpenGLBuffer.hpp"
#include "Renderer/OpenGL/OpenGLShader.hpp"
#include "Renderer/OpenGL/OpenGLShaderProgram.hpp"
#include "Renderer/OpenGL/OpenGLVertexArray.hpp"
#include "Memory/StackAllocator.hpp"
#include <memory>

class Viewer : public VL::Client
{
public:
	Viewer() = default;
	~Viewer() = default;
	void start() override;
	void update(VL::StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime) override;
	void renderGUI() override;
	void stop() override;
	void onKeyEvent(std::shared_ptr<VL::KeyPressEvent>& e) override;

private:
	std::shared_ptr<VL::OpenGL::OpenGLShaderProgram> m_program;
	std::unique_ptr<VL::OpenGL::OpenGLVertexArray> m_vertexArray;
	std::shared_ptr<VL::OpenGL::OpenGLVertexBuffer> m_vertexBuffer;
	std::shared_ptr<VL::OpenGL::OpenGLIndexBuffer> m_indexBuffer;
};