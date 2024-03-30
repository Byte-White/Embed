#include "AppLayer.h"
#include "imgui.h"

void AppLayer::OnAttach()
{
    m_embedManager.Generate("D:/.dev/Embed/app/src"); // example folder
    m_embedManager.Export("D:/.dev/Embed/export/");
}

void AppLayer::OnDetach()
{
    
}

void AppLayer::OnUIRender()
{
	DragAndDropRender();
}


void AppLayer::DragAndDropRender()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("View", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    
    ImGui::SetWindowFontScale(1.5f);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    // Calculate the position for centering the text
    ImVec2 textPosition = ImVec2(windowSize.x * 0.5f, windowSize.y * 0.5f);

    // Calculate the size of the text
    ImVec2 textSize = ImGui::CalcTextSize("Drag And Drop A Folder");

    // Offset text position to center it
    textPosition.x -= textSize.x * 0.5f;
    textPosition.y -= textSize.y * 0.5f;


    // Render the text at the calculated position
    ImGui::SetCursorScreenPos(textPosition);
    ImGui::Text("Drag And Drop A Folder");

    ImGui::SetWindowFontScale(1.0f);

    ImGui::End();
}