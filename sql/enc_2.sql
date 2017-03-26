pragma key== "x'31323334353637383132333435363738'";
create table people (name text primary key);
insert into people (name) values ('charlie'), ('huey');
select * from people;
.quit
