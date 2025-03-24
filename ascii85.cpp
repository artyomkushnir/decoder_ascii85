#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

class Ascii85 {
public:
    static void encode(std::istream& input, std::ostream& output) {
        std::vector<unsigned char> buffer(4);
        std::vector<char> encoded(5);
        while (input.read(reinterpret_cast<char*>(buffer.data()), 4)) {
            std::size_t bytesRead = input.gcount();
            if (bytesRead == 0) break;

            // Pad with zeros if necessary
            for (std::size_t i = bytesRead; i < 4; ++i) {
                buffer[i] = 0;
            }

            unsigned int value = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
            if (value == 0 && bytesRead == 4) {
                output.put('z');
                continue;
            }

            for (int i = 4; i >= 0; --i) {
                encoded[i] = (value % 85) + '!';
                value /= 85;
            }

            for (std::size_t i = 0; i < bytesRead + 1; ++i) {
                output.put(encoded[i]);
            }
        }
    }

    static void decode(std::istream& input, std::ostream& output) {
        std::vector<char> buffer(5);
        std::vector<unsigned char> decoded(4);
        while (input.read(buffer.data(), 5)) {
            std::size_t bytesRead = input.gcount();
            if (bytesRead == 0) break;

            if (buffer[0] == 'z') {
                output.put(0);
                output.put(0);
                output.put(0);
                output.put(0);
                continue;
            }

            unsigned int value = 0;
            for (std::size_t i = 0; i < bytesRead; ++i) {
                if (buffer[i] < '!' || buffer[i] > 'u') {
                    throw std::runtime_error("Invalid ASCII85 character");
                }
                value = value * 85 + (buffer[i] - '!');
            }

            for (int i = 3; i >= 0; --i) {
                decoded[i] = value & 0xFF;
                value >>= 8;
            }

            for (std::size_t i = 0; i < bytesRead - 1; ++i) {
                output.put(decoded[i]);
            }
        }
    }
};

int testmain(int argc, char* argv[]) {
    bool decodeMode = false;

    if (argc > 1 && std::string(argv[1]) == "-d") {
        decodeMode = true;
    } else if (argc > 1 && std::string(argv[1]) == "-e") {
        decodeMode = false;
    } else if (argc > 1) {
        std::cerr << "Usage: " << argv[0] << " [-d | -e]" << std::endl;
        return 1;
    }

    try {
        if (decodeMode) {
            Ascii85::decode(std::cin, std::cout);
        } else {
            Ascii85::encode(std::cin, std::cout);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
