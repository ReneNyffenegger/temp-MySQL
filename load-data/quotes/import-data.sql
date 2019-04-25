--
--   What to do if even numbers are quoted and can be null?
--
--  "C:\Program Files\MySQL\MySQL Server 8.0\bin\mysql.exe" --local-infile --show-warnings -u rene -prene tq84_db < import-data.sql
--

drop table if exists csv_quotes;

create table csv_quotes (
   col_1   varchar(10) not null,
   col_2   integer         null
);


load data local infile 'data.csv'
   into table csv_quotes
   fields terminated by ',' enclosed  by '"'
   lines  terminated by '\r\n'
    (col_1, @col_2 )
   set
     col_2 = case when @col_2 = '' then null else @col_2 end
 --  col_2 = cast(@col_2 as integer)
;

select * from csv_quotes;
