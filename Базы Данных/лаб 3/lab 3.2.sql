CREATE TYPE t_exam AS (
	id BIGINT,
	mark int2,
	id_team bigint,
	id_inspector bigint
);

CREATE OR REPLACE FUNCTION filter_array_of_exam (
	arr t_exam[],
	filter_var integer
)
RETURNS t_exam[]
AS $$
BEGIN
	RETURN ARRAY( /* Преобразуем выборку в массив */
		SELECT (id, mark, id_team, id_inspector)::t_exam
		FROM unnest(arr)
		WHERE mark >= filter_var
	);
END;
$$ LANGUAGE plpgsql;