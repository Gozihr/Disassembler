// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "runtime/binaryDisassemble.h"
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <ImGuiFileDialog/ImGuiFileDialog.h>

#include <iostream>
#include <string>
#include <sstream>

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;
std::string title = "Disasm-Gui";
std::string glslVersion = "#version 330";
GLFWwindow *window = nullptr;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool gozihr_active = true;
std::string filePath;
std::string binary;
std::string disasm;

void Disassemble(std::string binaryPath, std::string pluginPath = "") {
  if (binaryPath.empty()) {
    // TODO ImGui::OpenPopup
    return;
  }
  std::stringstream stream;
  BinaryDisassemble::action(binaryPath, pluginPath, stream);
  disasm = stream.str();
}

void draw() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  {
    ImGui::Begin("Gozihr", &gozihr_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open..", "Ctrl+O")) {
          std::string typeFilters = ".exe,.dll,.lib,.out,.a,.so,.dylib,.*";
          std::string startPath = ".";
          ImGuiFileDialog::Instance()->OpenDialog(
              "ChooseFileDlgKey", "Choose File", typeFilters.c_str(),
              startPath);
        }
        if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
        }
        if (ImGui::MenuItem("Close", "Ctrl+W")) {
          gozihr_active = false;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
      // action if OK
      if (ImGuiFileDialog::Instance()->IsOk()) {
        filePath = ImGuiFileDialog::Instance()->GetFilePathName();
      }

      // close
      ImGuiFileDialog::Instance()->Close();
    }
    ImGui::InputText("binary path: ", const_cast<char *>(filePath.c_str()),
                     filePath.capacity() + 1);
    if (ImGui::Button("Disassemble")) {
      Disassemble(filePath);
    }
    // Display contents in a scrolling region
    ImGui::BeginChild("Scrolling");
    ImGui::Text("%s", disasm.c_str());
    ImGui::EndChild();
    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imguiInit() {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glslVersion.c_str());
}

void update_loop(GLFWwindow *window) {
  glViewport(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char *argv[]) {
  if (glfwInit() != GL_TRUE) {
    std::cerr << "Failed to initialize GLFW!" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), nullptr,
                            nullptr);
  if (!window) {
    glfwTerminate();
    std::cerr << "Failed to initialize GLFW Window!" << std::endl;
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context" << std::endl;
    exit(EXIT_FAILURE);
  }

  imguiInit();

  glfwSetKeyCallback(window, key_callback);

  update_loop(window);

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}