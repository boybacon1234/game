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

    public;


    Hero();
    ~Hero();

    void attack();

    void gain();

    void load(std::string Hname);

    int chekhp();

    void getHero(int heroId);


private:

        std::string cname;
        int chp;
        int cstyrke;
        int clv;
        int cxp;
        QVariantList mName, mHp, mStyrke, mLv, mXp;

};


#endif // HERO_H
