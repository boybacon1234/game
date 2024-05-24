#include "hero.h"
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <thread>

//database med heros
Hero::Hero(){
    mQuery.exec("CREATE TABLE IF NOT EXISTS Heros ("
                "hero_id INT PRIMARY KEY AUTO_INCREMENT,"
                "name CHAR(125),"
                "hp INT,"
                "styrke INT,"
                "lv INT,"
                "xp INT)");

    cname = "";
    chp = 0;
    cstyrke = 0;
    clv = 0;
    cxp = 0;

}


/*
Hero::~Hero() {
    mQuery.exec("DROP TABLE IF EXISTS Heros");
}
*/

//funktion til at sætte basic hero in så hvis amn klikker load uden at lave en hero så er der en i forvvejen
void Hero::init(QVariantList name,QVariantList hp,QVariantList styrke,QVariantList lv,QVariantList xp){


    mQuery.prepare("INSERT INTO Heros (name, hp, styrke, lv, xp) VALUES (:name, :hp, :styrke, :lv, :xp)");
    mName = name;
    mHp = hp;
    mStyrke = styrke;
    mLv = lv;
    mXp = xp;

    if (mName.size() != mHp.size() || mName.size() != mStyrke.size() || mName.size() != mLv.size() || mName.size() != mXp.size()) {
        qDebug() << "Error: Input lists have different sizes";
        return;
    }
    for (int i = 0; i < mName.size(); ++i) {
        mQuery.bindValue(":name", mName.at(i));
        mQuery.bindValue(":hp", mHp.at(i));
        mQuery.bindValue(":styrke", mStyrke.at(i));
        mQuery.bindValue(":lv", mLv.at(i));
        mQuery.bindValue(":xp", mXp.at(i));
        mQuery.exec();
    }
}

//funktioner til at angribe, tjekke hp og tage skade, og til at finde navn på nuværende helt(kunne også bruge id)
int Hero::attack(){

    return cstyrke;
}

int Hero::chekhp(){


    return chp;
}

void Hero::takeDamage(int damage){

    chp-=damage;
}

std::string Hero::name(){
    return cname;
}

// funktion til at finde den nuværendes helt hp fra data basen så det kan resettes når man taber eller vinder
int Hero::getHpForHeroId(std::string Hname) {
    mQuery.prepare("SELECT hp FROM Heros WHERE name = :Hname");
    mQuery.bindValue(":Hname", QString::fromStdString(Hname));

    if (!mQuery.exec()) {
        qDebug() << "Error executing query:" << mQuery.lastError().text();
        return 0;
    }

    if (mQuery.next()) {
        return mQuery.value("hp").toInt();
    } else {
        qDebug() << "No hero found with hero name:" << QString::fromStdString(Hname);
        return 0;
    }

}
// resetter hp
void Hero::sethp(int hp){
    chp=hp;
}



// loader hero
void Hero::load(int hero_pick) {
    mQuery.prepare("SELECT * FROM Heros WHERE hero_id = :hero_pick");
    mQuery.bindValue(":hero_pick", hero_pick);

    if (mQuery.exec()) {
        if (mQuery.next()) {

            std::string name = mQuery.value("name").toString().toStdString();
            int hp = mQuery.value("hp").toInt();
            int styrke = mQuery.value("styrke").toInt();
            int lv = mQuery.value("lv").toInt();
            int xp = mQuery.value("xp").toInt();

            cname = name;
            chp = hp;
            cstyrke = styrke;
            clv = lv;
            cxp = xp;



            std::cout << "Hero Details:" << std::endl;
            std::cout << "Name: " << name << std::endl;
            std::cout << "HP: " << hp << std::endl;
            std::cout << "Styrke: " << styrke << std::endl;
            std::cout << "Level: " << lv << std::endl;
            std::cout << "Experience Points: " << xp << std::endl;
        } else {
            std::cout << "Hero not found with ID: " << hero_pick << std::endl;
        }
    } else {
        std::cout << "Error fetching hero: " << mQuery.lastError().text().toStdString() << std::endl;
    }
}



// fjender en helt. ikke implamenteres endnu
void Hero::deletehero(){
    int hero_id;
    std::cout << "Enter hero id: ";
    if (!(std::cin >> hero_id)) {
        std::cout << "Invalid input for hero id" << std::endl;
        return;
    }

    mQuery.prepare("DELETE FROM Heros WHERE hero_id = :hero_id");
    mQuery.bindValue(":hero_id", hero_id);
    if (!mQuery.exec()) {
        std::cout << "Error deleting Heros: " << mQuery.lastError().text().toStdString() << std::endl;
        return;
    }
    std::cout << "Heros deleted successfully" << std::endl;


}


