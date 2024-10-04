#define UIKIT_V1
#include "../../uikit.hpp"

#include <thread>
#include <memory>

class Layer : public UIKit::Layer
{
public:
  Layer() {};
};

UIKit::Application *UIKit::CreateApplication(int argc, char **argv)
{
  UIKit::ApplicationSpecification spec;
  std::shared_ptr<Layer> layer = std::make_shared<Layer>();

  std::string name = "UIKit example";
  spec.Name = name;
  spec.MinHeight = 500;
  spec.MinWidth = 500;
  spec.CustomTitlebar = true;
  spec.DisableWindowManagerTitleBar = true;
  spec.RenderMode = WindowRenderingMethod::DockingWindows;

  spec.UniqueAppWindowName = "?loc:loc.window_names.demo";
  spec.DisableTitle = true;
  spec.WindowSaves = true;
  spec.IconPath = Application::CookPath("ressources/imgs/icon.png");

  UIKit::Application *app = new UIKit::Application(spec);
  app->SetWindowSaveDataFile("savedatda.json", true);
  app->SetFavIconPath(Application::CookPath("ressources/imgs/favicon.png"));
  app->AddFont("Consola", Application::CookPath("ressources/fonts/consola.ttf"), 17.0f);

  app->AddLocale("fr", Application::CookPath("ressources/locales/fr.json"));
  app->AddLocale("en", Application::CookPath("ressources/locales/en.json"));
  app->AddLocale("es", Application::CookPath("ressources/locales/es.json")); // With not suffisent locales to show the "default" behavior
  app->SetDefaultLocale("en"); // The "default" behavior
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

                            if (ImGui::BeginMenu("Options"))
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
                            ImGui::PopStyleColor(2); 
                            });


  
  std::shared_ptr<ContentOutlinerSimple> ContentOutliner = std::make_shared<UIKit::ContentOutlinerSimple>("?loc:loc.window_names.outliner"); // Create Window
  ContentOutliner->RefreshRender(ContentOutliner); // Refresh the render channel
  Application::Get().PutWindow(ContentOutliner->GetAppWindow()); // Publish this window into the workspace

  std::shared_ptr<TextEditorSimple> TextEditor = std::make_shared<UIKit::TextEditorSimple>("?loc:loc.window_names.text_editor");
  TextEditor->RefreshRender(TextEditor);
  Application::Get().PutWindow(TextEditor->GetAppWindow()); // Publish this window into the workspace

  std::shared_ptr<PropsEditorSimple> PropsEditor = std::make_shared<UIKit::PropsEditorSimple>("?loc:loc.window_names.props_editor");
  PropsEditor->RefreshRender(PropsEditor);
  Application::Get().PutWindow(PropsEditor->GetAppWindow()); // Publish this window into the workspace
  
  std::shared_ptr<ContentBrowserAppWindow> ContentBrowser = std::make_shared<UIKit::ContentBrowserAppWindow>("?loc:loc.window_names.content_browser", "/home/diego");
  ContentBrowser->RefreshRender(ContentBrowser);
  Application::Get().PutWindow(ContentBrowser->GetAppWindow()); // Publish this window into the workspace

  std::shared_ptr<NodeEditorSimple> NodalEditor = std::make_shared<UIKit::NodeEditorSimple>("?loc:loc.window_names.node_editor");
  NodalEditor->RefreshRender(NodalEditor);
  Application::Get().PutWindow(NodalEditor->GetAppWindow()); // Publish this window into the workspace
  
  std::shared_ptr<DockingAppWindow> WindowWithDockspace = std::make_shared<UIKit::DockingAppWindow>("fqdow_names.texqsd");
  Application::Get().PutWindow(WindowWithDockspace->GetAppWindow());
   
  std::shared_ptr<MultiChildTabs> TabsWindow = std::make_shared<UIKit::MultiChildTabs>("Vertical Tabs");
  TabsWindow->AddChild("One", [](){ImGui::Text("One");});
  TabsWindow->AddChild("Two", [](){ImGui::Text("Two");});
  TabsWindow->AddChild("Three", [](){ImGui::Text("Three");});
  TabsWindow->RefreshRender(TabsWindow);
  Application::Get().PutWindow(TabsWindow->GetAppWindow()); // Publish this window into the workspace
   
  // Multi childs
  std::shared_ptr<MultiChildAreas> VerticalAreas = std::make_shared<UIKit::MultiChildAreas>("indow_names.content_browser");
  VerticalAreas->m_IsHorizontal = false;
  VerticalAreas->AddChild(Child("One", [](){ImGui::Text("One");}));
  VerticalAreas->AddChild(Child("Two", [](){ImGui::Text("Two");}, 20.0f));
  VerticalAreas->AddChild(Child("Three", [](){ImGui::Text("Three");}));
  VerticalAreas->AddChild(Child("Four", [](){ImGui::Text("Four");}));
  VerticalAreas->RefreshRender(VerticalAreas);
  Application::Get().PutWindow(VerticalAreas->GetAppWindow()); // Publish this window into the workspace

  std::shared_ptr<MultiChildAreas> HorizontalAreas = std::make_shared<UIKit::MultiChildAreas>("indow_names.content_browser2");
  HorizontalAreas->m_IsHorizontal = true;
  HorizontalAreas->AddChild(Child("One2", [](){ImGui::Text("One");}));
  HorizontalAreas->AddChild(Child("Two2", [](){ImGui::Text("Two");}, 20.0f));
  HorizontalAreas->AddChild(Child("Three2", [](){ImGui::Text("Three");}));
  HorizontalAreas->AddChild(Child("Four2", [](){ImGui::Text("Four");}));
  HorizontalAreas->RefreshRender(HorizontalAreas);
  Application::Get().PutWindow(HorizontalAreas->GetAppWindow()); // Publish this window into the workspace

  std::shared_ptr<MultiChildList> ListWindow = std::make_shared<UIKit::MultiChildList>("indow_names.list");
  ListWindow->AddChild("One", [](){ImGui::Text("One");});
  ListWindow->AddChild("Two", [](){ImGui::Text("Two");});
  ListWindow->AddChild("Three", [](){ImGui::Text("Three");});
  ListWindow->AddChild("Four", [](){ImGui::Text("Four");});
  ListWindow->RefreshRender(ListWindow);
  Application::Get().PutWindow(ListWindow->GetAppWindow()); // Publish this window into the workspace
  

  std::shared_ptr<MultiChildTabs> appTabs = std::make_shared<UIKit::MultiChildTabs>("indow_names.tabs");
  appTabs->AddChild("One", [](){ImGui::Text("One");});
  appTabs->AddChild("Two", [](){ImGui::Text("Two");});
  appTabs->AddChild("Three", [](){ImGui::Text("Three");});
  appTabs->AddChild("Four", [](){ImGui::Text("Four");});
  appTabs->RefreshRender(appTabs);
  
  

  return app;
}

int main(int argc, char *argv[])
{
  std::thread mainthread;
  std::thread Thread([&]()
                     { UIKit::Main(argc, argv); });
  mainthread.swap(Thread);

  while (g_ApplicationRunning)
  {
    /* Your program loop... */
  }

  mainthread.join();

  return 0;
}