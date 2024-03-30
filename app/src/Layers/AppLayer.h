#ifndef APP_LAYER_H
#define APP_LAYER_H
#include "Layer.h"
#include "Magma/Magma.h"

class AppLayer : public mg::Layer
{
public:
	void OnAttach();
	void OnDetach();
	void OnUIRender();
private:
	void DragAndDropRender();
private:
};

#endif // APP_LAYER_H