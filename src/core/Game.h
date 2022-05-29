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

		inline glm::i32vec2 GetCursorPosition() { return m_CursorPosition; }
		inline const od::Window &GetWindow() const { return *m_Window; }
		inline const glm::mat4 &GetProjection() const { return m_Projection; }
		inline const glm::mat4 &GetUIProjection() const { return m_UIProjection; }
		inline void SetCameraPosition(const glm::f32vec2 &pos) { m_CameraPosition = pos; }
		inline void MoveCamera(const glm::f32vec2 &offset) { m_CameraPosition += offset; }
		inline glm::f32vec2 GetUIViewport() const { return {m_Window->GetStartWidth(), m_Window->GetStartHeight() * m_AspectRatio}; }

	protected:
		Game(const od::WindowParameters &params);
		virtual void ProcessEvent(SDL_Event &event) {}
		virtual void Awake() {}
		virtual void Update(uint32_t deltaTime) {}
		virtual void DrawUI() {}
		virtual void Draw() {}
		virtual void OnShutdown() {}

	private:
		void UpdateProjections();
		void UpdateViewport();
		void SwapScenes();
		void CalculateDeltaTime();
		void PollEvents();

	protected:
		glm::f32vec2 m_CameraPosition{0,0};
		bool m_IsRunning = true;
		uint32_t m_TimeSinceStart = 0, m_DeltaTime = 0;
		TimePoint m_StartTimePoint, m_FrameStartTimePoint, m_FrameEndTimePoint;
		std::unique_ptr<od::Window> m_Window;
		glm::i32vec2 m_CursorPosition;

	private:
		float m_AspectRatio;
		glm::mat4 m_Projection;
		glm::mat4 m_UIProjection;
		SDL_GLContext m_GLCtx;
		std::unique_ptr<od::Scene> m_NextScene, m_Scene;
		glm::i32vec2 m_LastWindowSize;
	};
}
