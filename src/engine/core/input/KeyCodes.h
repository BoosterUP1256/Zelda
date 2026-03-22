#pragma once

namespace Gas {

    enum class Key
    {
        A,
        D,
        W,
        S,
        Space,

        Count,
        Unknown = -1
    };

    enum class MouseButton
    {
        Left,
        Middle,
        Right,

        Count,
        Unknown = -1
    };

    enum class Action
    {
        Press,
        Release,
        Repeat,

        Count,
        Unknown = -1
    };


}