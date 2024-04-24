#include <iostream>
#include <assert.h>
#include "include/logic.h"
#include "include/bool_logic_impl.h"

#define APPROX_EQ(x, y, threshold) std::abs(x-y) < threshold

#define LOG(x) if (ENABLE_DEBUG_LOGS) std::cout << x;

#define TEST(void_fn) \
    void_fn(); \
    LOG("TEST COMPLETED: " << #void_fn << std::endl);

using namespace logic;

#pragma region UNIT_TESTS

void test_logic_join(

)
{   
    /// Inputs.
    bool l_identity;
    bool l_a;
    bool l_b;
    
    l_identity = 0;
    l_a = 0;
    l_b = 0;
    assert(join(l_identity, l_a, l_b) == 0);

    l_identity = 0;
    l_a = 0;
    l_b = 1;
    assert(join(l_identity, l_a, l_b) == 1);
    
    l_identity = 0;
    l_a = 1;
    l_b = 0;
    assert(join(l_identity, l_a, l_b) == 1);

    l_identity = 0;
    l_a = 1;
    l_b = 1;
    assert(join(l_identity, l_a, l_b) == 1);

    l_identity = 1;
    l_a = 0;
    l_b = 0;
    assert(join(l_identity, l_a, l_b) == 0);

    l_identity = 1;
    l_a = 0;
    l_b = 1;
    assert(join(l_identity, l_a, l_b) == 0);

    l_identity = 1;
    l_a = 1;
    l_b = 0;
    assert(join(l_identity, l_a, l_b) == 0);

    l_identity = 1;
    l_a = 1;
    l_b = 1;
    assert(join(l_identity, l_a, l_b) == 1);

    ////////////
    /// TEST VARIADIC INPUTS

    /// OR of onehot is 1.
    assert(join<bool>(false, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0) == 1);
    
    assert(join<bool>(false, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0) == 1);

    assert(join<bool>(false, 0, 0, 0, 0, 0, 0, 0, 0) == 0);

    /// AND of onenot is 0.
    assert(join<bool>(1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1) == 0);
    
    assert(join<bool>(1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1) == 0);

    assert(join<bool>(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1) == 1);
    
}

void test_logic_conjoin(

)
{
    /// Inputs.
    bool l_a;
    bool l_b;

    l_a = 0;
    l_b = 0;
    assert(conjoin(l_a, l_b) == 0);

    l_a = 0;
    l_b = 1;
    assert(conjoin(l_a, l_b) == 0);

    l_a = 1;
    l_b = 0;
    assert(conjoin(l_a, l_b) == 0);

    l_a = 1;
    l_b = 1;
    assert(conjoin(l_a, l_b) == 1);
    
}

void test_logic_disjoin(

)
{
    /// Inputs.
    bool l_a;
    bool l_b;

    l_a = 0;
    l_b = 0;
    assert(disjoin(l_a, l_b) == 0);

    l_a = 0;
    l_b = 1;
    assert(disjoin(l_a, l_b) == 1);

    l_a = 1;
    l_b = 0;
    assert(disjoin(l_a, l_b) == 1);

    l_a = 1;
    l_b = 1;
    assert(disjoin(l_a, l_b) == 1);
    
}

void test_logic_exor(

)
{
    /// Inputs.
    bool l_a;
    bool l_b;

    l_a = 0;
    l_b = 0;
    assert(exor(l_a, l_b) == 0);
    
    l_a = 0;
    l_b = 1;
    assert(exor(l_a, l_b) == 1);
    
    l_a = 1;
    l_b = 0;
    assert(exor(l_a, l_b) == 1);
    
    l_a = 1;
    l_b = 1;
    assert(exor(l_a, l_b) == 0);

    // Test for variadic args.

    assert(exor(true, true, false, false) == 0);

    assert(exor(true, true, false, true) == 1);

    assert(exor(true, false, false, true) == 0);

    assert(exor(false, false, false, true) == 1);

}

void test_logic_exnor(

)
{
    /// Inputs.
    std::list<bool> l_a;
    std::list<bool> l_b;

    l_a = { 0, 1, 1, 0, 1 };
    l_b = { 0, 1, 1, 0, 0 };
    assert(exnor(l_a, l_b) == false);

    l_a = { 0, 1, 1, 0, 1 };
    l_b = { 0, 1, 1, 0, 1 };
    assert(exnor(l_a, l_b) == true);

    l_a = { 0, 1, 1, 0, 1 };
    l_b = { 0, 0, 1, 1, 0 };
    assert(exnor(l_a, l_b) == false);

    l_a = { 0, 1, 1, 1, 1, 0, 0 };
    l_b = { 0, 1, 1, 1, 1, 0, 0 };
    assert(exnor(l_a, l_b) == true);
    
}

void test_logic_full_add(

)
{
    /// Inputs.
    bool l_a;
    bool l_b;
    bool l_cin;

    /// Outputs.
    bool l_sout;
    bool l_cout;
    
    l_a = 0;
    l_b = 0;
    l_cin = 0;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 0 && l_sout == 0);
    
    l_a = 0;
    l_b = 0;
    l_cin = 1;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 0 && l_sout == 1);
    
    l_a = 0;
    l_b = 1;
    l_cin = 0;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 0 && l_sout == 1);
    
    l_a = 0;
    l_b = 1;
    l_cin = 1;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 1 && l_sout == 0);
    
    l_a = 1;
    l_b = 0;
    l_cin = 0;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 0 && l_sout == 1);
    
    l_a = 1;
    l_b = 0;
    l_cin = 1;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 1 && l_sout == 0);
    
    l_a = 1;
    l_b = 1;
    l_cin = 0;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 1 && l_sout == 0);
    
    l_a = 1;
    l_b = 1;
    l_cin = 1;
    full_add(l_a, l_b, l_cin, l_cout, l_sout);
    assert(l_cout == 1 && l_sout == 1);
    
}

