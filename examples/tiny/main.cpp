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

  std::string name = "Tiny window";
  spec.Name = name;
  spec.MinHeight = 500;
  spec.MinWidth = 500;
  spec.Height = 400;
  spec.Width = 700;
  spec.CustomTitlebar = false;
  spec.DisableWindowManagerTitleBar = true;
  spec.RenderMode = WindowRenderingMethod::SimpleWindow;

  spec.UniqueAppWindowName = "main_window";
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
  app->SetDefaultLocale("en");                                               // The "default" behavior
  app->SetLocale("fr");

  app->PushLayer(layer);
  std::shared_ptr<MultiChildAreas> Areas = std::make_shared<UIKit::MultiChildAreas>("main_window");
  Areas->m_IsHorizontal = true;
  Areas->AddChild(Child("One", []()
                        {
                          ImVec2 imageSize = Application::GetCurrentRenderedWindow()->get_texture_size(
                              Application::Get().CookPath("ressources/imgs/back.jpg"));

                          ImVec2 availableSize = ImGui::GetContentRegionAvail();

                          float scaleX = availableSize.x / imageSize.x;
                          float scaleY = availableSize.y / imageSize.y;

                          float scale = (scaleX > scaleY) ? scaleX : scaleY;

                          ImVec2 displaySize = ImVec2(imageSize.x * scale, imageSize.y * scale);

                          ImVec2 offset = ImVec2(
                              (availableSize.x - displaySize.x) * 0.5f,
                              (availableSize.y - displaySize.y) * 0.5f);

                          if (offset.x < 0)
                            offset.x = 0;
                          if (offset.y < 0)
                            offset.y = 0;

                          ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset.x);
                          ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offset.y);

                          ImGui::Image(
                              Application::GetCurrentRenderedWindow()->get_texture(Application::Get().CookPath("ressources/imgs/back.jpg")),
                              ImVec2(availableSize.x, availableSize.y),
                              ImVec2(-offset.x / displaySize.x, -offset.y / displaySize.y),
                              ImVec2((availableSize.x - offset.x) / displaySize.x, (availableSize.y - offset.y) / displaySize.y));
                        }, 0.0f, true));
  Areas->AddChild(Child("Two", []()
                        { 
                          ImGui::Separator();
                          UIKit::TitleTwo("Welcome to UIKit !!!");
                          UIKit::TitleSixColored("by Infinite"); 
                          ImGui::TextWrapped("UIKit is a powerfull low-level framework to help developpers to create simple or advanced application, with no advanced knowledges required. UIKit provide components, tools, a render engine & all backends you need to make the next revolutionnary app !"); 
                          }, 20.0f));

  Areas->RefreshRender(Areas);
  Application::Get().PutWindow(Areas->GetAppWindow());

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