#include "corruptedspectator.h"
#include "artist.h"

QList<CorruptedSpectator*> CorruptedSpectator::spectators;

CorruptedSpectator::CorruptedSpectator(const QList<double> &prices):
    artistIndex(-1)
{
    setPrices(prices);
}

int CorruptedSpectator::vote() const
{

}

void CorruptedSpectator::setPrices(const QList<double> &prices)
{
    prices_ = prices;
}

bool CorruptedSpectator::tribe(Artist *artist, double money)
{
    if (artistIndex>-1)
    {
        int index = artist->index();
        if (prices_.at(index)<=money)
        {
            artistIndex = index;
            return true;
        }
    }
    return false;
}

const QList<CorruptedSpectator *> &CorruptedSpectator::spectatorList()
{
    return spectators;
}
