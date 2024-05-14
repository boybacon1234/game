#include <iostream>
#include "hero.h"
#include "enemy.h"
using namespace std;

void waitForEnter() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker"); // Change database name
    db.setUserName("root");             // Change username
    db.setPassword("password");         // Change password
    db.open();
    if (!db.isOpen()) {
        std::cerr << "Error: Unable to open database\n";
        return 1;
    }
    //chek hero
    QVariantList name, hp, styrke, lv, xp;
    name << "fin" ;
    hp << 10;
    styrke << 2 ;
    lv << 1;
    xp << 0;

    Hero myHero;
    myHero.innit(name, hp, styrke, lv, xp);
    Enemy myEnemy;


    QVariantList name, hp, styrke, xp;
    name << "horse" << "monkey" << "troll" << "cake" << "dragon";
    hp << 3 << 5 << 7 << 10 << 20;
    styrke << 1 << 2 << 3 << 5 << 8;
    xp << 100 << 200 << 500 << 1000 << 2000 ;
    //chek enemy
    myEnemy.innit(name, hp, styrke, xp);

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. create here\n";
        std::cout << "2. load hero\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
        case 1:
            myHero.create();
            choice =8;
            break;
        case 2:
            myHero.printheroes();
            std::cout << "Pick your hero\n";
            std::cin >> hero_pick;
            myHero.load(hero_pick);
            choice =8;
            break;
        case 3: // make this part work
            while (myHero.chekhp() >0 || myEnemy.chekhp()>0) {
                waitForEnter();

                myEnemy.takeDamage(myHero.attack());
                if (myHero.chekhp() >0) {
                    myHero.takeDamage(myEnemy.attack());
                }
            }

            if (myHero.chekhp()<=0 ) {
                std::cout << "You were defeated by the enemy!\n";

                myHero.sethp(myHero.getHpForHeroId(myHero.name()));

            } else {
                std::cout << "Congratulations! You defeated the enemy!\n";
                myHero.gain();
                myHero.showStats();

                choice = 8;
            }
            break;
        case 8:
            std::cout << "\nPick Enemy:\n";
            std::cout << "0. Horse´\n";
            std::cout << "1. Monkey\n";
            std::cout << "2. Troll\n";
            std::cout << "3. Cake\n";
            std::cout << "4. Dragon\n";
            std::cout << "5. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> enemy;

            std::cout << std::endl;

            if (enemy >= 0 && enemy <= 4) {
                set_stats(enemy);  // Assuming set_stats function sets enemy stats based on choice
                choice = 3;         // Choice to proceed with battle
            } else if (enemy == 5) {
                choice = 0;         // Player chooses to exit
            } else {
                std::cout << "invalid choice exiting game\n";
                choice = 0;


            }
            break;


        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);




    return 0;
}
