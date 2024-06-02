#include <iostream>
#include "hero.h"
#include "enemy.h"
#include "grotte.h"
#include <QSqlDatabase>
using namespace std;
//shop.h shop.cpp magic.h magic.cpp

void waitForEnter() {
    std::cout << "Press Enter to fight\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("game"); // Change database name
    db.setUserName("root");             // Change username
    db.setPassword("Zhy52vsb#");         // Change password
    db.open();
    if (!db.isOpen()) {
        std::cerr << "Error: Unable to open database\n";
        return 1;
    }

    QSqlQuery query;
    query.exec("SET autocommit=1;");
    //kør første gang for at lave en basic hero
    /*
    QVariantList name, hp, styrke, lv, xp;
    name << "fin" ;
    hp << 10;
    styrke << 2 ;
    lv << 1;
    xp << 0;
    */


    //opretter hero database/hero og /enemy
    Hero myHero;
    //myHero.init(name, hp, styrke, lv, xp);
    Enemy myEnemy;

    //insætter enemys
    QVariantList ename, ehp, estyrke, exp;
    ename << "horse" << "monkey" << "troll" << "cake" << "dragon";
    ehp << 3 << 5 << 7 << 10 << 20;
    estyrke << 1 << 2 << 3 << 5 << 8;
    exp << 900 << 200 << 500 << 1000 << 2000;
    myEnemy.init(ename, ehp, estyrke, exp);




    grotte mygrotte;
    QVariantList gname, ggold, genemys;

    gname << "easy" << "medium" << "hard";
    ggold << 10 << 20 << 40;

    // Define enemy lists for each cave
    QStringList easyEnemies, mediumEnemies, hardEnemies;
    easyEnemies << "1" << "1" << "1";  // Example enemy IDs for the easy cave
    mediumEnemies << "2" << "3" << "3";  // Example enemy IDs for the medium cave
    hardEnemies << "4" << "4" << "4";  // Example enemy IDs for the hard cave

    // Convert QStringLists to comma-separated strings
    QString easyEnemiesStr = easyEnemies.join(",");
    QString mediumEnemiesStr = mediumEnemies.join(",");
    QString hardEnemiesStr = hardEnemies.join(",");

    // Add the enemy strings to genemys
    genemys << easyEnemiesStr << mediumEnemiesStr << hardEnemiesStr;

    // Initialize the grotte object
    mygrotte.init(gname, ggold, genemys);

    //variabler til spillet
    int choice,hero_pick,enemy,cave, item;
    bool skip_menu = false;
    mygrotte.print();

    //game menu som kun køre første gang man starter op
    do {
        if (!skip_menu)
        {
            std::cout << "\nMenu:\n";
            std::cout << "1. create hero\n";
            std::cout << "2. load hero\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cout << std::endl;
       }

        switch (choice) {
        case 1:  //laver helt og viser stats, skipper hoved menuen og hopper til case 8
            myHero.create();
            myHero.showStats(myHero.name());
            choice =8;
            skip_menu = true;
            break;



        case 2: // printer alle heros med stats så man kan vælge ud fra id, skipper hoved menuen og hopper til case 8
            myHero.printheroes();
            std::cout << "\nPick your hero. select hero_id\n";
            std::cin >> hero_pick;
            myHero.load(hero_pick);
            choice =8;
            skip_menu = true;
            break;


        case 3: //loop hvor hero og valgte enemy kæmper indtil en er besejret ( når kampen er slut så skal der trykkes enter en gang til // skal fikses i senere iteration)
            while (myHero.chekhp() > 0 && myEnemy.chekhp() > 0) {
                std::cout << "Hero HP: " << myHero.chekhp() << "\n";
                std::cout << "Enemy HP: " << myEnemy.chekhp() << "\n";
                waitForEnter();

                myEnemy.takeDamage(myHero.attack());

                if (myEnemy.chekhp() > 0) { // Enemy attacks only if still alive
                    myHero.takeDamage(myEnemy.attack());
                }
            }
            //chek om em af dem er besejret og hvis hero vandt giv om enemys xp
            if (myHero.chekhp() <= 0) {
                std::cout << "You were defeated by the enemy!\n";
                myHero.sethp(myHero.getHpForHeroId(myHero.name()));
            } else if (myEnemy.chekhp() <= 0) {
                std::cout << "Congratulations! You defeated the enemy!\n";
                myHero.sethp(myHero.getHpForHeroId(myHero.name()));
                myHero.gain(myEnemy.xp());
                myHero.showStats(myHero.name()); // skal evt smides sammen med gain så stats ikke printes hver gang

            }

            choice = 8;
            break;


        case 4: // grotte
            std::cout << "\n pick cave\n";
            mygrotte.print();
            std::cin >> cave;
            std::cout << "\n entering cave\n";
            mygrotte.get_grotte(cave);

            std::cout << "Enemies: ";
            for (int enemy : mygrotte.enemys()) {
                std::cout << enemy << " ";
            }
            std::cout << std::endl;


            while ((enemy = mygrotte.get_enemy()) != -1) {
                    myEnemy.set_stats(enemy);
                    while (myHero.chekhp() > 0 && myEnemy.chekhp() > 0) {
                        std::cout << "Hero HP: " << myHero.chekhp() << "\n";
                        std::cout << "Enemy HP: " << myEnemy.chekhp() << "\n";
                        waitForEnter();
                        myEnemy.takeDamage(myHero.attack());

                        if (myEnemy.chekhp() > 0) { // Enemy attacks only if still alive
                            myHero.takeDamage(myEnemy.attack());
                        }
                    }
                    // Check if the hero or enemy won the battle
                    if (myHero.chekhp() <= 0) {
                        std::cout << "You were defeated by the enemy!\n";
                        myHero.sethp(myHero.getHpForHeroId(myHero.name()));
                        break;
                    } else if (myEnemy.chekhp() <= 0) {
                        std::cout << "Congratulations! You defeated the enemy!\n";
                        myHero.sethp(myHero.getHpForHeroId(myHero.name()));
                        myHero.gain(myEnemy.xp());
                        myHero.showStats(myHero.name()); // Print hero stats
                    }
                }
                if (enemy == -1) {
                    myHero.gold(mygrotte.gold()); // Award gold if cave is complete
                    myHero.showStats(myHero.name());

                }



            choice = 8; // Set choice for returning to the main menu
            break;
/*
        case 5:
            std::cout << "\n welcome to the shop of magic\n";
            std::cout << "\n what would you like\n";
            shop.print();
            std::cin >> item;
            if (shop.pick(item,hero.gold(),hero.magic())){
                    std::cout << "\n enjoy your magic\n";
                    hero.get_magic(item);
                    hero.giv_gold(shop.cost(item));
            }
            else{
                    std::cout << "\n you cannot buy this magic\n";
            }
            break;
*/

        case 8: // vælger fjende eller om man vil stoppe eller om man vil til en grotte
            std::cout << "\nPick Enemy:\n";
            myEnemy.print();
            std::cout << "\nOr cave: 10\n";
           // std::cout << "\nOr shop: 11\n";
            std::cout << "\n or exit 0:\n";
            std::cin >> enemy;

            std::cout << std::endl;

            if (enemy> 0 && enemy<= 5) {
                myEnemy.set_stats(enemy);
                choice = 3;
            } else if (enemy == 0) {
                choice = 0;
            }
            else if (enemy == 10) {
                choice = 4;
            }
            else {
                std::cout << "invalid choic\n";
                choice = 8;
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

