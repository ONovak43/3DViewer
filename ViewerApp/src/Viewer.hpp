#include "Client/Client.hpp"
#include "Core/Base.hpp"
#include "Event/Events.hpp"
#include "Renderer/IShaderProgram.hpp"
#include "Memory/StackAllocator.hpp"
#include "Renderer/Renderer.hpp"
#include "ModelRenderer.hpp"
#include "Camera.hpp"

#include <memory>

class Viewer : public VL::Client
{
public:
	enum class KEY_EVENT_TYPE
	{
		PRESSED,
		RELEASED
	};
	Viewer();
	~Viewer() = default;
	void start() override;
	void update(VL::StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime) override;
	void renderGUI() override;
	void stop() override;
	void setRenderer(VL::Renderer* renderer) override;

	// Events
	void onKeyPressedEvent(const std::shared_ptr<VL::KeyPressEvent>& e) override;
	void onKeyReleasedEvent(const std::shared_ptr<VL::KeyReleaseEvent>& e) override;
	void onMouseMovedEvent(const std::shared_ptr<VL::MouseMovedEvent>& e) override;
private:
	void onKeyEvent(VL::KeyboardEvent::KEY_CODES key, KEY_EVENT_TYPE type);

private:
	Camera m_camera;
	VL::Renderer* m_renderer;
	std::unique_ptr<ModelRenderer> m_modelRenderer;
	std::shared_ptr<VL::IShaderProgram> m_program;
	float m_rotation = 0.f;
	float m_deltaTime = 0.f;
};