#include <iostream>

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : " << ((argc >= 1) ? argv[0] : "program") << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}