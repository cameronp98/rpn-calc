#include "rpn.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    rpn_init();

    if (argc < 2)
        printf("Usage: %s <expression>\n", argv[0]);
    else
        rpn_showResults(rpn_eval(argv[1]));

    return 0;
}
