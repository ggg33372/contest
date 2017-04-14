#ifndef ACTIVESPECTATOR_H
#define ACTIVESPECTATOR_H

#include <artist.h>

#define N 2

class ActiveSpectator
{
public:
    ActiveSpectator();

    bool vote(Artist *s);

    static bool setProbability(float prob[][NUM_STARS]);

protected:
    bool setProbability(float prob[NUM_STARS]);

private:
    float p[NUM_STARS];
};

extern ActiveSpectator spectators[N];

#endif // ACTIVESPECTATOR_H
