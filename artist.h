#ifndef STAR_H
#define STAR_H

#define NUM_STARS 3

class Artist
{
public:
    Artist();
    void earnMoney();

private:
    float money;

    static float S;
};

extern Artist stars[NUM_STARS];

#endif // STAR_H
