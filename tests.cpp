#include "test_simple_calc.inl"
#include "test_credit_calc.inl"
#include "test_deposit_calc.inl"

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

