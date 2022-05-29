#pragma once

#include "core/Sprite.h"

class Cursor : public od::Sprite {
public:
	Cursor(float size);
	void Render() override;
};
