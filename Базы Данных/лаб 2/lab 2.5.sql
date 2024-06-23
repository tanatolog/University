create or replace view exam_full_v as
select e.first_name as examinee_name, e.second_name as examinee_second_name, 
	i.first_name as instructor_name, i.second_name as instructor_second_name,
	p.first_name as inspector_name, p.second_name as inspector_second_name, 
	v.kind as type, m.mark
from examinee e, instructor i, inspector p, vehicle v, exam m, team t
where m.id_team = t.id and t.id_examinee = e.id and t.id_instructor = i.id and m.id_inspector = p.id
and e.id_vehicle = v.id;
select * from exam_full_v;
