do language plpgsql $$
declare
	id_vehicle bigint;
	id_instructor bigint;
	id_examinee bigint;
	id_team bigint;
	id_inspector bigint;
begin
	insert into vehicle(model, license_plate, kind)
	values('Lada', 'н284пп', 'manual car')
	returning id into id_vehicle;

	insert into examinee(first_name, second_name, middle_name, id_vehicle)
	values('Алексей', 'Кубарев', 'Григорьевич', id_vehicle)
	returning id into id_examinee;

	insert into instructor(first_name, second_name, middle_name, price)
	values('Николай', 'Скочинский', 'Дмитриевич', 9999)
	returning id into id_instructor;

	insert into team(id_instructor, id_examinee)
	values(id_instructor, id_examinee)
	returning id into id_team;

	insert into inspector(first_name, second_name, middle_name)
	values('Петр', 'Павлов', 'Павлович')
	returning id into id_inspector;

	insert into exam(mark, id_team, id_inspector)
	values(0, id_team, id_inspector);

end;
$$





