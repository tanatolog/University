select e.first_name as examinee_name, e.second_name as examinee_second_name, 
	i.first_name as instructor_name, i.second_name as instructor_second_name, i.price
from examinee e join team t on e.id = t.id_examinee join instructor i on i.id = t.id_instructor;

