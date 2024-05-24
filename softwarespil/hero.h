#ifndef HERO_H
#define HERO_H

#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>

class Hero
{

public:


    Hero();
    /*
    ~Hero();
*/
    void init(QVariantList name, QVariantList hp, QVariantList styrke, QVariantList lv, QVariantList xp);

    void create();

    int attack();

    void gain(int xp);

    void load(int hero_pick);

    int chekhp();

    void getHero(int heroId);

    void printheroes();

    void takeDamage(int damage);

    std::string name();

    int getHpForHeroId(std::string Hname);

    void deletehero();

    void sethp(int hp);

    void showStats(std::string Hname);

private:

        std::string cname;
        int chp;
        int cstyrke;
        int clv;
        int cxp;
        QVariantList mName, mHp, mStyrke, mLv, mXp;
        QSqlQuery mQuery, assignmentQuery, updateQuery, durationQuery;

};


#endif // HERO_H
