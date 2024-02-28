#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h> // Include GLFW or equivalent for your context

class ImGuiManager {
public:
    ImGuiManager(GLFWwindow* window);
    void NewFrame();
    void Render();
    void DrawGUI();

    void DrawButtons(unsigned int& index, int size,ImVec4& color, float& brightness);
    ~ImGuiManager();
};

#endif // IMGUI_MANAGER_HPP