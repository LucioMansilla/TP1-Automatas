#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("## IMPORTANnnnnT:\n");
    printf("* Executables are generated in the tests/exec directory.\n");
    printf("* Files \"AFND_TP.dot\", \"AFND_TP2.dot\", and \"AFND.dot\" are used for various tests.\n");
    printf("* Files \"AFD_TP.dot\", \"kleene.dot\", \"union.dot\", \"concatenate.dot\", ");
    printf("\"minimize.dot\", and \"write_afnd.dot\" are generated after running run.sh.\n");
    printf("You can find both input and output files in the C/tests directory.\n");
    printf("* run.sh will report the test status.\n");
    printf("* A log file will be generated after running run.sh in the C/tests/exec directory. ");
    printf("It will contain additional information about the tests, (printouts of automata, lists, etc.).\n");

    return 0;
}