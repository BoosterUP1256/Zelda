#include "core/input/MouseListener.h"

namespace Gas {

    // TODO: Implement frame stamping

    static float               s_scrollX              = 0.0f;
    static float               s_scrollY              = 0.0f;
    static float               s_xPos                 = 0.0f; 
    static float               s_yPos                 = 0.0f;
    static float               s_lastY                = 0.0f;
    static float               s_lastX                = 0.0f;
    static bool                s_isDragging           = 0.0f;
    static std::array<bool, 3> s_currentButtonsDown    {};
    static std::array<bool, 3> s_previousButtonsDown   {};


    void MouseListener::init()
    {
        // TODO: consider removing if unused 
    }

    void MouseListener::update()
    {
        s_scrollX = 0.0f;
        s_scrollY = 0.0f;
        s_lastX   = s_xPos;
        s_lastY   = s_yPos;

        s_previousButtonsDown = s_currentButtonsDown;
    }

    void MouseListener::s_handleMousePosEvent(float xPos, float yPos)
    {
        s_lastX = s_xPos;
        s_lastY = s_yPos;
        s_xPos = xPos;
        s_yPos = yPos;
        s_isDragging = s_currentButtonsDown[0] || s_currentButtonsDown[1] || s_currentButtonsDown[2];
    }

    void MouseListener::s_handleMouseButtonEvent(MouseButton button, Action action)
    {

        int index = static_cast<int>(button);

        // TODO: Will have to test mice with more buttons
        // if && button != MouseButton::Unknown doesnt try
        // if (index < mouseButtonPressed.size())
        if (action == Action::Press)
        {
            if (button != MouseButton::Unknown)
                s_currentButtonsDown[index] = true;
        }
        else if (action == Action::Release)
        {
            if (button != MouseButton::Unknown)
            {
                s_currentButtonsDown[index] = false;
                s_isDragging = false;
            }
        }
    }

    void MouseListener::s_handleMouseScrollEvent(float xOffset, float yOffset)
    {
        s_scrollX = xOffset;
        s_scrollY = yOffset;
    }

    bool MouseListener::isDragging()
    {
        return s_isDragging;
    }

    // TODO: Will have to test mice with more buttons
    // if && button != MouseButton::Unknown doesnt try
    // if (index < mouseButtonPressed.size())
    // COME TO THINK OF IT AGAIN UNKNOWN IS BAD BECAUSE WE
    // MAY WANT TO STILL PROCESS INPUT FROM UNKNOWN BUTTONS
    bool MouseListener::isMouseButtonDown(MouseButton button)
    {
        if (button != MouseButton::Unknown)
            return s_currentButtonsDown[static_cast<int>(button)];
        
        return false;
    }

    bool MouseListener::isMouseButtonPressed(MouseButton button)
    {
        int index = static_cast<int>(button);
        if (button != MouseButton::Unknown)
            return s_currentButtonsDown[index] && !s_previousButtonsDown[index];
        
        return false;
    }

    bool MouseListener::isMouseButtonReleased(MouseButton button)
    {
        int index = static_cast<int>(button);
        if (button != MouseButton::Unknown)
            return !s_currentButtonsDown[index] && s_previousButtonsDown[index];
        
        return false;
    }

    float MouseListener::getX()       { return s_xPos; }
    float MouseListener::getY()       { return s_yPos; }
    float MouseListener::getDx()      { return s_xPos - s_lastX; }
    float MouseListener::getDy()      { return s_yPos - s_lastY; }
    float MouseListener::getScrollX() { return s_scrollX; }
    float MouseListener::getScrollY() { return s_scrollY; }

}
