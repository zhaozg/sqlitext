pragma key='12345678';
create table people (name text primary key);
insert into people (name) values ('charlie'), ('huey');
select * from people;
.quit
