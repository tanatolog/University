unit LevyCurve;

interface
Uses Graph;
procedure levy(x, y, a, r: real; k: integer);

implementation

procedure levy(x, y, a, r: real; k: integer);
begin
  if k > 0 then begin
    r := r * sin(pi / 4);
    levy(x, y, a + pi / 4, r, k - 1);
    levy(x + r * cos(a + pi / 4), y - r * sin(a + pi / 4), a -pi / 4, r, k - 1);
   end
  else line(trunc(x), trunc(y), trunc(x + r * cos(a)), trunc(y - r * sin(a)));
end;

end.
