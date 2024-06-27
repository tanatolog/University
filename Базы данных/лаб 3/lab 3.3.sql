/*CREATE TABLE log_examinee (
	id BIGSERIAL PRIMARY KEY,
	examinee_id BIGINT DEFAULT NULL,
	change_datetime TIMESTAMP DEFAULT NOW(),
	old_value bigint DEFAULT NULL,
	new_value bigint DEFAULT NULL
);*/

CREATE OR REPLACE FUNCTION trigger_func()
RETURNS TRIGGER
AS $$
DECLARE
	old_val bigint;
BEGIN
	IF (TG_OP = 'UPDATE') THEN /* Определяем "старое" значение */
		old_val := OLD.id_vehicle;
	ELSIF (TG_OP = 'INSERT') THEN
		old_val := NULL;
	end if;
	INSERT INTO log_examinee
		(examinee_id, old_value, new_value)  
	VALUES
		(NEW.id, old_val, NEW.id_vehicle);
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER commit_examinee_change
AFTER UPDATE OR INSERT
ON examinee
FOR EACH ROW
EXECUTE PROCEDURE trigger_func();
