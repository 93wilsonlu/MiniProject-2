#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP
#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <functional>
#include <string>
#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"

namespace Engine {
class TextInput : public IObject, public IControl {
   protected:
    // Smart pointer to font.
    std::shared_ptr<ALLEGRO_FONT> font;
    std::function<void(int keyCode)> OnValueChangedCallback;

   public:
    // Text to draw.
    std::string Text;
    // Text's color.
    ALLEGRO_COLOR Color;

    explicit TextInput(const std::string& text,
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
                       float anchorY);

    void Draw() const override;
    void SetOnValueChangedCallback(std::function<void(int keyCode)> onValueChangedCallback);


    int GetTextWidth() const;

    int GetTextHeight() const;
    void OnKeyDown(int keyCode) override;
};
}  // namespace Engine
#endif  // TEXTINPUT_HPP
