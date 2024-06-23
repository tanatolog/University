--create database lab;					-- Создать БД lab 

--create user db_user password 'db_user';

--create type vehicle_type as enum (
--	'automatic car', 'manual car'
--);

create table public.vehicle(			--Создание таблицы Транспортное средство
	id bigserial primary key,
	model varchar(30),
	license_plate varchar(30),
	kind vehicle_type not null default 'automatic car'
);

create table public.examinee(			--Создание таблицы Экзаменуемый
	id bigserial primary key,
	first_name varchar(30) not null,
	second_name varchar(30) not null,
	middle_name varchar(30),
	id_vehicle bigint not null references public.vehicle(id)
);

create table public.instructor(		--Создание таблицы Инструктор
	id bigserial primary key,
	first_name varchar(30) not null,
	second_name varchar(30) not null,
	middle_name varchar(30),
	price int not null check(price >= 500 and price <= 10000)
);

create table public.team(				--Создание таблицы Группа
	id bigserial primary key,
	id_instructor bigint not null references public.instructor(id),
	id_examinee bigint not null references public.examinee(id)
);

create table public.inspector(		--Создание таблицы Инспектор
	id bigserial primary key,
	first_name varchar(30) not null,
	second_name varchar(30) not null,
	middle_name varchar(30)
);

create table public.exam(				--Создание таблицы экзамен
	id bigserial primary key,
	mark int2 check(mark >= 0 and mark <= 5),
	id_team bigint not null references public.team(id),
	id_inspector bigint not null references public.inspector(id)
);

--grant all on schema public to db_user;	--Выдача прав на созданные объекты пользователю user















