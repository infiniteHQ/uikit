#pragma once

#include "../../../src/Layer.h"
#include "Image.h"

#include <string>
#include <vector>
#include <queue>
#include <mutex>
#include <memory>
#include <functional>
#include <filesystem>

#include "../../../lib/imgui/imgui.h"
#include "../../../lib/imgui/imgui_internal.h"
#include "../../../lib/imgui/backends/imgui_impl_vulkan.h"
#include "../../../lib/imgui/backends/imgui_impl_glfw.h"
#include "../../../lib/stb-image/stb_image.h"
#include "vulkan/vulkan.h"

void check_vk_result(VkResult err);

struct GLFWwindow;

namespace UIKit {

	struct ApplicationSpecification
	{
		std::string Name = "UIKit App";
		uint32_t Width = 1850;
		uint32_t Height = 1000;

		std::filesystem::path IconPath;

		bool WindowResizeable = true;

		// Uses custom UIKit titlebar instead
		// of Windows default
		bool CustomTitlebar = false;

		// Window will be created in the center
		// of primary monitor
		bool CenterWindow = false;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& applicationSpecification = ApplicationSpecification());
		~Application();

		static Application& Get();

		void Run();
		void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }

		template<typename T>
		void PushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
			m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
		}

		void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

		void Close();

		bool IsMaximized() const;
		std::shared_ptr<Image> GetApplicationIcon() const { return m_AppHeaderIcon; }

		float GetTime();
		GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
		bool IsTitleBarHovered() const { return m_TitleBarHovered; }

		static VkInstance GetInstance();
		static VkPhysicalDevice GetPhysicalDevice();
		static VkDevice GetDevice();

		static VkCommandBuffer GetCommandBuffer(bool begin);
		static void FlushCommandBuffer(VkCommandBuffer commandBuffer);

		static void SubmitResourceFree(std::function<void()>&& func);

		static ImFont* GetFont(const std::string& name);

		template<typename Func>
		void QueueEvent(Func&& func)
		{
			m_EventQueue.push(func);
		}

		ApplicationSpecification m_Specification;
		
	private:
		void Init();
		void Shutdown();

		// For custom titlebars
		void UI_DrawTitlebar(float& outTitlebarHeight);
		void UI_DrawMenubar();
	private:
		GLFWwindow* m_WindowHandle = nullptr;
		bool m_Running = false;
		
		float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		bool m_TitleBarHovered = false;

		std::vector<std::shared_ptr<Layer>> m_LayerStack;
		std::function<void()> m_MenubarCallback;

		std::mutex m_EventQueueMutex;
		std::queue<std::function<void()>> m_EventQueue;

		// Resources
		// TODO(Yan): move out of application class since this can't be tied
		//            to application lifetime
		std::shared_ptr<UIKit::Image> m_AppHeaderIcon;
		std::shared_ptr<UIKit::Image> m_IconClose;
		std::shared_ptr<UIKit::Image> m_IconMinimize;
		std::shared_ptr<UIKit::Image> m_IconMaximize;
		std::shared_ptr<UIKit::Image> m_IconRestore;
	};

	// Implemented by CLIENT
	Application* CreateApplication(int argc, char** argv);
}