#include "ImGuiManager.h"

#include <iostream>


ImGuiManager::ImGuiManager(GLFWwindow* window) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); // or ImGui::StyleColorsLight();
    // Setup Platform/Renderer bindings

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiManager::NewFrame() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::DrawGUI()
{
    // Start building your GUI here
    ImGui::Begin("Control Panel");

    // Display some text
    ImGui::Text("Import Obj");

    // Button to import obj
    if (ImGui::Button("Import")) {
		std::cout << "Importing obj" << std::endl;
	}


    // More ImGui widgets go here

    ImGui::End();

}
void ImGuiManager::DrawButtons(unsigned int& index, int size, ImVec4& color, float& brightness) {
    ImGui::Begin("Control Panel");

    // Swap models section
    ImGui::Text("Swap models");
    if (ImGui::Button("<")) {
        if (index > 1) {
            index--;
        }
    }
    ImGui::SameLine();
    if (ImGui::Button(">")) {
        if (index < size) {
            index++;
        }
    }
    ImGui::Text("Model %d", index);

    // Color Picker
    ImGui::ColorEdit3("Color Picker", (float*)&color); // Pass a pointer to your color variable

    // Brightness Slider
    ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f); // Adjust brightness between 0 (dark) and 1 (bright)

    ImGui::End();
}

ImGuiManager::~ImGuiManager() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
