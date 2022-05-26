#pragma once

#include "Libs.h"
#include "Window.h"
#include "Scene.h"
#include "assets/Font.h"

namespace od {
	typedef std::chrono::high_resolution_clock::time_point TimePoint;

	class Game {
	public:
		static Game *GetInstance();

		void Start();
		void Shutdown(bool error=false, std::string_view reason="");
		void SetScene(std::unique_ptr<od::Scene> scene);

		inline glm::i32vec2 GetCursorPosition() { return m_CursorPosition; }
		inline const od::Window &GetWindow() const { return *m_Window; }
		inline const od::Font &GetFont() const { return *m_Font; }

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
		std::shared_ptr<od::Font> m_Font;
		TimePoint m_StartTimePoint, m_FrameStartTimePoint, m_FrameEndTimePoint;
		std::unique_ptr<od::Window> m_Window;
		glm::i32vec2 m_CursorPosition;

	private:
		SDL_GLContext m_GLCtx;
		std::unique_ptr<od::Scene> m_NextScene, m_Scene;
		glm::i32vec2 m_LastWindowSize;
	};
}
