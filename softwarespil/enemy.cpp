#include "enemy.h"



#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>


Enemy::Enemy(){
                mQuery.exec("DROP TABLE IF EXISTS Enemys")
                mQuery.exec("CREATE TABLE Enemys ("
                "enemy_id INT PRIMARY KEY AUTO_INCREMENT,"
                "name CHAR(125),"
                "hp INT,"
                "styrke INT UNSIGNED,"
                "xp INT UNSIGNED");
    cname = "";
    chp = 0;
    cstyrke = 0;
    cxp = 0;
}

Enemy::~Enemy(){

   mQuery.exec("DROP TABLE IF EXISTS Enemys");

}

void Enemy::init(QVariantList name, QVariantList hp, QVariantList styrke, QVariantList xp){


   mQuery.prepare("INSERT INTO Enemys (name, hp, styrke, xp) VALUES (:name, :hp, :styrke, :lv, :xp)");
   mName = name;
   mHp = hp;
   mStyrke = styrke;
   mXp = xp;

   if (mName.size() != mHp.size() || mName.size() != mStyrke.size() || mName.size() != mXp.size()) {
       qDebug() << "Error: Input lists have different sizes";
       return;
   }
   for (int i = 0; i < mName.size(); ++i) {
       mQuery.bindValue(":name", mName.at(i));
       mQuery.bindValue(":hp", mHp.at(i));
       mQuery.bindValue(":styrke", mStyrke.at(i));
       mQuery.bindValue(":xp", mXp.at(i));
       mQuery.exec();
   }
}

void Enemy::set_stats(int enemy_int){
   query.prepare("SELECT * FROM Enemys WHERE enemy_id = :enemy_int");
   query.bindValue(":enemy_int", enemy_int);
^

   if (query.exec()) {
       if (query.next()) {

           QString name = query.value("name").toString();
           int hp = query.value("hp").toInt();
           int styrke = query.value("styrke").toInt();
           int xp = query.value("xp").toInt();

           cname=name;
           chp = hp;
           cstyrke = styrke;
           cxp = xp;


/*
           std::cout << "Hero Details:" << std::endl;
           std::cout << "Name: " << name.toStdString() << std::endl;
           std::cout << "HP: " << hp << std::endl;
           std::cout << "Styrke: " << styrke << std::endl;
           std::cout << "Level: " << lv << std::endl;
           std::cout << "Experience Points: " << xp << std::endl;
*/
       } else {
           std::cout << "enemy not found with ID: " << heroId << std::endl;
       }
   } else {
       std::cout << "Error fetching enemy: " << query.lastError().text().toStdString() << std::endl;
   }


}

int Enemy::attack(){

   return cstyrke;
}


int Enemy::chekhp(){

   return chp;

}

void Enemy::takeDamage(int damage){

   chp-=damage;
}

void Enemy::setA(){

   cstyrke = 0;
}


int Enemy::setH(){

    chp = 10;

}





