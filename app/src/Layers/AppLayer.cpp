#include "AppLayer.h"
#include "imgui.h"

#include <Windows.h>
#include <commdlg.h>
#include <Shlobj.h>

namespace utils
{
    wchar_t* OpenFolderDialog()
    {
        BROWSEINFOW bi = {};
        bi.lpszTitle = L"Select a folder";
        bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

        LPITEMIDLIST pidl = SHBrowseForFolderW(&bi);
        if (pidl != NULL)
        {
            // Get the folder path from the ID list
            wchar_t folderPath[MAX_PATH];
            if (SHGetPathFromIDListW(pidl, folderPath))
            {
                // Allocate memory for the result and copy the folder path
                size_t pathLength = wcslen(folderPath);
                wchar_t* result = (wchar_t*)malloc((pathLength + 1) * sizeof(wchar_t));
                if (result != NULL)
                {
                    wcscpy(result, folderPath);
                    return result;
                }
            }
        }
        return NULL;
    }
}


std::filesystem::path AppLayer::s_path = "";
bool AppLayer::s_shouldRegenerate = false;


static void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    if (std::filesystem::is_directory(paths[0]))
    {
        AppLayer::SetPath(paths[0]);
        // MAGMA_INFO("Dropped folder {0}",paths[0]);
    }
}

void AppLayer::OnAttach()
{
    glfwSetDropCallback(*mg::app->GetWindow(), drop_callback);
}

void AppLayer::OnDetach()
{
    
}

void AppLayer::OnUIRender()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("View", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

    if (s_path == "") DragAndDropRender();
    else ExportConfigRender();

    ImGui::End();
}


void AppLayer::DragAndDropRender()
{    
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

}


void AppLayer::ExportConfigRender()
{
    if (s_shouldRegenerate) 
    { 
        m_embedManager.Generate(s_path); 
        s_shouldRegenerate = false;
    }

    if (ImGui::ArrowButton("Back", ImGuiDir_Left)) SetPath("");

    if (ImGui::Button("Regenerate"))
    {
        m_embedManager.Generate(s_path);
    }

    for (auto& file : m_embedManager.GetEmbededFiles())
    {
        ImGui::Checkbox(("##" + file.variableName).c_str(), &file.include);
        ImGui::SameLine();
        ImGui::Text("%s", file.filepath.string().c_str());
    }

    if (ImGui::Button("Export"))
    {
        std::filesystem::path outpath = utils::OpenFolderDialog();
        if (outpath != "")
        {
            m_embedManager.Export(outpath);
            m_status = "Exported to '" + outpath.string() + "' successfully.";
        }
        else MAGMA_ERROR("Export was canceled.");
    }
    ImGui::TextColored(ImVec4(0.0f,0.8f,0.0f,1.0f), "%s", m_status.c_str());
}