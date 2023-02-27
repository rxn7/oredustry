#pragma once

#include "Libs.h"
#include "Window.h"
#include "Scene.h"
#include "Font.h"
#include "ui/Text.h"

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

		glm::f32vec2 GetWorldCursorPosition();
		inline glm::i32vec2 GetCursorPosition() { return m_CursorPosition; }
		inline od::Window &GetWindow() const { return *m_Window; }
		inline const glm::mat4 &GetProjection() const { return m_Projection; }
		inline const glm::mat4 &GetUIProjection() const { return m_UIProjection; }
		inline od::Font *GetFont() const { return m_Font.get(); }
		inline uint32_t GetTimeSinceStartMs() const { return m_TimeSinceStart; }
		inline void SetCursorPosition(const glm::f32vec2 &pos) { m_CursorPosition = pos; }
		inline void SetCameraPosition(const glm::f32vec2 &pos) { m_CameraPosition = pos; }
		inline void MoveCamera(const glm::f32vec2 &offset) { m_CameraPosition += offset; }

	protected:
		Game(const od::WindowParameters &params);
		virtual void Ready() {}

		// NOTE: deltaTime argument doesn't refer to time between ticks, but time between frames!
		virtual void Tick(uint32_t deltaTime) {}

		virtual void Update(uint32_t deltaTime);
		virtual void Render2D() {}
		virtual void RenderUI() {}
		virtual void OnShutdown() {}
		virtual void HandleTick(uint32_t deltaTime);
		virtual void HandleUpdate(uint32_t deltaTime); 
		virtual void HandleRender2D();
		virtual void HandleRenderUI();

	private:
		void UpdateProjections();
		void UpdateViewport();
		void SwapScenes();
		uint32_t CalculateDeltaTime();

	protected:
		std::unique_ptr<od::Font> m_Font;
		TimePoint m_StartTimePoint, m_FrameStartTimePoint, m_FrameEndTimePoint;
		std::unique_ptr<od::Window> m_Window;
		glm::f32vec2 m_CameraPosition{0,0};
		glm::i32vec2 m_CursorPosition{0,0};

	private:
		uint32_t m_TimeSinceStart = 0;
		uint32_t m_TickTimer=0;
		glm::mat4 m_Projection;
		glm::mat4 m_UIProjection;
		std::unique_ptr<od::Scene> m_NextScene, m_Scene;
	};
}
