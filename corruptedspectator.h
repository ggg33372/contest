#ifndef CORRUPTEDSPECTATOR_H
#define CORRUPTEDSPECTATOR_H

#include <QList>
#include "spectator.h"

class Artist;
class CorruptedSpectator: Spectator
{
public:
    CorruptedSpectator(const QList<double> &prices = QList<double>());
    void setPrices(const QList<double> &prices);
    bool tribe(Artist *artist, double money);
    static const QList<CorruptedSpectator*> &spectatorList();

    // Spectator interface
    int vote() const;

private:
    int artistIndex;
    QList<double> prices_;
    static QList<CorruptedSpectator*> spectators;
};

#endif // CORRUPTEDSPECTATOR_H
