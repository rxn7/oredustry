#include "Text.h"
#include "core/Game.h"
#include <glm/gtc/matrix_transform.hpp>

od::UI::Text::Text(const glm::i32vec2 &position, const std::string_view &text, float scale, const od::Color &color, TextAlign align, const Anchors &anchors) :
m_Align(align),
m_Scale(scale),
od::UI::UIElement(position, {0,0}, anchors) {
	m_Color = color;
	SetText(text);
	// m_GltText = gltCreateText();
}

od::UI::Text::~Text() {
	// gltDeleteText(m_GltText);
}

void od::UI::Text::SetText(std::string_view text) {
	// gltSetText(m_GltText, text.data());
}

void od::UI::Text::Render() {
	ENSURE_VISIBLE


	/*
	glm::mat4 modelProjection = od::Game::GetInstance()->GetProjection() * m_ModelMatrix;

	gltBeginDraw();
	// gltColor(static_cast<float>(m_Color.r) / 255.0f, static_cast<float>(m_Color.g) / 255.0f, static_cast<float>(m_Color.b) / 255.0f, static_cast<float>(m_Color.a) / 255.0f);
	gltColor(0.0f, 0.0f, 0.0f, 1.0f);
	gltDrawText(m_GltText, &modelProjection[0][0]);
	gltEndDraw();
	*/

	od::UI::UIElement::Render();
}
