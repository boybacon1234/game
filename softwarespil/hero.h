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

   // ~Hero();

    void init(QVariantList name, QVariantList hp, QVariantList styrke, QVariantList lv, QVariantList xp, QVariantList gold);

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

    void gold(int gold);

private:

        std::string cname;
        int chp;
        int cstyrke;
        int clv;
        int cxp;
        int cgold;
        int cMN;
        QVariantList mName, mHp, mStyrke, mLv, mXp, mGold;
        QSqlQuery mQuery, assignmentQuery, updateQuery, durationQuery;

};


#endif // HERO_H
