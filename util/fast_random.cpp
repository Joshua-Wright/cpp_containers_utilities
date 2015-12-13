// (c) Copyright 2015 Josh Wright
/* for when you want lots and lots of random data for testing,
 * but don't really care about the randomness of that random data.
 * NOT FOR CRYPTOGRAPHIC USES, THIS IS NOT NEARLY RANDOM ENOUGH FOR THAT!!
 */
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include <random>

const std::size_t BUFFER_SIZE = 1024 * 1024;

unsigned long long random_ullong() {
    return ((unsigned long long) rand()) |
           (((unsigned long long) rand()) << 32);
}

int main(int argc, char const *argv[]) {
    if (isatty(fileno(stdout))) {
        std::cout << "Will not write output to terminal!" << std::endl;
        std::cout << "usage: " << argv[0] << " > [output file]" << std::endl;
        std::cout << "usage: " << argv[0] << " | COMMAND" << std::endl;
        return 1;
    }
    srand((unsigned int) time(nullptr));
    unsigned long long *randoms = new unsigned long long int[BUFFER_SIZE];
    for (int i=0; i<BUFFER_SIZE; i++) {
        randoms[i] = random_ullong();
    }
    while (!std::cout.eof()) {
        unsigned long long int newrand = random_ullong();
        for (int i=0; i<BUFFER_SIZE; i++) {
            randoms[i] ^= newrand;
            newrand ^= randoms[BUFFER_SIZE - i];
        }
        std::cout.write((char *) randoms, sizeof(unsigned long long) * BUFFER_SIZE);
    }

    return 0;
}
