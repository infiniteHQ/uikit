#pragma once

#include "../../src/layer.hpp"
#include "../../src/core/color.hpp"
#include "image.hpp"
#include "app.hpp"
#include "base.hpp"
#include "app_window.hpp"

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <mutex>
#include <memory>
#include <functional>
#include <filesystem>
#include <SDL2/SDL_image.h>

#include "ui/ui.hpp"
#include "imgui/ImGuiTheme.h"
#include "vulkan/vulkan.h"

struct ImGuiDockPreviewData
{
    ImGuiDockNode FutureNode;
    bool IsDropAllowed;
    bool IsCenterAvailable;
    bool IsSidesAvailable;   // Hold your breath, grammar freaks..
    bool IsSplitDirExplicit; // Set when hovered the drop rect (vs. implicit SplitDir==None when hovered the window)
    ImGuiDockNode *SplitNode;
    ImGuiDir SplitDir;
    float SplitRatio;
    ImRect DropRectsDraw[ImGuiDir_COUNT + 1]; // May be slightly different from hit-testing drop rects used in DockNodeCalcDropRects()

    ImGuiDockPreviewData() : FutureNode(0)
    {
        IsDropAllowed = IsCenterAvailable = IsSidesAvailable = IsSplitDirExplicit = false;
        SplitNode = NULL;
        SplitDir = ImGuiDir_None;
        SplitRatio = 0.f;
        for (int n = 0; n < IM_ARRAYSIZE(DropRectsDraw); n++)
            DropRectsDraw[n] = ImRect(+FLT_MAX, +FLT_MAX, -FLT_MAX, -FLT_MAX);
    }
};

namespace UIKit
{
    class Application;

    class Window
    {
    public:
        Window(const std::string &name, int width, int height, ApplicationSpecification specs, bool cold_start = true);

        ~Window();

        void ProcessMouseEvents();

        VkCommandBuffer GetCommandBuffer(bool begin);
        SDL_Window *GetWindowHandle() const { return m_WindowHandler; }
        static void ShowDockingPreview(ImGuiID dockspaceID, Window *win, WindowDragDropState *dragState, const std::shared_ptr<AppWindow> appwin = nullptr);

        // void OnWindowResize(GLFWwindow *windowHandle, int width, int height);
        // void OnWindowMove(int xpos, int ypos);

        void BeginFrame()
        {
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        }

        void EndFrame()
        {
            ImGui::Render();
        }

        void OnUpdate();

        const std::string &GetName() const
        {
            return m_Name;
        }

        void CreateImage(std::shared_ptr<UIKit::Image> image, void *data);

        void UI_DrawTitlebar(float &outTitlebarHeight);
        void UI_DrawMenubar();

        void CleanupVulkanWindow();

        template <typename Func>
        void QueueEvent(Func &&func);

        void RequestResize(int width, int height);
        void RequestMove(int x, int y);

        bool hasImage(const std::string &image)
        {
            for (const auto &existingImage : this->m_ImageList)
            {
                if (existingImage.first == image)
                {
                    return true;
                }
            }
            return false;
        }

        void ApplyPendingResize()
        {
            if (m_ResizePending)
            {
                m_WinData.Width = m_PendingWidth;
                m_WinData.Height = m_PendingHeight;
                SDL_Window *win = this->GetWindowHandle();
                ImGui_ImplVulkanH_Window *wd = &this->m_WinData;

                m_ResizePending = false;
            }
        }

        void SetFavIcon(const std::string &path)
        {
            SDL_Surface *iconSurface = IMG_Load(path.c_str());
            if (!iconSurface)
            {
                return;
            }
            SDL_SetWindowIcon(m_WindowHandler, iconSurface);
            SDL_FreeSurface(iconSurface);
        }

        void Render();

        ImGuiContext *m_ImGuiContext;

        bool m_ResizePending = false;
        bool m_MovePending = false;
        int m_PendingWidth = 0;
        int m_PendingHeight = 0;
        int m_PendingX = 0;
        int m_PendingY = 0;
        int m_PreviousWidth = 0;
        int m_PreviousHeight = 0;
        int m_PreviousX = 0;
        int m_PreviousY = 0;
        int m_PosX = 0;
        int m_PosY = 0;

        bool m_IsClosing = false;

        bool isMoving = false;
        ImVec2 clickOffset = {0.0f, 0.0f};
        // If true, listen mouse pos and click and return a dropp emplacement response.
        bool m_IsDraggingAppWindow = false;

        bool m_Resizing = false;

        ApplicationSpecification m_Specifications;

        std::mutex m_EventQueueMutex;
        std::queue<std::function<void()>> m_EventQueue;
        bool g_SwapChainRebuild = false;
        VkSwapchainKHR g_Swapchain;
        std::vector<VkImage> g_SwapchainImages;
        std::vector<VkImageView> g_SwapchainImageViews;
        VkFormat g_SwapchainImageFormat;
        std::vector<std::vector<std::function<void()>>> s_ResourceFreeQueue;
        uint32_t s_CurrentFrameIndex = 0;
        std::vector<VkCommandBuffer> m_CommandBuffers;
        ImGuiWindow *m_ImGuiWindow;

        // List of all images (absolute path / image ref)
        std::vector<std::pair<std::string, std::shared_ptr<UIKit::Image>>> m_ImageList;

        std::shared_ptr<UIKit::Image> add(const std::string &path);
        std::shared_ptr<UIKit::Image> add(const uint8_t data[], const std::string &name);
        std::shared_ptr<UIKit::Image> get(const std::string &path);
        std::shared_ptr<UIKit::Image> get(const uint8_t data[], const std::string &name);
        ImTextureID get_texture(const std::string &path);
        void free();

        VkSurfaceKHR m_Surface;
        std::shared_ptr<WindowClickEvent> m_PendingClick = nullptr;
        std::shared_ptr<WindowMoveEvent> m_PendingMove = nullptr;
        WindowDragDropState drag_dropstate;
        int WinID;

        std::vector<std::vector<VkCommandBuffer>> s_AllocatedCommandBuffers;
        ImDrawData DrawData;
        int m_Width, m_Height;

        ImGui_ImplVulkanH_Window m_WinData;

        VkPipelineLayout pipelineLayout;
        ImGuiViewport *m_Viewport = nullptr;
        bool m_IsDragging = false;
        ImVec2 m_InitialMousePos;
        ImVec2 m_InitialWindowPos;

    private:
        std::function<void()> m_MenubarCallback;
        std::string m_Name;
        SDL_Window *m_WindowHandler;
    };
}