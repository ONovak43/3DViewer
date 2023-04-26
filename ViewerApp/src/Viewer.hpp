#include "Client/Client.hpp"
#include "Core/Base.hpp"
#include "Event/Events.hpp"
#include "Renderer/IShaderProgram.hpp"
#include "Memory/StackAllocator.hpp"
#include "Renderer/Renderer.hpp"
#include "ModelRenderer.hpp"
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
	void setRenderer(VL::Renderer* renderer) override;

	// Events
	void onKeyPressedEvent(std::shared_ptr<VL::KeyPressEvent>& e) override;
	void onMouseMovedEvent(std::shared_ptr<VL::MouseMovedEvent>& e) override;

private:
	VL::Renderer* m_renderer;
	std::unique_ptr<ModelRenderer> m_modelRenderer;
	std::shared_ptr<VL::IShaderProgram> m_program;
	float m_rotation = 0;
};