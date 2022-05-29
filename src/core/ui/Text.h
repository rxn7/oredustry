#pragma once

#include "UIElement.h"

// TODO: Text rendering!!!
namespace od::UI {
	enum class TextAlign {
		Left,
		Center,
		Right,
	};

	class Text : public UIElement {
	public:
		Text(const glm::i32vec2 &position, const std::string_view &text, float scale, const SDL_Color &color = {255,255,255,255}, TextAlign align = TextAlign::Left, const Anchors &anchors = ANCHORS_CENTER); virtual ~Text();
		void Render() override;
		void SetText(std::string_view text);

		inline glm::i32vec2 GetSize() const { return m_Size; }
		// inline std::string_view GetText() const { return gltGetText(m_GltText); }

	private:
		void UpdateModelMatrix();

	public:
		TextAlign m_Align;
		SDL_Color m_Color;
		float m_Scale;

	private:
		glm::f32mat4 m_ModelMatrix;
		// GLTtext *m_GltText = nullptr;
	};
}
