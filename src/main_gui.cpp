#include "list.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include <vector>

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "To-Do List GUI", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // To-Do List Logic
    List todoList;
    std::string exportFileName = "default.txt";
    bool exported = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main GUI window
        ImGui::Begin("To-Do List");

        // Add Task Section
        static char newTaskBuffer[256] = "";
        ImGui::InputText("New Task", newTaskBuffer, sizeof(newTaskBuffer));
        ImGui::SameLine();
        if (ImGui::Button("Add Task")) {
            if (strlen(newTaskBuffer) > 0) {
                todoList.AddTask(newTaskBuffer);
                newTaskBuffer[0] = '\0'; // Clear input buffer
            }
        }

        // Display Tasks
        ImGui::Separator();
        ImGui::Text("Tasks:");
        auto& tasks = todoList.GetTasks();
        for (size_t i = 0; i < tasks.size(); ++i) {
            ImGui::PushID(static_cast<int>(i));
            bool completed = tasks[i].completed;
            if (ImGui::Checkbox(tasks[i].title.c_str(), &completed)) {
                todoList.CompleteTask(i);
            }
            ImGui::SameLine();
            if (ImGui::Button("Delete")) {
                todoList.DeleteCompletedTasks();
                ImGui::PopID();
                break; // Break to avoid iterator invalidation
            }
            ImGui::PopID();
        }

        // Export List Section
        ImGui::Separator();
        static char exportBuffer[256] = "list.txt";
        ImGui::InputText("Export File", exportBuffer, sizeof(exportBuffer));
        ImGui::SameLine();
        if (ImGui::Button("Export")) {
            exportFileName = exportBuffer;
            todoList.SaveToFile(exportFileName);
            exported = true;
        }

        // Update Exported List
        if (ImGui::Button("Update Exported List")) {
            if (exported) {
                todoList.SaveToFile(exportFileName);
            } else {
                ImGui::Text("Error: Export the list first!");
            }
        }

        ImGui::End();

        // Render ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}