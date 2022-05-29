#pragma once

#include "UIElement.h"
#include "core/Color.h"

// TODO: Text rendering!!!
namespace od::UI {
	enum class TextAlign {
		Left,
		Center,
		Right,
	};

	class Text : public UIElement {
	public:
		Text(const glm::i32vec2 &position, const std::string_view &text, float scale, const od::Color &color = od::Colors::WHITE, TextAlign align = TextAlign::Left, const Anchors &anchors = ANCHORS_CENTER); virtual ~Text();
		void Render() override;
		void SetText(std::string_view text);

		inline glm::i32vec2 GetSize() const { return m_Size; }
		// inline std::string_view GetText() const { return gltGetText(m_GltText); }

	private:
		void UpdateModelMatrix();

	public:
		TextAlign m_Align;
		od::Color m_Color;
		float m_Scale;

	private:
		glm::f32mat4 m_ModelMatrix;
		// GLTtext *m_GltText = nullptr;
	};
}
