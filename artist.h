#ifndef STAR_H
#define STAR_H

#include <QList>
#include <QString>

class CorruptedSpectator;
class Artist
{
public:
    Artist(const QString &name, double earnings = 0);
    void earnMoney();
    bool tribe(CorruptedSpectator *spectator);
    bool tribe();
    void setEarnings(double earnings);
    void win();
    bool isWinner() const;
    const QString &name() const;
    int  index();

    static void setProfit(double p);
    static const QList<Artist *> &artistList();
    static void cleanupArtistList();
    static void setWinner(int index);

private:
    const QString name_;
    double money;
    double earnings_;
    double toTribe;

    static double S;
    static QList<Artist*> artists;
    static int winner;
};

#endif // STAR_H
