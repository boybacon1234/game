#include "shop.h"

shop::shop()
{
        mQuery.exec("DROP TABLE IF EXISTS shop");
        mQuery.exec("CREATE TABLE shop ("
                    "item_id INT PRIMARY KEY AUTO_INCREMENT,"
                    "name CHAR(125),"
                    "selvstyrke INT,"
                    "styrke INT UNSIGNED,"
                    "magipris INT UNSIGNED,"
                    "element CHAR(125))");
        cname = "";
        chp = 0;
        cstyrke = 0;
        cxp = 0;
        celement="";
}
    //destructor
    shop::~shop(){

        mQuery.exec("DROP TABLE IF EXISTS shop");

    }

