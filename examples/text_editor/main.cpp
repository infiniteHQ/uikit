#define CHERRY_V1
#include "../../cherry.hpp"

#include <thread>
#include <memory>

class Layer : public Cherry::Layer
{
public:
  Layer() {};
};

Cherry::Application *Cherry::CreateApplication(int argc, char **argv)
{
  Cherry::ApplicationSpecification spec;
  std::shared_ptr<Layer> layer = std::make_shared<Layer>();

  std::string name = "Text Editor";
  spec.Name = name;
  spec.MinHeight = 500;
  spec.MinWidth = 500;
  spec.CustomTitlebar = false;
  spec.DisableWindowManagerTitleBar = false;
  spec.RenderMode = WindowRenderingMethod::SimpleWindow;
  spec.UniqueAppWindowName = "Test";
  spec.WindowSaves = false;
  spec.IconPath = BINPATH("ressources/imgs/icon.png");

  Cherry::Application *app = new Cherry::Application(spec);
  app->SetFavIconPath(Application::CookPath("ressources/imgs/favicon.png"));
  app->AddFont("Consola", Application::CookPath("ressources/fonts/consola.ttf"), 17.0f);

  app->AddLocale("fr", Application::CookPath("ressources/locales/fr.json"));
  app->AddLocale("en", Application::CookPath("ressources/locales/en.json"));
  app->SetLocale("fr");

  app->PushLayer(layer);
  app->SetMenubarCallback([app, layer]()
                          {
                            ImVec4 grayColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);        
                            ImVec4 graySeparatorColor = ImVec4(0.4f, 0.4f, 0.4f, 0.5f);
                            ImVec4 darkBackgroundColor = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
                            ImVec4 lightBorderColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);       

                            ImGui::PushStyleColor(ImGuiCol_PopupBg, darkBackgroundColor);

                            ImGui::PushStyleColor(ImGuiCol_Border, lightBorderColor);

                            ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 3.0f);

                            static bool t;

                            if (ImGui::BeginMenu("Edit"))
                            {
                              ImGui::GetFont()->Scale *= 0.8;
                              ImGui::PushFont(ImGui::GetFont());

                              ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);

                              ImGui::PushStyleColor(ImGuiCol_Text, grayColor);
                              ImGui::Text("Main stuff");
                              ImGui::PopStyleColor();

                              ImGui::PushStyleColor(ImGuiCol_Separator, graySeparatorColor);
                              ImGui::Separator();
                              ImGui::PopStyleColor();

                              ImGui::GetFont()->Scale = 0.84;
                              ImGui::PopFont();
                              ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);

                              if (ImGui::MenuItem("Project Settings", "Main configurations of this project", &t))
                              {
                              }

                              if(ImGui::Button("Set en"))
                              {
  app->SetLocale("en");
                              }

                              if(ImGui::Button("Set fr"))
                              {
  app->SetLocale("fr");
                              }

                              if(ImGui::Button("Set es"))
                              {
  app->SetLocale("es");
                              }
                              ImGui::GetFont()->Scale *= 0.8;
                              ImGui::PushFont(ImGui::GetFont());

                              ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);

                              ImGui::PushStyleColor(ImGuiCol_Text, grayColor);
                              ImGui::Text("Main stuff");
                              ImGui::PopStyleColor();

                              ImGui::PushStyleColor(ImGuiCol_Separator, graySeparatorColor);
                              ImGui::Separator();
                              ImGui::PopStyleColor();

                              ImGui::GetFont()->Scale = 0.84;
                              ImGui::PopFont();
                              ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);

                              if (ImGui::MenuItem("Logs Utility", "Overview of all logs", &t))
                              {
                              }

                              ImGui::GetFont()->Scale *= 0.8;
                              ImGui::PushFont(ImGui::GetFont());

                              ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);

                              ImGui::PushStyleColor(ImGuiCol_Text, grayColor);
                              ImGui::Text("Main stuff");
                              ImGui::PopStyleColor();

                              ImGui::PushStyleColor(ImGuiCol_Separator, graySeparatorColor);
                              ImGui::Separator();
                              ImGui::PopStyleColor();

                              ImGui::GetFont()->Scale = 0.84;
                              ImGui::PopFont();
                              ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);

                              if (ImGui::MenuItem("Manage plugins", "Add, remove, edit plugins of this project"))
                              {
                              }

                              if (ImGui::MenuItem("Manage modules", "Manage modules loaded/registered", &t))
                              {
                              }

                              if (ImGui::MenuItem("Templates modules", "Create, add template in your project", &t))
                              {
                              }

                              ImGui::EndMenu();
                            }

                            ImGui::PopStyleVar();  
                            ImGui::PopStyleColor(2); });

  std::shared_ptr<TextEditorSimple> TextEditor = std::make_shared<TextEditorSimple>("Test");
  TextEditor->RefreshRender(TextEditor);
  Application::Get().PutWindow(TextEditor->GetAppWindow()); // Publish this window into the workspace

  app->SetMainRenderCallback([]()
                             {
                               /*static ImFont *font = Application::GetFontList()["Consola"];

                               ImFont *old = ImGui::GetFont();
                               if (font)
                               {
                                 ImGui::PushFont(font);
                               }

                               cp_TextEditor->Render("Title");

                               if (font)
                               {
                                 ImGui::PopFont();
                               }*/ });

  return app;
}

int main(int argc, char *argv[])
{
  std::thread mainthread;
  std::thread Thread([&]()
                     { Cherry::Main(argc, argv); });
  mainthread.swap(Thread);

  while (g_ApplicationRunning)
  {
    /* Your program loop... */
  }

  mainthread.join();

  return 0;
}