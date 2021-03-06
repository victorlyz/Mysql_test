#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    long int   snResult = 0;
    char       chOption[1+1];
    char       chBuff[100];
    char       chSql_insert[100];
    MYSQL      *pMysql = NULL;
    MYSQL_RES  *pRes = NULL;
    MYSQL_ROW  *pRow = NULL;

    memset(chOption, 0x00, sizeof(chOption));
    memset(chBuff, 0x00, sizeof(chBuff));
    memset(chSql_insert, 0x00, sizeof(chSql_insert));

    if(argc < 2) {
        printf("Missing input parameters ! OPTION_TYPE \n \
                1:create 2:select 3:insert 4:update 5:delete \n");
        return 1;
    }

    pMysql = mysql_init(NULL);
    if(NULL ==  pMysql) {
        fprintf(stderr, "mysql_init error !");
        return 1;
    }


    /*连接MYSQL*/
    snResult = Mysql_connect(pMysql);
    if(snResult != 0) {
        printf("Mysql_connect error ! \n");
    }

    /*新增数据表*/
    if('1' == argv[1][0]) {
        snResult = Mysql_create(pMysql);
        if(snResult != 0) {
            printf("Mysql_create error ! \n");
        }
    }

    /*插入数据*/
    if('3' == argv[1][0]) {
        sprintf(chSql_insert,"INSERT INTO %s (%s, %s, %s) \
       VALUES ('%s', '%s', '%s')", argv[2], argv[3], argv[4],argv[5], argv[6], argv[7], argv[8], argv[9]);
        snResult = Mysql_insert(pMysql, chSql_insert);
        if(snResult != 0) {
            printf("Mysql_insert error ! \n");
        }
    }

        return 0;
}

int Mysql_connect(MYSQL *pMysql) {
    MYSQL  *psnResult = NULL;

    char chServer[] = "localhost";
    char chUser[] = "root";
    char chPassword[] = "test123";
    char chDatabase[] = "db_test";

    psnResult = mysql_real_connect(pMysql, chServer, chUser, chPassword, chDatabase, 0, NULL, 0);
    if(pMysql != psnResult) {
        fprintf(stderr, "mysql_real_connect error ! %s\n", mysql_error(pMysql));
        return 1;
    }
    else {
        printf("MySQL Connected!\n");
    }
}
int Mysql_create(MYSQL *pMysql) {
    int    snResult;

    snResult = mysql_query(pMysql, "CREATE TABLE IF NOT EXISTS `history4` ( \
                                   `id` int NOT NULL  AUTO_INCREMENT PRIMARY KEY, \
                                   `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, \
                                   `active` varchar(30) DEFAULT NULL, \
                                   `who`    varchar(8) DEFAULT NULL \
                                    ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    if(snResult != 0) {
        fprintf(stderr, "mysql_query error ! %s\n", mysql_error(pMysql));
        return 1;
    }
    else {
        printf("NEW TABLE CREATE SUCCESS !\n");
    }

    return 0;
}

int Mysql_insert(MYSQL *pMysql, char *chSql_insert) {
    long int snResult = 0;

    snResult = mysql_query(pMysql, chSql_insert);
    if(snResult != 0) {
        fprintf(stderr, "msyql_query error ! %s\n", mysql_error(pMysql));
        return 1;
    }
    else {
        printf("INSERT IS SUCCESS !\n");
    }

    return 0;
}
