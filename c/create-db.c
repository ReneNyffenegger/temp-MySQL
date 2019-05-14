#include <stdio.h>
#include "mysql.h"

MYSQL *con = NULL;

void query(const char *stmt) {

  if (mysql_query(con, stmt)) {
    fprintf(stderr, "Error:     %s\nStatement: %s\n", mysql_error(con), stmt);
    mysql_close(con);
    exit(1);
  }

}

void insert_records() {

  MYSQL_STMT *stmt;

  stmt = mysql_stmt_init(con);
  if (!stmt) {
    fprintf(stderr, "Error:     %s\nStatement: %s\n", mysql_error(con), stmt);
    mysql_close(con);
    exit(1);
  }

  const char *insert_stmt = "insert into tq84_tab values (?, ?, ?, ?)";
  if (mysql_stmt_prepare(stmt, insert_stmt, strlen(insert_stmt))) {
    fprintf(stderr, "Error:     %s\nStatement: %s\n", mysql_error(con), stmt);
    mysql_stmt_close(stmt);
    mysql_close(con);
    exit(1);
  }

  printf("Parameter count in insert statement: %d\n",  mysql_stmt_param_count(stmt));

  MYSQL_BIND insert_values[4];

  memset(insert_values, 0, sizeof(insert_values));


  int         num    ; bool int_is_null;
  double      dbl    ; bool dbl_is_null;
  char        txt[20]; bool txt_is_null; long txt_len;
  MYSQL_TIME  dat    ; bool dat_is_null;

   
  insert_values[0].buffer_type = MYSQL_TYPE_LONG    ; insert_values[0].buffer = (char*) &num ; insert_values[0].is_null = &int_is_null;
  insert_values[1].buffer_type = MYSQL_TYPE_DOUBLE  ; insert_values[1].buffer = (char*) &dbl ; insert_values[1].is_null = &dbl_is_null;
  insert_values[2].buffer_type = MYSQL_TYPE_STRING  ; insert_values[2].buffer = (char*)  txt ; insert_values[2].is_null = &txt_is_null; insert_values[2].length = &txt_len; insert_values[2].buffer_length = 20; 
  insert_values[3].buffer_type = MYSQL_TYPE_DATETIME; insert_values[3].buffer = (char*) &dat ; insert_values[3].is_null = &dat_is_null; // buffer_length = sizeof(MYSQL_TIME); // or MYSQL_TYPE_DATE or MYSQL_TYPE_TIME or MYSQL_TYPE_TIMESTAMP ?


  if (mysql_stmt_bind_param(stmt, insert_values)) {
    fprintf(stderr, "Could not bind parameters\n");
    mysql_stmt_close(stmt);
    mysql_close(con);
    exit(1);
  }


  printf("m\n");
  memset(&dat, 0, sizeof(dat));
  printf("n\n");


  int_is_null = false; num =  42;
  dbl_is_null = false; dbl =  9.99;
  txt_is_null = false; strcpy(txt, "1st record"); txt_len = strlen("1st record");
  dat_is_null = false; dat.year = 2019; dat.month = 8; dat.day = 28; dat.hour = 22; dat.minute = 23; dat.second = 24;

  printf("x\n");

  if (mysql_stmt_execute(stmt)) {
    printf("y\n");
    fprintf(stderr, "Could not execute insert statement. %s\n", mysql_error(con));
    mysql_stmt_close(stmt);
    mysql_close(con);
    exit(1);
  }

  printf("Inserted records: %d\n", mysql_stmt_affected_rows(stmt));


  query("insert into tq84_tab values(2, 1.1, 'one', null)");

  mysql_stmt_close(stmt);

}

int main() {

  con = mysql_init(NULL);


  if (!con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
  }

  if (! mysql_real_connect(con,
        "localhost",
        "root"     ,
        "iAmRoot"  ,
         NULL      ,
         0         , // Port number - 0 = default ?
         NULL      ,
         0
  )) {

    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);

  }

  query( "drop database if exists some_db"                                                 );
  query( "create database some_db"                                                         );
  query( "grant all on some_db.* to rene@'%'"                                              );
  query( "use some_db"                                                                     );
  query( "create table tq84_tab (num integer, dbl double,  txt varchar(20), dat datetime)" );


  insert_records();



  query("commit");

  mysql_close(con);
  exit(0);

}
