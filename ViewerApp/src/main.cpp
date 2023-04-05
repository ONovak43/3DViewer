#include "Core/Application.hpp"
#include "Client.hpp"
#include "Memory/StackAllocator.hpp"

int main()
{
	auto client = std::make_shared<Viewer>();
	auto& app = VL::Application::getInstance();
	app.setClient(client);
	app.run();

}