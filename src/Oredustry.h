#pragma once

#include "core/Game.h"
#include "core/assets/Texture.h"
#include "Cursor.h"

// TODO: Tilemaps
// TODO: Camera class
// TODO: Spritesheet animations
// TODO: Profiling!!!!!

class Oredustry : public od::Game {
public:
	Oredustry();

	void Ready() override;
	inline static Oredustry *GetInstance() { return s_Instance; }

private:
	void Update(uint32_t dt) override;
	void Tick(uint32_t dt) override;
	void RenderUI() override;
	void HandleRenderUI() override;
	void UpdateDebug(uint32_t dt);

private:
	std::unique_ptr<od::UI::Text> m_DebugText;
	std::unique_ptr<Cursor> m_Cursor;
	static Oredustry *s_Instance;
};
