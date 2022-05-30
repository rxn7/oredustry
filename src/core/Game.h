#pragma once

#include "Libs.h"
#include "Window.h"
#include "Scene.h"

namespace od {
	typedef std::chrono::high_resolution_clock::time_point TimePoint;

	class Game {
	public:
		static Game *GetInstance();

		void Start();
		void Shutdown(bool error=false, std::string_view reason="");
		void ShutdownWithoutReason();
		void SetScene(std::unique_ptr<od::Scene> scene);
		void HandleWindowResize(int32_t width, int32_t height);
		void TakeScreenshot(const std::string_view &path = "screenshot.png") const;

		inline glm::i32vec2 GetCursorPosition() { return m_CursorPosition; }
		inline od::Window &GetWindow() const { return *m_Window; }
		inline FT_Library &GetFT() { return m_Ft; }
		inline const glm::mat4 &GetProjection() const { return m_Projection; }
		inline const glm::mat4 &GetUIProjection() const { return m_UIProjection; }
		inline void SetCursorPosition(const glm::f32vec2 &pos) { m_CursorPosition = pos; }
		inline void SetCameraPosition(const glm::f32vec2 &pos) { m_CameraPosition = pos; }
		inline void MoveCamera(const glm::f32vec2 &offset) { m_CameraPosition += offset; }

	protected:
		Game(const od::WindowParameters &params);
		virtual void Awake() {}
		virtual void Update(uint32_t deltaTime);
		virtual void DrawNuklear() {}
		virtual void DrawUI() {}
		virtual void Draw() {}
		virtual void OnShutdown() {}

	private:
		void UpdateProjections();
		void UpdateViewport();
		void SwapScenes();
		void CalculateDeltaTime();

	protected:
		uint32_t m_TimeSinceStart = 0, m_DeltaTime = 0;
		TimePoint m_StartTimePoint, m_FrameStartTimePoint, m_FrameEndTimePoint;
		std::unique_ptr<od::Window> m_Window;
		FT_Library m_Ft;
		glm::f32vec2 m_CameraPosition{0,0};
		glm::i32vec2 m_CursorPosition{0,0};

	private:
		glm::mat4 m_Projection;
		glm::mat4 m_UIProjection;
		std::unique_ptr<od::Scene> m_NextScene, m_Scene;
	};
}
