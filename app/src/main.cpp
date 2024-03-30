#define MAGMA_ENTRYPOINT
#include "Magma/Magma.h"
#include "Layers/Layer.h"
#include "Layers/AppLayer.h"

class EmbedApplication:public mg::Application
{
public:
	EmbedApplication()
	{
		m_Layers.emplace_back(new AppLayer());
		// add your layers here
	}

	void Init() override
	{
		for (auto& layer : m_Layers)
			layer->OnAttach();
	}

	void Destroy() override
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}

		m_Layers.clear();
	}

	~EmbedApplication()
	{
	}
	void Render() override
	{
		for (auto& layer : m_Layers)
			layer->OnUIRender();
	}
private:
	std::vector<mg::Layer*> m_Layers;
};


mg::Application* CreateApplication(int argc, char** argv)
{
	EmbedApplication* app = new EmbedApplication(); 
	app->SetSize(800,600);
	app->SetTitle("Embed");
	return app;
}