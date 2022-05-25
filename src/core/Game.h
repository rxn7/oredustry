#pragma once

#include "Libs.h"
#include "Window.h"
#include "Scene.h"

namespace od {
	class Game {
	public:
		static Game *GetInstance();

		void Start();
		void Shutdown(bool error=false, std::string_view reason="");
		void SetScene(std::unique_ptr<od::Scene> scene);

		inline glm::i32vec2 GetCursorPosition() { return m_CursorPosition; }
		inline od::Window &GetWindow() { return *m_Window; }
		inline TTF_Font *GetFont() { return m_Font; }

	protected:
		Game(const od::WindowParameters &params);
		virtual void ProcessEvent(SDL_Event &event) {}
		virtual void Awake() {}
		virtual void Update(uint32_t deltaTime) {}
		virtual void DrawUI() {}
		virtual void Draw() {}
		virtual void OnShutdown() {}

	private:
		void UpdateViewport();
		void SwapScenes();
		void CalculateDeltaTime();
		void PollEvents();

	protected:
		bool m_IsRunning = true;
		uint32_t m_TimeSinceStart = 0, m_DeltaTime = 0;
		TTF_Font *m_Font;
		std::chrono::high_resolution_clock::time_point m_ClockStart, m_ClockFrameStart, m_ClockFrameEnd;
		std::unique_ptr<od::Window> m_Window;
		glm::i32vec2 m_CursorPosition;

	private:
		SDL_GLContext m_GLCtx;
		std::unique_ptr<od::Scene> m_NextScene, m_Scene;
		glm::i32vec2 m_LastWindowSize;
	};
}
