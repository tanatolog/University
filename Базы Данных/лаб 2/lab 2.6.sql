create or replace view price_s_v as
(select 'Максимальное значение цены', price, first_name as instructor_name, second_name as instructor_surname
	from instructor order by price desc limit 1)
union all
(select 'Минимальное значение цены', price, first_name as instructor_name, second_name as instructor_surname
	from instructor order by price limit 1)
union all
(select 'Среднее значение цены', avg(price), null, null from instructor)
union all
(select 'Сумма цен', sum(price), null, null from instructor);
select * from price_s_v;