void test_logic_add(

)
{
    /// Inputs.
    std::list<bool> l_a;
    std::list<bool> l_b;

    /// Outputs.
    std::list<bool> l_desired;

    // TEST ADDITION OF HOMOGENOUS SIZED OPERANDS
    l_a =       { 0, 1, 1, 0, 0, 1 };
    l_b =       { 1, 0, 0, 0, 0, 0 };
    l_desired = { 1, 1, 1, 0, 0, 1, 0 };
    assert(add(l_a, l_b) == l_desired);

    // TEST ADDITION OF HETEROGENEOUS SIZED OPERANDS
    l_a =       { 0, 1, 1, 0, 0, 1 };
    l_b =       { 1 };
    l_desired = { 1, 1, 1, 0, 0, 1, 0 };
    assert(add(l_a, l_b) == l_desired);

    // TEST ADDITION OF HETEROGENEOUS SIZED OPERANDS
    l_a =       { 0, 1, 1, 0, 1 };
    l_b =       { 0, 1, 1, 0 };
    l_desired = { 0, 0, 1, 1, 1, 0 };
    assert(add(l_a, l_b) == l_desired);

    // TEST ADDITION OF HETEROGENEOUS SIZED OPERANDS
    l_a =       { 0, 1, 1, 1 };
    l_b =       { 0, 1, 1, 0, 0, 0, 1, 1 };
    l_desired = { 0, 0, 1, 0, 1, 0, 1, 1, 0 };
    assert(add(l_a, l_b) == l_desired);

    // TEST ADDITION OF HETEROGENEOUS SIZED OPERANDS
    l_a =       { 0, 0, 0, 0, 0 };
    l_b =       { 0 };
    l_desired = { 0, 0, 0, 0, 0, 0 };
    assert(add(l_a, l_b) == l_desired);

    // TEST ADDITION OF HETEROGENEOUS SIZED OPERANDS
    l_a =       { 1, 1, 1, 1, 1 };
    l_b =       { 1 };
    l_desired = { 0, 0, 0, 0, 0, 1 };
    assert(add(l_a, l_b) == l_desired);
    
}

void test_logic_outer_product(

)
{
    /// Inputs.
    std::list<bool> l_a;
    std::list<bool> l_b;
    
    /// Desired.
    std::list<std::list<bool>> l_desired;

    l_a = { 0, 1, 1, 0, 1 };
    l_b = { 1, 0, 1 };
    l_desired = {
        { 0, 0, 0 },
        { 1, 0, 1 },
        { 1, 0, 1 },
        { 0, 0, 0 },
        { 1, 0, 1 }
    };
    assert(outer_product(l_a, l_b) == l_desired);

    l_a = { 0, 0, 1, 0, 1 };
    l_b = { 1, 1, 0, 1 };
    l_desired = {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 1, 0, 1 },
        { 0, 0, 0, 0 },
        { 1, 1, 0, 1 }
    };
    assert(outer_product(l_a, l_b) == l_desired);

}

void test_logic_multiply(

)
{
    /// Inputs.
    std::list<bool> l_a;
    std::list<bool> l_b;

    /// Desired.
    std::list<bool> l_desired;

    /// Multiplying two heterogeneous numbers.
    l_a =       { 1, 1, 0, 1, 0 };
    l_b =       { 0, 1, 1, 0, 0, 1 };
    l_desired = { 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0 };
    assert(multiply(l_a, l_b) == l_desired);

    /// Multiplying two heterogeneous numbers.
    l_a =       { 1, 1, 1 };
    l_b =       { 1, 1, 1, 0, 0, 1 };
    l_desired = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    assert(multiply(l_a, l_b) == l_desired);

    /// Multiplying two heterogeneous numbers.
    l_a =       { 1, 0, 0, 1, 0, 1, 0, 0, 1 };
    l_b =       { 1, 1, 1, 0 };
    l_desired = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0 };
    assert(multiply(l_a, l_b) == l_desired);

    /// Multiplying by 1. Identity case.
    l_a =       { 1 };
    l_b =       { 1, 1, 1, 0, 0, 1 };
    l_desired = { 1, 1, 1, 0, 0, 1, 0 };
    assert(multiply(l_a, l_b) == l_desired);

    /// Equivalent to a right-shift by 1.
    l_a =       { 0, 1 };
    l_b =       { 1, 1, 1, 0, 0, 1 };
    l_desired = { 0, 1, 1, 1, 0, 0, 1, 0 };
    assert(multiply(l_a, l_b) == l_desired);
    
}

void unit_test_main(

)
{
    constexpr bool ENABLE_DEBUG_LOGS = true;

    // LOGIC Unit tests (using bool-specialized logic)

    LOG("---------------------------------------" << std::endl);
    LOG("-------STARTING LOGIC UNIT TESTS-------" << std::endl);
    LOG("---------------------------------------" << std::endl);

    TEST(test_logic_join);
    TEST(test_logic_conjoin);
    TEST(test_logic_disjoin);
    TEST(test_logic_exor);
    TEST(test_logic_exnor);
    TEST(test_logic_full_add);
    TEST(test_logic_add);
    TEST(test_logic_outer_product);
    TEST(test_logic_multiply);

}

#pragma endregion

int main(

)
{
    unit_test_main();
}
