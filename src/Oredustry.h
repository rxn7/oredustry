#pragma once

#include "core/Game.h"
#include "core/ui/Text.h"
#include "core/assets/Texture.h"
#include "Cursor.h"

// TODO: Tilemaps
// TODO: Spritesheet animations

class Oredustry : public od::Game {
public:
	Oredustry();

	void OnShutdown() override;
	void Awake() override;
	void Update(uint32_t deltaTime) override;
	void DrawUI() override;
	inline bool IsDebugOn() const { return m_DebugText->m_Visible; }
	inline static Oredustry *GetInstance() { return s_Instance; }

private:
	void UpdateDebug(uint32_t deltaTime);
	void DrawCursor();

private:
	std::unique_ptr<od::UI::Text> m_DebugText;
	std::unique_ptr<Cursor> m_Cursor;
	uint32_t m_DebugTextUpdateCounter = 0;
	static Oredustry *s_Instance;
};
