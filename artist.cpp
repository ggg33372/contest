//#include <math.h>
//#include <stdlib.h>
#include "artist.h"
#include "corruptedspectator.h"

double Artist::S = 0;
int    Artist::winner = -1;

QList<Artist*> Artist::artists;

Artist::Artist(const QString &name, double earnings):
    name_(name), toTribe(0)
{
    setEarnings(earnings);
    artists.append(this);
}

void Artist::earnMoney()
{
    money += earnings_;
    if (isWinner())
        money += S;
    toTribe = money/1000;
}

bool Artist::tribe(CorruptedSpectator *spectator)
{
    if (spectator->tribe(this, toTribe))
    {
        money -= toTribe;
        return true;
    }
    return false;
}

bool Artist::tribe()
{

}

void Artist::setEarnings(double earnings)
{
    earnings_ = earnings;
}

void Artist::win()
{
    setWinner(index());
}

bool Artist::isWinner() const
{
    return (winner >=0 && artists.at(winner)==this);
}

const QString &Artist::name() const
{
    return name_;
}

int Artist::index()
{
    return artists.indexOf(this);
}

void Artist::setProfit(double p)
{
    S = p;
}

const QList<Artist*> &Artist::artistList()
{
    return artists;
}

void Artist::cleanupArtistList()
{
    while (!artists.isEmpty())
        delete artists.takeFirst();
}

void Artist::setWinner(int index)
{
    winner = index;
}
