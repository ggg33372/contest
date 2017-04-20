#ifndef ACTIVESPECTATOR_H
#define ACTIVESPECTATOR_H

#include <QList>
#include "spectator.h"

class ActiveSpectator: Spectator
{
public:
    ActiveSpectator(const QList<double> &prob = QList<double>());
    bool setProbabilities(const QList<double> &prob);
    const QList<double> &probabilies() const;
    static const QList<ActiveSpectator*> &spectatorList();

    // Spectator interface
    int vote() const;

private:
    QList<double> prob_;
    static QList<ActiveSpectator*> spectators;
};

#endif // ACTIVESPECTATOR_H
