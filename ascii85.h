#ifndef ASCII85_H
#define ASCII85_H

#include <iostream>
#include <vector>
#include <stdexcept>

class Ascii85 {
public:
    static void encode(std::istream& input, std::ostream& output);
    static void decode(std::istream& input, std::ostream& output);
};

#endif // ASCII85_H
