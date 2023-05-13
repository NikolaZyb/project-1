#include "gra.h"
#include <time.h>

int main()
{
    srand(static_cast<unsigned>(time(0)));
    gra Gra;
    Gra.run();
    return 0;
}
