#ifndef APP_LAYER_H
#define APP_LAYER_H
#include "Layer.h"
#include "Magma/Magma.h"
#include "Generator/EmbedManager.h"

class AppLayer : public mg::Layer
{
public:
	void OnAttach();
	void OnDetach();
	void OnUIRender();
	static void SetPath(const std::filesystem::path& path) { s_path = path; s_shouldRegenerate = true; }
private:
	void DragAndDropRender();
	void ExportConfigRender();
private:
	EmbedManager m_embedManager;
	std::string m_status;

	static std::filesystem::path s_path;
	static bool s_shouldRegenerate;
};

#endif // APP_LAYER_H