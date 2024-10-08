#include "./docking_appwindow.hpp"

namespace Cherry
{

    DockingAppWindow::DockingAppWindow(const std::string &name)
    {
        m_AppWindow = std::make_shared<Cherry::AppWindow>(name, name);
        m_AppWindow->SetIcon("/usr/local/include/Vortex/imgs/vortex.png");
        m_AppWindow->SetDockingMode(true);
        m_AppWindow->SetRenderCallback([this]()
                                       {
        ImGui::Text("AA.BB.CC.DD.EE.FF 1");
        ImGui::Button("qsd"); });

        std::shared_ptr<Cherry::AppWindow> win = m_AppWindow;

        m_AppWindow->SetLeftMenubarCallback([]()
                                            { ImGui::Text("ll"); });

        m_AppWindow->SetRightMenubarCallback([win]() {});

        std::shared_ptr<EmptyAppWindow> windodo = std::make_shared<Cherry::EmptyAppWindow>("sec1", win);
        Application::Get().PutWindow(windodo->m_AppWindow);
        std::shared_ptr<EmptyAppWindow> windodof = std::make_shared<Cherry::EmptyAppWindow>("sec2", win);
        Application::Get().PutWindow(windodof->m_AppWindow);
        std::shared_ptr<EmptyAppWindow> windodofg = std::make_shared<Cherry::EmptyAppWindow>("sec3");
        Application::Get().PutWindow(windodofg->m_AppWindow);
        std::shared_ptr<EmptyAppWindow> windodofh = std::make_shared<Cherry::EmptyAppWindow>("sec4");
        Application::Get().PutWindow(windodofh->m_AppWindow);
    }
}
