#include"hero.h"


Hero::Hero(){
    mQuery.exec("DROP TABLE IF EXISTS Heros");
    mQuery.exec("CREATE TABLE Heros ("
                "hero_id INT PRIMARY KEY AUTO_INCREMENT,"
                "name CHAR(125),"
                "hp INT,"
                "styrke INT UNSIGNED,"
                "lv INT UNSIGNED,"
                "xp INT UNSIGNED");

    cname = "";
    chp = 0;
    cstyrke = 0;
    clv = 0;
    cxp = 0;
}


Hero::~Hero() {
    mQuery.exec("DROP TABLE IF EXISTS Heros");
}



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


int Hero::getHpForHeroId(std::string Hname) {


    // Prepare a SELECT query to retrieve hp for a specific hero_id
    mQuery.prepare("SELECT hp FROM Heros WHERE name = :Hname");
    mQuery.bindValue(":Hname", Hname);

    if (!mQuery.exec()) {
        qDebug() << "Error executing query:" << mQuery.lastError().text();
        return 0; // or suitable error handling
    }

    // Check if there is a result
    if (mQuery.next()) {
        // Extract the value of 'hp' from the result row
        return mQuery.value("hp").toInt();
    } else {
        qDebug() << "No hero found with hero_id:" << heroId;
        return 0; // or suitable error handling
    }

}

void sethp(int hp){

    chp=hp;
}




void Hero::load(int heroId) {
    query.prepare("SELECT * FROM Heros WHERE hero_id = :id");
    query.bindValue(":id", heroId);


    if (query.exec()) {
        if (query.next()) {

            QString name = query.value("name").toString();
            int hp = query.value("hp").toInt();
            int styrke = query.value("styrke").toInt();
            int lv = query.value("lv").toInt();
            int xp = query.value("xp").toInt();

            cname=name;
            chp = hp;
            cstyrke = styrke;
            clv = lv;
            cxp = xp;



            std::cout << "Hero Details:" << std::endl;
            std::cout << "Name: " << name.toStdString() << std::endl;
            std::cout << "HP: " << hp << std::endl;
            std::cout << "Styrke: " << styrke << std::endl;
            std::cout << "Level: " << lv << std::endl;
            std::cout << "Experience Points: " << xp << std::endl;
        } else {
            std::cout << "Hero not found with ID: " << heroId << std::endl;
        }
    } else {
        std::cout << "Error fetching hero: " << query.lastError().text().toStdString() << std::endl;
    }
}




void Hero::deletehero(){
    int hero_id;
    //name
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
                 << qPrintable(hpString);
        << qPrintable(styrkeString)
        << qPrintable(lvString)
        << qPrintable(xpString);
    }


}





void Hero::create() {
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

void Hero::gain(int xp)
{

    cxp += xp;

    if (cxp>=1000)
    {
        cname=name();
        chp += 2;
        cstyrke += 1;
        clv += 1;
        cxp=0;


        updateQuery.prepare("UPDATE heroes SET level = :clv, health = :chp, styrke = :cstyrke, xp = :cxp, lv = :clv, WHERE cname = :name");
        updateQuery.bindValue(":lv", clv);
        updateQuery.bindValue(":hp", chp);
        updateQuery.bindValue(":styrke", clv);
        updateQuery.bindValue(":xp", cxp);


            // Execute the prepared query
            if (updateQuery.exec()) {
                qDebug() << "Update successful for hero_id:" << heroIdToUpdate;
                }
                else {
                    qDebug() << "Update failed:" << updateQuery.lastError().text();
                     }


    }
}
