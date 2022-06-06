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
	void RenderUI() override;
	inline static Oredustry *GetInstance() { return s_Instance; }

private:
	std::unique_ptr<Cursor> m_Cursor;
	static Oredustry *s_Instance;
};
