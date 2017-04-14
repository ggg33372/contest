#include <QDebug>
#include "activespectator.h"

ActiveSpectator spectators[N];

ActiveSpectator::ActiveSpectator()
{

}

bool ActiveSpectator::vote(Artist *s)
{

}

bool ActiveSpectator::setProbability(float prob[])
{
    float sum(0);

    for (int j=0; j<NUM_STARS; ++j)
    {
        qDebug() << "prob[" << j << "]=" << prob[j];
        sum += p[j] = prob[j];
    }
    qDebug() << "sum=" << sum;

    if (1-sum)
        return false;
}

bool ActiveSpectator::setProbability(float prob[][NUM_STARS])
{
    for (int i=0; i<N; ++i)
    {
        qDebug() << "i=" << i;
        if (!spectators[i].setProbability(prob[i]))
            return false;
    }
    return true;
}
