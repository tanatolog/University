function main_script()
    % Основной код
    [X, Y] = meshgrid([-1:1, 1:3]);
    Z = log(1 + X.^2 + Y.^2).^2 + (X - Y - 1).^2;
    plot3(X, Y, Z)

    % Использование fminsearch
    [xmin, minf] = fminsearch(@Fxy, [2; 2]);

    % Вывод результатов
    xmin
    minf

    % Вложенная функция
    function f = Fxy(x)
        x = x(:);  % Преобразование в столбец
        f = log(1 + x(1)^2 + x(2)^2)^2 + (x(1) - x(2) - 1)^2;
    end
end