x = -0.5:0.001:1.5;
y = (x - 2).^5 .* (2 * x + 1).^ 4;
plot(x, y); grid on;

[x, y] = fminbnd('(x - 2).^5 .* (2 * x + 1).^ 4', 0.5, 1.5)