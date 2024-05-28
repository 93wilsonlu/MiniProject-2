#include "TextInput.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <string>
#include "Engine/IObject.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {

TextInput::TextInput(const std::string& text,
                     const std::string& font,
                     int fontSize,
                     float x,
                     float y,
                     float w,
                     float h,
                     unsigned char r,
                     unsigned char g,
                     unsigned char b,
                     unsigned char a,
                     float anchorX,
                     float anchorY)
    : IObject(x, y, w, h, anchorX, anchorY),
      font(Resources::GetInstance().GetFont(font, fontSize)),
      Text(text),
      Color(al_map_rgba(r, g, b, a)) {}

void TextInput::Draw() const {
    al_draw_text(font.get(), Color, Position.x - Anchor.x * GetTextWidth(),
                 Position.y - Anchor.y * GetTextHeight(), 0, Text.c_str());

    al_draw_rectangle(
        Position.x - Size.x * Anchor.x, Position.y - Size.y * Anchor.y,
        Position.x + Size.x * (1 - Anchor.x),
        Position.y + Size.y * (1 - Anchor.y), al_map_rgb(255, 255, 255), 2);
}

void TextInput::SetOnValueChangedCallback(
    std::function<void(int keyCode)> onValueChangedCallback) {
    OnValueChangedCallback = onValueChangedCallback;
}

void TextInput::OnKeyDown(int keyCode) {
    if (keyCode == ALLEGRO_KEY_BACKSPACE && Text.size() > 0) {
        Text.pop_back();
    } else if (Text.size() <= 15) {
        if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
            Text.push_back('a' + keyCode - ALLEGRO_KEY_A);
        } else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
            Text.push_back('0' + keyCode - ALLEGRO_KEY_0);
        }
    }
    if (OnValueChangedCallback) {
        OnValueChangedCallback(keyCode);
    }
}

int TextInput::GetTextWidth() const {
    return al_get_text_width(font.get(), Text.c_str());
}
int TextInput::GetTextHeight() const {
    return al_get_font_line_height(font.get());
}
}  // namespace Engine