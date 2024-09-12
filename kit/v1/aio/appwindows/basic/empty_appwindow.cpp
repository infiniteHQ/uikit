#include "./empty_appwindow.hpp"

namespace UIKit
{

    EmptyAppWindow::EmptyAppWindow(const std::string &name, const std::shared_ptr<AppWindow> &parent)
    {
        m_AppWindow = std::make_shared<UIKit::AppWindow>(name, name);
        m_AppWindow->SetIcon("/usr/local/include/Vortex/imgs/vortex.png");
        m_AppWindow->SetParent(parent);
        m_AppWindow->SetRenderCallback([this]()
                                       {
        ImGui::Text("AA.BB.CC.DD.EE.FF 1");
        ImGui::Button("qsd"); });

        std::shared_ptr<UIKit::AppWindow> win = m_AppWindow;

        m_AppWindow->SetLeftMenubarCallback([]()
                                            { ImGui::Text("ll"); });

        m_AppWindow->SetRightMenubarCallback([win]()
                                             {
                                                     if (UIKit::ImageButtonSimple("Test", "/usr/local/include/Vortex/imgs/vortex.png"))
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     }
                                                     if (UIKit::DangerButtonLowProfile())
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     }
                                                     if (UIKit::CustomButtonSimple("Test"))
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     } });
    }
    EmptyAppWindow::EmptyAppWindow()
    {
        m_AppWindow = std::make_shared<UIKit::AppWindow>("Sec", "Sec");
        m_AppWindow->SetIcon("/usr/local/include/Vortex/imgs/vortex.png");
        m_AppWindow->SetRenderCallback([this]()
                                       {
        ImGui::Text("AA.BB.CC.DD.EE.FF 1");
        ImGui::Button("qsd"); });

        std::shared_ptr<UIKit::AppWindow> win = m_AppWindow;

        m_AppWindow->SetLeftMenubarCallback([]()
                                            { ImGui::Text("ll"); });

        m_AppWindow->SetRightMenubarCallback([win]()
                                             {
                                                     if (UIKit::ImageButtonSimple("Test", "/usr/local/include/Vortex/imgs/vortex.png"))
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     }
                                                     if (UIKit::DangerButtonLowProfile())
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     }
                                                     if (UIKit::CustomButtonSimple("Test"))
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     } });
    }
    
    EmptyAppWindow::EmptyAppWindow(const std::string &name)
    {
        m_AppWindow = std::make_shared<UIKit::AppWindow>(name, name);
        m_AppWindow->SetIcon("/usr/local/include/Vortex/imgs/vortex.png");
        m_AppWindow->SetRenderCallback([this]()
                                       {
        ImGui::Text("AA.BB.CC.DD.EE.FF 1");
        ImGui::Button("qsd"); });

        std::shared_ptr<UIKit::AppWindow> win = m_AppWindow;

        m_AppWindow->SetLeftMenubarCallback([]()
                                            { ImGui::Text("ll"); });

        m_AppWindow->SetRightMenubarCallback([win]()
                                             {
                                                     if (UIKit::ImageButtonSimple("Test", "/usr/local/include/Vortex/imgs/vortex.png"))
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     }
                                                     if (UIKit::DangerButtonLowProfile())
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     }
                                                     if (UIKit::CustomButtonSimple("Test"))
                                                     {
                                                         std::cout << "ok" << std::endl;
                                                     } });
    }

}