INCDIR="C:\Program Files\MySQL\MySQL Server 8.0\include"

create-db: create-db.o
	gcc $< "C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.lib" -o $@ 

create-db.o: create-db.c
	gcc -I$(INCDIR) -c $< -o $@

