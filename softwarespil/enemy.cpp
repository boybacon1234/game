#include "enemy.h"



#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>


//enemy database with viables to the current enemy
Enemy::Enemy(){
    mQuery.exec("DROP TABLE IF EXISTS Enemys");
                mQuery.exec("CREATE TABLE Enemys ("
                "enemy_id INT PRIMARY KEY AUTO_INCREMENT,"
                "name CHAR(125),"
                "hp INT,"
                "styrke INT UNSIGNED,"
                "xp INT UNSIGNED,"
                "element CHAR(125))");
    cname = "";
    chp = 0;
    cstyrke = 0;
    cxp = 0;
    //celement="";
}
//destructor
Enemy::~Enemy(){

   mQuery.exec("DROP TABLE IF EXISTS Enemys");

}
//funktion til at sætte fjender in i databasen
void Enemy::init(QVariantList name, QVariantList hp, QVariantList styrke, QVariantList xp){


   mQuery.prepare("INSERT INTO Enemys (name, hp, styrke, xp) VALUES (:name, :hp, :styrke, :xp)");
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
//setter stats på den valgte fjende fra main code
void Enemy::set_stats(int enemy_int){
   mQuery.prepare("SELECT * FROM Enemys WHERE enemy_id = :enemy_int");
   mQuery.bindValue(":enemy_int", enemy_int);

   if (mQuery.exec()) {
       if (mQuery.next()) {

           std::string name = mQuery.value("name").toString().toStdString();
           int hp = mQuery.value("hp").toInt();
           int styrke = mQuery.value("styrke").toInt();
           int xp = mQuery.value("xp").toInt();

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
           std::cout << "enemy not found with ID: " << enemy_int << std::endl;
       }
   } else {
       std::cout << "Error fetching enemy: " << mQuery.lastError().text().toStdString() << std::endl;
   }


}
//funktioner til at angribe, cheke hp og til at tage damage
int Enemy::attack(){

   return cstyrke;
}


int Enemy::chekhp(){

   return chp;

}

int Enemy::xp(){

   return cxp;

}


void Enemy::takeDamage(int damage){

   chp-=damage;
}

// printer fjende databasen
void Enemy::print(){
   std::cout << "All :" << std::endl;
   if (!mQuery.exec("SELECT * FROM Enemys")) {
       qDebug() << "Error executing query:" << mQuery.lastError().text();
       return;
   }

   while (mQuery.next()) {
       int id = mQuery.value(0).toInt();
       QString name = mQuery.value(1).toString();
       int hp = mQuery.value(2).toInt();
       int styrke = mQuery.value(3).toInt();
       int xp = mQuery.value(4).toInt();

       QString idString = QString("enemy_id: %1").arg(id).leftJustified(15, ' ');
       QString nameString = QString("name: %1").arg(name).leftJustified(15, ' ');
       QString hpString = QString("hp: %1").arg(hp).leftJustified(15, ' ');
       QString styrkeString = QString("styrke: %1").arg(styrke).leftJustified(15, ' ');
       QString xpString = QString("xp: %1").arg(xp).leftJustified(15, ' ');

       qDebug() << qPrintable(idString)
                << qPrintable(nameString)
                << qPrintable(hpString)
                << qPrintable(styrkeString)
                << qPrintable(xpString);
   }


}






