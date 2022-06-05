#pragma once

#include "core/Libs.h"
#include "core/Sprite.h"

class Player : public od::Sprite {
public:
	Player();
	void Update(uint32_t deltaTime) override;
	void Render() override;
};
