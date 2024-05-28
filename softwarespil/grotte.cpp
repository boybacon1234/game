#include "grotte.h"



//destructor
/*
grotte::~grotte(){

    mQuery.exec("DROP TABLE IF EXISTS Enemys");

}
*/

grotte::grotte() {
    mQuery.exec("DROP TABLE IF EXISTS cave");
    mQuery.exec("CREATE TABLE cave ("
                "cave_id INT PRIMARY KEY AUTO_INCREMENT,"
                "name CHAR(125),"
                "gold INT,"
                "enemy VARCHAR(255))");  // Change enemy to VARCHAR to store comma-separated IDs
    cname = "";
    cgold = 0;
    cenemys = std::vector<int>();
    currentEnemyIndex=0;
}

void grotte::init(QVariantList name, QVariantList gold, QVariantList enemys) {
    mQuery.prepare("INSERT INTO cave (name, gold, enemy) VALUES (:name, :gold, :enemys)");
    mName = name;
    mGold = gold;
    mEnemys = enemys;

    if (mName.size() != mGold.size() || mName.size() != mEnemys.size()) {
        qDebug() << "Error: Input lists have different sizes";
        return;
    }

    for (int i = 0; i < mName.size(); ++i) {
        mQuery.bindValue(":name", mName.at(i));
        mQuery.bindValue(":gold", mGold.at(i));
        mQuery.bindValue(":enemys", mEnemys.at(i).toString());  // Convert to string if necessary
        mQuery.exec();
    }
}

int grotte::get_enemy(){
// Check if there are enemies left in the cave
if (currentEnemyIndex < cenemys.size()) {
int nextEnemy = cenemys[currentEnemyIndex]; // Get the next enemy ID
currentEnemyIndex++; // Move to the next enemy for next call
return nextEnemy;
} else {
    currentEnemyIndex =0;
    return -1; // Indicates no more enemies left in the cave
}
};




void grotte::get_grotte(int cave) {
mQuery.prepare("SELECT * FROM cave WHERE cave_id = :cave");
mQuery.bindValue(":cave", cave);

if (mQuery.exec()) {
    if (mQuery.next()) {
        std::string name = mQuery.value("name").toString().toStdString();
        int gold = mQuery.value("gold").toInt();
        QString enemyStr = mQuery.value("enemy").toString();

        // Split the QString into a list of strings
        QStringList enemyList = enemyStr.split(",");

        // Clear the existing vector
        cenemys.clear();

        // Convert the list of strings to a vector of integers
        for (const QString& enemy : enemyList) {
            cenemys.push_back(enemy.toInt());
        }

        cname = name;
        cgold = gold;
    } else {
        std::cout << "Cave not found with ID: " << cave << std::endl;
    }
} else {
    std::cout << "Error fetching cave: " << mQuery.lastError().text().toStdString() << std::endl;
}
}



void grotte::print(){
std::cout << "All caves:" << std::endl;
if (!mQuery.exec("SELECT cave_id, name, gold, enemy FROM cave")) {
    qDebug() << "Error executing query:" << mQuery.lastError().text();
    return;
}

while (mQuery.next()) {
    int id = mQuery.value(0).toInt();
    QString name = mQuery.value(1).toString();
    int gold = mQuery.value(2).toInt();
    QString enemyListStr = mQuery.value(3).toString();

    QStringList enemyIds = enemyListStr.split(",");
    QStringList enemies;
    for (const QString& enemyId : enemyIds) {
        // You may want to fetch enemy names from another table based on their IDs
        enemies.append("Enemy ID: " + enemyId);
    }
    QString enemyString = enemies.join(", ");

    QString idString = QString("cave_id: %1").arg(id).leftJustified(15, ' ');
    QString nameString = QString("name: %1").arg(name).leftJustified(15, ' ');
    QString goldString = QString("gold: %1").arg(gold).leftJustified(15, ' ');

    qDebug() << qPrintable(idString)
             << qPrintable(nameString)
             << qPrintable(goldString)
             << qPrintable(enemyString);
}
}


void grotte::set_cave(int cave_id){
    mQuery.prepare("SELECT * FROM cave WHERE cave_id = :cave_id");
    mQuery.bindValue(":cave_id", cave_id);

    if (mQuery.exec()) {
        if (mQuery.next()) {

            std::string name = mQuery.value("name").toString().toStdString();
            int gold = mQuery.value("gold").toInt();
            QVariantList enemyList = mQuery.value("enemy").toList();

            cenemys.clear(); // Clear previous enemies
            for (int i = 0; i < enemyList.size(); ++i) {
            cenemys.push_back(enemyList[i].toInt());
            }

            cname = name;
            cgold = gold;
        } else {
            std::cout << "Cave not found with ID: " << cave_id << std::endl;
        }
    } else {
        std::cout << "Error fetching cave: " << mQuery.lastError().text().toStdString() << std::endl;
    }
}



int grotte::gold(){
    return cgold;
}

std::vector<int> grotte::enemys(){
    return cenemys;
}
