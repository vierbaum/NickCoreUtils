#include <printf.h>
#include <string.h>
#include "frac.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("\\documentclass{article}\n\\begin{document}\n");

    Frac f1 = genFrac(1, 2);
    Frac f2 = genFrac(18, 3);
    char* s = (char*) malloc(255);

    Frac f3 = f1 * f2;
    register_printf_function('K', print_frac, print_frac_arginfo);
    printf("%K\n", &f3);

    printf("\\end{document}\n");
    return 0;
}