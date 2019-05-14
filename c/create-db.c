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

int main() {

  con = mysql_init(NULL);

  MYSQL_STMT *stmt;

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

  query( "drop database if exists some_db"                                             );
  query( "create database some_db"                                                     );
  query( "grant all on some_db.* to rene@'%'"                                          );
  query( "use some_db"                                                                 );
  query( "create table tq84_tab (num integer, dbl double,  txt varchar(20), dat date)" );

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

  MYSQL_BIND insert_values[4];
  insert_values[0].buffer_type = MYSQL_TYPE_LONG    ; insert_values[0].buffer_length = sizeof(long  ); // or MYSQL_TYPE_LONGLONG
  insert_values[1].buffer_type = MYSQL_TYPE_DOUBLE  ; insert_values[1].buffer_length = sizeof(double);
  insert_values[2].buffer_type = MYSQL_TYPE_STRING  ; insert_values[2].buffer_length = 20; 
  insert_values[3].buffer_type = MYSQL_TYPE_DATETIME; insert_values[3].buffer_length = sizeof(MYSQL_TIME); // or MYSQL_TYPE_DATE or MYSQL_TYPE_TIME or MYSQL_TYPE_TIMESTAMP ?


  if (mysql_stmt_bind_param(stmt, insert_values)) {
    fprintf(stderr, "Could not bind parameters\n");
    mysql_stmt_close(stmt);
    mysql_close(con);
    exit(1);

  }

  int         num; bool int_is_null;
  double      dbl; bool dbl_is_null;
  char       *txt; bool txt_is_null;
  MYSQL_TIME  dat; bool dat_is_null;



//   insert_values[0].buffer = (char*) 42   ; insert_values[0].is_null = 0;
//   insert_values[1].buffer = (char*) &d   ; insert_values[1].is_null = 0;
// //insert_values[1].buffer = (char*) &d   ; insert_values[1].is_null = 0;
                                              insert_values[0].is_null = &int_is_null;
                                              insert_values[1].is_null = &dbl_is_null;
                                              insert_values[2].is_null = &txt_is_null;
                                              insert_values[3].is_null = &dat_is_null;

  int_is_null = true;
  dbl_is_null = true;
  txt_is_null = true;
  dat_is_null = true;

  mysql_stmt_execute(stmt);


  mysql_stmt_close(stmt);

  mysql_close(con);
  exit(0);

}
