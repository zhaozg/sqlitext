create table seq (id integer primary key AUTOINCREMENT, name varchar(64));
insert into seq (name) values ('charlie'), ('huey');
select * from seq;
select load_extension('sqlite.sequence.dll');
select curval('seq');
select nextval('seq');
select curval('seq');

.quit
