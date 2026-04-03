#include <algorithm>
#include <iostream>

#include "core/input/MouseListener.h"

namespace Gas {

    // TODO: Consider moving making a current_frame translation unit header for keyboard, mouse and gamepad
    // TODO: input so I don't have to keep three frame IDs. Maybe a separate time or delta class

    static uint64_t s_currentFrame    = 0;
    static uint64_t s_lastScrollFrame = 0;
    static float    s_scrollX         = 0.0f;
    static float    s_scrollY         = 0.0f;

    static uint64_t s_lastMoveFrame   = 0;
    static float    s_xPos            = 0.0f;
    static float    s_yPos            = 0.0f;
    static float    s_dx              = 0.0f;
    static float    s_dy              = 0.0f;

    static std::array<bool, static_cast<int>(MouseButton::Count)>     s_currentButtonsDown {};
    static std::array<uint64_t, static_cast<int>(MouseButton::Count)> s_lastPressedFrame   {};
    static std::array<uint64_t, static_cast<int>(MouseButton::Count)> s_lastReleasedFrame  {};


    void MouseListener::init()
    {
        // TODO: consider removing if unused 
    }

    void MouseListener::update()
    {
        // s_scrollX = 0.0f;
        // s_scrollY = 0.0f;
        // s_lastX   = s_xPos;
        // s_lastY   = s_yPos;
        //
        // s_previousButtonsDown = s_currentButtonsDown;
        s_currentFrame++;
    }

    bool MouseListener::isDragging()
    {
        if (s_lastMoveFrame != s_currentFrame)
            return false;

        for (const bool isDown : s_currentButtonsDown)
        {
            if (isDown) return true;
        }

        return false;
    }

    void MouseListener::s_handleMousePosEvent(float xPos, float yPos)
    {
        // s_lastX = s_xPos;
        // s_lastY = s_yPos;
        // s_xPos = xPos;
        // s_yPos = yPos;
        // s_isDragging = s_currentButtonsDown[0] || s_currentButtonsDown[1] || s_currentButtonsDown[2];

        if (s_lastMoveFrame != s_currentFrame)
        {
            s_dx = xPos - s_xPos;
            s_dy = yPos - s_yPos;
            s_lastMoveFrame = s_currentFrame;
        }
        else
        {
            // handles high polling mice
            s_dx += xPos - s_xPos;
            s_dy += yPos - s_yPos;
        }

        s_xPos = xPos;
        s_yPos = yPos;
    }

    void MouseListener::s_handleMouseButtonEvent(MouseButton button, Action action)
    {

        int index = static_cast<int>(button);

        // TODO: check this code for real to handle more than normal amount of mouse buttons
        if (button == MouseButton::Unknown || index >= s_currentButtonsDown.size() || index < 0)
        {
            std::cout << "WARNING: Unknown mouse button detected!\n";
            return;
        }

        if (action == Action::Press)
        {
            s_currentButtonsDown[index] = true;
            s_lastPressedFrame[index] = s_currentFrame;
        }
        else if (action == Action::Release)
        {
            s_currentButtonsDown[index] = false;
            s_lastReleasedFrame[index] = s_currentFrame;
        }
    }

    void MouseListener::s_handleMouseScrollEvent(float xOffset, float yOffset)
    {
        if (s_lastScrollFrame != s_currentFrame)
        {
            s_scrollX = xOffset;
            s_scrollY = yOffset;
            s_lastScrollFrame = s_currentFrame;
        }
        else
        {
            // accumulate if wheel spins really fast in single frame
            s_scrollX += xOffset;
            s_scrollY += yOffset;
        }
    }

    bool MouseListener::isDragging(MouseButton button)
    {
        bool buttonDragging = s_currentButtonsDown[static_cast<int>(button)];
        return buttonDragging && (s_lastMoveFrame == s_currentFrame);
    }

    // TODO: Will have to test mice with more buttons
    // if && button != MouseButton::Unknown doesnt try
    // if (index < mouseButtonPressed.size())
    // COME TO THINK OF IT AGAIN UNKNOWN IS BAD BECAUSE WE
    // MAY WANT TO STILL PROCESS INPUT FROM UNKNOWN BUTTONS
    bool MouseListener::isMouseButtonDown(MouseButton button)
    {
        int index = static_cast<int>(button);
        if (button != MouseButton::Unknown && index < s_currentButtonsDown.size())
            return s_currentButtonsDown[index];

        return false;
    }

    bool MouseListener::isMouseButtonPressed(MouseButton button)
    {
        int index = static_cast<int>(button);
        if (button != MouseButton::Unknown && index < s_lastPressedFrame.size())
            return s_lastPressedFrame[index] == s_currentFrame;

        return false;
    }

    bool MouseListener::isMouseButtonReleased(MouseButton button)
    {
        int index = static_cast<int>(button);
        if (button != MouseButton::Unknown && index < s_lastReleasedFrame.size())
            return s_lastReleasedFrame[index] == s_currentFrame;

        return false;
    }

    float MouseListener::getX()       { return s_xPos; }
    float MouseListener::getY()       { return s_yPos; }
    float MouseListener::getDx()      { return (s_lastMoveFrame == s_currentFrame) ? s_dx : 0.0f; }
    float MouseListener::getDy()      { return (s_lastMoveFrame == s_currentFrame) ? s_dy : 0.0f; }
    float MouseListener::getScrollX() { return (s_lastScrollFrame == s_currentFrame) ? s_scrollX : 0.0f; }
    float MouseListener::getScrollY() { return (s_lastScrollFrame == s_currentFrame) ? s_scrollY : 0.0f; }

}
