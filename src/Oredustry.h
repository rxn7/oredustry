#pragma once

#include "core/Game.h"
#include "core/ui/Text.h"
#include "core/assets/Texture.h"
#include "Cursor.h"

class Oredustry : public od::Game {
public:
	Oredustry();

	void OnShutdown() override;
	void Awake() override;
	void Update(uint32_t deltaTime) override;
	void DrawUI() override;

private:
	void DrawDebug();
	void DrawCursor();

private:
	std::shared_ptr<od::UI::Text> m_DebugText;
	std::unique_ptr<Cursor> m_Cursor;
	uint32_t m_DebugTextUpdateCounter = 0;
};
