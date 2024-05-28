#ifndef GROTTE_H
#define GROTTE_H

#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>


class grotte
{
public:
    grotte();

//    ~grotte();



    void init(QVariantList name, QVariantList gold, QVariantList enemys);

    int get_enemy();

    void get_grotte(int cave);

    void print();

    void set_cave(int cave_id);


    int gold();
    std::vector<int> enemys();






private:

    std::string cname;
    int chp;
    int cgold;
    std::vector<int> cenemys;
    int currentEnemyIndex;


    QSqlQuery mQuery, assignmentQuery, updateQuery, durationQuery;
    QVariantList mName, mGold, mEnemys;





};

#endif // GROTTE_H
