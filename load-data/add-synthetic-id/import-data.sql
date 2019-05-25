--
--  "C:\Program Files\MySQL\MySQL Server 8.0\bin\mysql.exe" --local-infile --show-warnings -u rene -prene tq84_db < import-data.sql
--
drop table if exists csv_without_id;

create table csv_without_id (
   id      integer        primary key,
   col_1   varchar(10),
   col_2   varchar(10)
);


--
--   Use a variable to add an synthetic id.
--
set @id := 0;

load data local infile 'data.csv'
   into table csv_without_id
   fields terminated by ','
   lines  terminated by '\r\n'
   ignore 1 lines
(
  col_1,
  col_2
)
set
  id = @id := @id + 1
;

select * from csv_without_id;
