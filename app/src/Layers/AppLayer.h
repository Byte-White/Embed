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
private:
	void DragAndDropRender();
private:
	EmbedManager m_embedManager;
};

#endif // APP_LAYER_H