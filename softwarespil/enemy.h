#ifndef ENEMY_H
#define ENEMY_H

#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>

class Enemy{



    public;


    Enemy();
    ~Enemy();

    void init();

    void attack();

    void chekhp();

private:
    std::string cName;
    int cstyrke;
    int chp;
    int cxp;
    QVariantList mName, mHp, mStyrke, mXp;


};


#endif // ENEMY_H