// viser en helts stats. tager navnet på helten finder den i databasen og printer dem i terminalen
void Hero::showStats(std::string Hname){
    std::cout << "hero stats:" << std::endl;

    mQuery.prepare("SELECT * FROM Heros WHERE name = :Hname");
    mQuery.bindValue(":Hname", QString::fromStdString(Hname));

    if (!mQuery.exec()) {
        qDebug() << "Error executing query:" << mQuery.lastError().text();
        return;
    }


    while (mQuery.next()) {
        QString name = mQuery.value(1).toString();
        int hp = mQuery.value(2).toInt();
        int styrke = mQuery.value(3).toInt();
        int lv = mQuery.value(4).toInt();
        int xp = mQuery.value(5).toInt();

        QString nameString = QString("name: %1").arg(name).leftJustified(40, ' ');
        QString hpString = QString("hp: %1").arg(hp).leftJustified(15, ' ');
        QString styrkeString = QString("styrke: %1").arg(styrke).leftJustified(15, ' ');
        QString lvString = QString("lv: %1").arg(lv).leftJustified(15, ' ');
        QString xpString = QString("xp: %1").arg(xp).leftJustified(15, ' ');

        qDebug()

        << qPrintable(nameString)
        << qPrintable(hpString)
        << qPrintable(styrkeString)
        << qPrintable(lvString)
        << qPrintable(xpString);
    }


}

// printer alle heros når man vælger at loade en helt så man kan se hvem man kan vælge
void Hero::printheroes(){
    std::cout << "All heros:" << std::endl;
    if (!mQuery.exec("SELECT * FROM Heros")) {
        qDebug() << "Error executing query:" << mQuery.lastError().text();
        return;
    }

    while (mQuery.next()) {
        int id = mQuery.value(0).toInt();
        QString name = mQuery.value(1).toString();
        int hp = mQuery.value(2).toInt();
        int styrke = mQuery.value(3).toInt();
        int lv = mQuery.value(4).toInt();
        int xp = mQuery.value(5).toInt();

        QString idString = QString("hero_id: %1").arg(id).leftJustified(15, ' ');
        QString nameString = QString("name: %1").arg(name).leftJustified(40, ' ');
        QString hpString = QString("hp: %1").arg(hp).leftJustified(15, ' ');
        QString styrkeString = QString("styrke: %1").arg(styrke).leftJustified(15, ' ');
        QString lvString = QString("lv: %1").arg(lv).leftJustified(15, ' ');
        QString xpString = QString("xp: %1").arg(xp).leftJustified(15, ' ');

        qDebug() << qPrintable(idString)
                 << qPrintable(nameString)
                 << qPrintable(hpString)
                 << qPrintable(styrkeString)
                 << qPrintable(lvString)
                 << qPrintable(xpString);
    }


}




// laver en helt og sætterruværende sats til defult værrdier og sætetr helt in i databasen
void Hero::create(){
    std::string name;
    unsigned int lv = 1;
    unsigned int xp = 0;
    unsigned int styrke = 2;
    int hp = 10;


    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter hero name: ";
    std::getline(std::cin, name);


    cname=name;
    chp = hp;
    cstyrke = styrke;
    clv = lv;
    cxp = xp;

    mQuery.prepare("INSERT INTO Heros (name, hp, styrke, lv, xp) "
                   "VALUES (:name, :hp, :styrke, :lv, :xp)");
    mQuery.bindValue(":name", QString::fromStdString(name));
    mQuery.bindValue(":hp", hp);
    mQuery.bindValue(":styre", styrke);
    mQuery.bindValue(":lv", lv);
    mQuery.bindValue(":xp", xp);
        if (!mQuery.exec()) {
        std::cout << "Error adding hero: " << mQuery.lastError().text().toStdString() << std::endl;
        return;
    }
    std::cout << "hero added successfully" << std::endl;
}
// tilføjer deen besejjret fjendes xp til hero og hvis xp er over 1000 eller lige med 1000 så får man bedre stats som opdateres
void Hero::gain(int xp) {
    cxp += xp;
    std::cout << "Hero XP: " << cxp << "\n";

    if (cxp >= 1000) {
        chp += 2;
        cstyrke += 1;
        clv += 1;
        cxp = 0;

        updateQuery.prepare("UPDATE Heros SET lv = :clv, hp = :chp, styrke = :cstyrke, xp = :cxp WHERE name = :cname");
        updateQuery.bindValue(":clv", clv);
        updateQuery.bindValue(":chp", chp);
        updateQuery.bindValue(":cstyrke", cstyrke);
        updateQuery.bindValue(":cxp", cxp);
        updateQuery.bindValue(":cname", QString::fromStdString(cname));

        if (updateQuery.exec()) {
            qDebug() << "Update successful for hero:" << QString::fromStdString(cname)<< "\n";
        } else {
            qDebug() << "Update failed:" << updateQuery.lastError().text()<< "\n";
        }
    }
}

