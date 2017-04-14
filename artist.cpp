#include <math.h>
#include <stdlib.h>
#include "artist.h"

float Artist::S = 800;

Artist stars[NUM_STARS];

Artist::Artist()
{

}

void Artist::earnMoney()
{
    money += rand()*1000/RAND_MAX+500+S;
}
