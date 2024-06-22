select e.first_name, e.second_name, e.middle_name, v.model, v.kind as gear, v.license_plate
from examinee e, vehicle v
where v.id = e.id_vehicle;
