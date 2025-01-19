#ifndef LOGIC_H
#define LOGIC_H

#include <unistd.h>
#include <list>
#include <assert.h>

namespace logic
{

    ////////////////////////////////////
    ///////// USER SPECIALIZED /////////
    ////////////////////////////////////
    #pragma region USER SPECIALIZED

    template<typename T>
    inline T padding(
        bool a_logic_state
    );

    template<typename T>
    inline T join(
        bool a_identity,
        T a_operand_0,
        T a_operand_1
    );

    template<typename T>
    inline T invert(
        T a_operand
    );

    #pragma endregion

    ////////////////////////////////////
    ///////// BASIC FUNCTIONS //////////
    ////////////////////////////////////
    #pragma region BASIC FUNCTIONS

    template<typename T, typename ... REMAINING> 
        requires (sizeof...(REMAINING) > 0)
    inline T join(
        bool a_identity,
        T a_operand_0,
        T a_operand_1,
        REMAINING ... a_remaining_operands
    )
    {
        /// Offload the variadic nature of junctions
        ///     to a pre-defined helper function (needed for
        ///     template specialization).
        
        T l_junction = join(a_identity, a_operand_0, a_operand_1);
        
        return join<T>(a_identity, l_junction, a_remaining_operands...);
        
    }
    
    template<typename T>
    inline T disjoin(
        T a_x_0,
        T a_x_1,
        auto ... a_remaining
    )
    {
        return join<T>(false, a_x_0, a_x_1, a_remaining...);
    }

    template<typename T>
    inline T conjoin(
        T a_x_0,
        T a_x_1,
        auto ... a_remaining
    )
    {
        return join<T>(true, a_x_0, a_x_1, a_remaining...);
    }

    #pragma endregion

    ////////////////////////////////////
    /////// COMPOSITE FUNCTIONS ////////
    ////////////////////////////////////
    #pragma region COMPOSITE FUNCTIONS

    template<typename T>
    inline T exor(
        T a_x_0,
        T a_x_1,
        auto ... a_remaining_operands
    )
    {
        T l_first_exor = disjoin(
            conjoin(invert(a_x_0),a_x_1),
            conjoin(a_x_0,invert(a_x_1))
        );
        
        if constexpr (sizeof...(a_remaining_operands) > 0)
        {
            return exor<T>(l_first_exor, a_remaining_operands...);
        }
        else
        {
            return l_first_exor;
        }
        
    }

    template<typename T>
    inline T exnor(
        T a_x_0,
        T a_x_1,
        auto ... a_remaining_operands
    )
    {
        return invert(exor<T>(a_x_0, a_x_1, a_remaining_operands...));
    }

    template<typename T>
    inline T exnor(
        std::list<T> a_x_0,
        std::list<T> a_x_1
    )
    {
        assert(a_x_0.size() == a_x_1.size());
        
        T l_result = padding<T>(true);

        auto l_it_0 = a_x_0.begin();
        auto l_it_1 = a_x_1.begin();

        while (l_it_0 != a_x_0.end() && l_it_1 != a_x_1.end())
            l_result = conjoin(l_result, exnor(*(l_it_0++), *(l_it_1++)));

        return l_result;
        
    }

    template<typename T>
    inline void full_add(
        T a_x_0,
        T a_x_1,
        T a_cin,
        T& a_cout,
        T& a_sout
    )
    {
        a_cout = disjoin(
            conjoin(a_x_0,a_x_1),
            conjoin(a_x_0,a_cin),
            conjoin(a_x_1,a_cin)
        );

        a_sout = exor(a_x_0, a_x_1, a_cin);

    }

    template<typename T>
    inline void pad_left(
        std::list<T>& a_x,
        size_t a_count,
        T a_padding = padding<T>(false)
    )
    {
        a_x.splice(a_x.begin(), std::list<T>(a_count, a_padding));
    }

    template<typename T>
    inline void pad_right(
        std::list<T>& a_x,
        size_t a_count,
        T a_padding = padding<T>(false)
    )
    {
        a_x.splice(a_x.end(), std::list<T>(a_count, a_padding));
    }

    template<typename T>
    inline std::list<T> add(
        std::list<T> a_x_0,
        std::list<T> a_x_1,
        T a_cin = padding<T>(false)
    )
    {
        const size_t l_largest_opd_size = 
            std::max(
                a_x_0.size(),
                a_x_1.size()
            );

        // Resize either operand to be operable
        pad_right(a_x_0, l_largest_opd_size - a_x_0.size());
        pad_right(a_x_1, l_largest_opd_size - a_x_1.size());
        
        // Create carry bit
        T l_carry = a_cin;

        // Initialize SUM OUT result vector
        std::list<T> l_result(l_largest_opd_size);

        auto l_it_0 = a_x_0.begin();
        auto l_it_1 = a_x_1.begin();
        auto l_it_result = l_result.begin();

        while (l_it_result != l_result.end())
            full_add(
                *(l_it_0++),
                *(l_it_1++),
                l_carry,
                l_carry,
                *(l_it_result++)
            );

        // CARRY BIT MATTERS. Save to result vector
        l_result.push_back(l_carry);

        return l_result;

    }

    template<typename T>
    inline std::list<std::list<T>> outer_product(
        std::list<T> a_x_0,
        std::list<T> a_x_1
    )
    {
        std::list<std::list<T>> l_result;

        for (auto l_element_0 : a_x_0)
        {
            std::list<T> l_row;
            
            for (auto l_element_1 : a_x_1)
                l_row.push_back(conjoin(l_element_0, l_element_1));

            l_result.push_back(l_row);

        }

        return l_result;
        
    }

    template<typename T>
    std::list<T> multiply(
        std::list<T> a_x_0,
        std::list<T> a_x_1
    )
    {
        /// Construct reusable padding bit.
        T l_padding = padding<T>(false);

        /// First, compute outer product.
        auto l_outer_product = outer_product(a_x_0, a_x_1);
        
        /// Construct result bit string. It must start as
        ///     having the size as the col count of outer prod.
        ///     It must also start as all zeroes.
        std::list<T> l_result(a_x_1.size(), l_padding);
        
        /// Now, perform cumulative addition.
        for (int i = 0; auto l_row : l_outer_product)
        {
            pad_left(l_row, i++, l_padding);
            l_result = add(l_result, l_row);
        }
        
        return l_result;
        
    }

    #pragma endregion

}

#endif
