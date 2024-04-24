#ifndef BOOL_LOGIC_IMPL_H
#define BOOL_LOGIC_IMPL_H

#include "logic.h"

namespace logic
{

    ////////////////////////////////////
    //// BOOL LOGIC IMPLEMENTATION /////
    ////////////////////////////////////
    #pragma region BOOL LOGIC IMPLEMENTATION

    template<>
    inline bool padding(
        bool a_logic_state
    )
    {
        return a_logic_state;
    }

    template<>
    inline bool join(
        bool a_identity,
        bool a_x_0,
        bool a_x_1
    )
    {
        if (a_identity)
            return a_x_0 && a_x_1;
        else
            return a_x_0 || a_x_1;
            
    }

    template<>
    inline bool invert(
        bool a_x
    )
    {
        return !a_x;
    }

    #pragma endregion

}

#endif
