--
--  "C:\Program Files\MySQL\MySQL Server 8.0\bin\mysql.exe" --local-infile -u rene -prene tq84_db < import-data.sql
--
drop table if exists csv_set;

create table csv_set (
   col_1   varchar(10),
   col_2   integer
);


load data local infile 'data.csv'
   into table csv_set
   fields terminated by ','  enclosed  by '"'
-- lines  terminated by '\r\n'
  (col_1, @col_2 )
set
  col_2 = power(@col_2 / 100, 2)
;

select * from csv_set;
