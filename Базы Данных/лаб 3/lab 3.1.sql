CREATE OR REPLACE FUNCTION save_vehicle (
	_id BIGINT, 
	_model VARCHAR(30), 
	_license_plate VARCHAR(30),
	_kind vehicle_type
)
RETURNS BIGINT
AS $$
DECLARE
	used_id BIGINT;
BEGIN
	IF _id IS NULL THEN
		INSERT INTO vehicle (model, license_plate, kind)
		VALUES (_model, _license_plate, _kind)
		RETURNING id /* Вернуть id нового элемента */
		INTO used_id; /* В переменную used_id */
	ELSE
		UPDATE vehicle SET
		model = _model,
		license_plate = _license_plate,
		kind = _kind
		WHERE id = _id;
		used_id := _id; /* Присвоим известный  id */
	END IF;
	RETURN used_id;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION delete_vehicle (
	_id BIGINT
)
RETURNS VOID
AS $$
BEGIN
	DELETE FROM vehicle WHERE id = _id; /* Просто пытаемся удалить строку */
	EXCEPTION
	WHEN foreign_key_violation THEN /* Перехват нужного нам исключения */
	RAISE EXCEPTION 'Невозможно выполнить удаление, так как есть внешние ссылки.';
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION filter_instructor_by_price (
	min_price BIGINT
)
RETURNS SETOF instructor
AS $$
BEGIN
	RETURN QUERY (SELECT * FROM instructor WHERE price >= min_price);
END;
$$ LANGUAGE plpgsql;
