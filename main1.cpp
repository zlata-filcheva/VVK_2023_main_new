#include <iostream>
#include "StudentuRusiavimas.h"

int main() {
    clock_t start;
    double duration;

    start = clock();

    StudentuRusiavimas studentas;

    studentas.fillFileWithRandomData();

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"Time elapsed (in seconds): "<< duration <<'\n';

    return 0;
}