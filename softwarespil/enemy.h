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



public:


    Enemy();
    ~Enemy();

    void init(QVariantList name, QVariantList hp, QVariantList styrke, QVariantList xp);
    void set_stats(int enemy_int);

    int attack();

    int chekhp();

    void takeDamage(int damage);

    void setH();

    int xp();
    void print();



private:
    std::string cname;
    int cstyrke;
    int chp;
    int cxp;
    QVariantList mName, mHp, mStyrke, mXp;
    QSqlQuery mQuery, assignmentQuery, updateQuery, durationQuery;



};


#endif // ENEMY_H
