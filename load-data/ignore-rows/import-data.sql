--
--  "C:\Program Files\MySQL\MySQL Server 8.0\bin\mysql.exe" --local-infile --show-warnings -u rene -prene tq84_db < import-data.sql
--
drop table if exists csv_ignore_rows;

create table csv_ignore_rows (
   col_1   varchar(10),
   col_2   varchar(10),
   col_3   varchar(10)
);


load data local infile 'data.csv'
   into table csv_ignore_rows
   fields terminated by ','
   lines  terminated by '\r\n'
   ignore 1 lines
;

select * from csv_ignore_rows;
