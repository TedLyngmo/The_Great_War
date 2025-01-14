#ifndef CHECKBOX_H
#define CHECKBOX_H

#pragma once
#include "Drawable.h"
#include "Label.h"
#include "ToggleButton.h"

#include <SDL.h>

#include <functional>
#include <memory>
#include <string>

class Checkbox : public InputDrawable {
public:
    // Constructor
    Checkbox(MainWindow& mw, int x, int y, int Height, std::string text, int textSize, std::function<void(bool)> f = {}, int keybind = 0);
    Checkbox(MainWindow& mw, int x, int y, int Height, std::string text, int textSize, Anchor anchor, std::function<void(bool)> f = nullptr, int keybind = 0);

    // Called when received input, to check whether the click was in this button
    void HandleInput(const SDL_Event& ev) override;

    // Change the button's position
    void ChangePosition(int x, int y, int Height);

    // Change the function bound to this button
    void ChangeFunctionBinding(std::function<void(bool)> f);

    // Change the keyboard key that is bound to this button
    void ChangeKeybind(int keybind);

    // Change the Checkboxes text
    void ChangeText(std::string text);

    // Change the Checkboxes text size
    void ChangeTextSize(int size);

    // Change the current value of the button
    void ChangeValue(bool val);

    // Get the value of the toggle button
    bool GetValue();

    // Play the button's onClick sound
    void Playsound();

    // Execute the function that was bound to this button
    void CallBoundFunction();

    // Enable/Disable the checkbox
    void SetActive(bool state) override;

protected:
    // Render the Checkbox on the screen
    void pDraw() override;

    // The Drawables that make up this Drawable
    // std::unique_ptr<ToggleButton> toggleButton;
    // std::unique_ptr<Label> label;
    ToggleButton toggleButton;
    Label label;
};

#endif
