#include <QDebug>
#include "activespectator.h"

QList<ActiveSpectator*> ActiveSpectator::spectators;

ActiveSpectator::ActiveSpectator(const QList<double> &prob)
{
    if (!prob.isEmpty())
        setProbabilities(prob);
    spectators.append(this);
}

const QList<ActiveSpectator *> &ActiveSpectator::spectatorList()
{
    return spectators;
}

int ActiveSpectator::vote() const
{
    double sum;
    double roll = ((double)qrand())/RAND_MAX;
    int index = 0;

    for (QList<double>::ConstIterator it=prob_.constBegin(); it!=prob_.constEnd(); ++it, ++index)
    {
        sum += *it;
        if (roll<sum)
            return index;
    }

    Q_ASSERT(false);

    return -1;
}

bool ActiveSpectator::setProbabilities(const QList<double> &prob)
{
    double sum(0);

    for (QList<double>::ConstIterator it=prob.constBegin(); it!=prob.constEnd(); ++it)
        sum += *it;

    qDebug() << "sum=" << sum;

    if (1-sum)
        return false;

    prob_ = prob;
    return true;
}

const QList<double> &ActiveSpectator::probabilies() const
{
    return prob_;
}
