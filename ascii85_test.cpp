#include <gtest/gtest.h>
#include <sstream>
#include "ascii85.h"

TEST(Ascii85Test, EncodeSimple) {
    std::istringstream input("Hello");
    std::ostringstream output;

    Ascii85::encode(input, output);

    EXPECT_EQ(output.str(), "<~9jqo^BlbD-BleB~>");
}

TEST(Ascii85Test, EncodeEmpty) {
    std::istringstream input("");
    std::ostringstream output;

    Ascii85::encode(input, output);

    EXPECT_EQ(output.str(), "");
}

TEST(Ascii85Test, EncodeWithPadding) {
    std::istringstream input("Hi");
    std::ostringstream output;

    Ascii85::encode(input, output);

    EXPECT_EQ(output.str(), "<~9jqo^~>");
}

TEST(Ascii85Test, EncodeAllZeros) {
    std::istringstream input("0000");
    std::ostringstream output;

    Ascii85::encode(input, output);

    EXPECT_EQ(output.str(), "<~z~>");
}

TEST(Ascii85Test, DecodeSimple) {
    std::istringstream input("<~9jqo^BlbD-BleB~>");
    std::ostringstream output;

    Ascii85::decode(input, output);

    EXPECT_EQ(output.str(), "Hello");
}

TEST(Ascii85Test, DecodeEmpty) {
    std::istringstream input("");
    std::ostringstream output;

    Ascii85::decode(input, output);

    EXPECT_EQ(output.str(), "");
}

TEST(Ascii85Test, DecodeInvalidCharacter) {
    std::istringstream input("<~invalid~>");
    std::ostringstream output;

    EXPECT_THROW(Ascii85::decode(input, output), std::runtime_error);
}

TEST(Ascii85Test, DecodeZero) {
    std::istringstream input("<~z~>");
    std::ostringstream output;

    Ascii85::decode(input, output);

    EXPECT_EQ(output.str(), "0000");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
