// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "imguiGLWindow.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "runtime/binaryDisassemble.h"
#include <ImGuiFileDialog/ImGuiFileDialog.h>

#include <iostream>
#include <sstream>
#include <string>

void GozihrWindow::Draw() {
  ImGui::Begin("Gozihr", &gozihr_active, ImGuiWindowFlags_MenuBar);
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open..", "Ctrl+O")) {
        std::string typeFilters = ".exe,.dll,.lib,.out,.a,.so,.dylib,.*";
        std::string startPath = ".";
        ImGuiFileDialog::Instance()->OpenDialog(
            "ChooseFileDlgKey", "Choose File", typeFilters.c_str(), startPath);
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
  if (pDisasm != nullptr) {
    auto instructions = pDisasm->getInstructions();
    for (size_t i = 0; i < instructions.size(); i++) {
      std::stringstream stream;
      stream << instructions[i];
      ImGui::Text("%s", stream.str().c_str());
    }
  }
  ImGui::EndChild();
  ImGui::End();
}

void GozihrWindow::Disassemble(std::string binaryPath, std::string pluginPath) {
  if (binaryPath.empty()) {
    // TODO ImGui::OpenPopup
    return;
  }

  pDisasm = BinaryDisassemble::disassemble(binaryPath, pluginPath);
}

ImguiGLWindow::ImguiGLWindow(std::string title, int width, int height)
    : GLWindow(title, width, height) {
  mGozihrWindow = std::make_unique<GozihrWindow>();
}

void ImguiGLWindow::init() {
  GLWindow::init();
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(this->getGLFWwindow(), true);
  ImGui_ImplOpenGL3_Init(GLWindow::glslVersion);
  drawFunctors.push_back([this]() { this->mGozihrWindow->Draw(); });
}

void ImguiGLWindow::draw() {
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  for (const std::function<void()> &df : drawFunctors) {
    df();
  }

  // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(this->getGLFWwindow(), &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}