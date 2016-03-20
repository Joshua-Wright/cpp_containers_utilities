// (c) Copyright 2016 Josh Wright
/* for when you want lots and lots of random data for testing,
 * but don't really care about the randomness of that random data.
 * NOT FOR CRYPTOGRAPHIC USES, THIS IS NOT NEARLY RANDOM ENOUGH FOR THAT!!
 */
#include <iostream>
#include <unistd.h> /*isatty, fileno, stdout*/
#include <ctime>
#include <random>
#include <algorithm>

/*valgrind doesn't like the compiiled result of std::random_device*/
//#define VALGRIND_COMPATIBLE 1

const std::size_t buffer_size = 1024 * 10; /*10KB buffer*/

int main(int argc, char* argv[]) {
    /* don't want to write random garbage to a terminal because that hurts the
     * terminal */
    if (isatty(fileno(stdout))) {
        std::cout << "Will not write output to terminal!" << std::endl;
        std::cout << "usage: " << argv[0] << " > [output file]" << std::endl;
        std::cout << "usage: " << argv[0] << " | COMMAND" << std::endl;
        return 1;
    }
    std::mt19937_64 prng;
#ifdef VALGRIND_COMPATIBLE
    prng.seed(time(NULL));
#else
    std::random_device d;
    prng.seed(d());
#endif
    /*make a buffer to store random data*/
    std::mt19937_64::result_type *out = new std::mt19937_64::result_type[buffer_size];
    /*as long as cout is still able to be written to*/
    while (!std::cout.eof()) {
        /*fill the buffer with random data*/
        std::generate(out, out + buffer_size, prng);
        /*write the buffer*/
        std::cout.write((char *) out,
                        sizeof(std::mt19937_64::result_type) * buffer_size);
    }
    return 0;
}
