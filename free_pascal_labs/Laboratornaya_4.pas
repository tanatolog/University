Program laba4;
uses Graph, math, wincrt, crt;

procedure info;
begin
  writeln('Calculatin the area of a shape bounded by a curve');
  writeln('2x^3 - x^2 - 3x + 11 in the positive part of the OY axis.');
  writeln('The Simpson method');
  writeln;
  writeln('Press Enter to return to menu');
  readln;
end;

function limits(var al, bl: real; var flagar, flagabs, flagvis: byte): byte;
begin
 flagar := 0;
 flagabs := 0;
 flagvis := 0;
 writeln('Enter the limits of integration');
 writeln('a - lower, b - upper');
 write('a = '); readln(al);
 write('b = '); readln(bl);
 clrscr;
 while al > bl do begin
    writeln('b must be greater than a ');
    writeln('enter the limits of integration');
    write('a = '); readln(al);
    write('b = '); readln(bl);
    clrscr;
  end;
while (bl - al) > 50000 do begin
    writeln('You entered too large the segment');
    writeln('enter a segment less than 50000');
    write('a = '); readln(al);
    write('b = '); readln(bl);
    clrscr;
end;
 limits := 1;
end;

function Y(t:real): extended;
begin
 Y := 2 * t * t * t - t * t - 3 * t + 11;
end;

function F(z: real): extended;
begin
 F := 0.5 * z * z * z * z - 1/3 * z * z * z - 3/2 * z * z + 11 * z;
end;

function F1(t: real): extended;
begin
  F1:=2 * t * t * t - t * t - 3 * t + 11;
end;

function integration(var i, af, bf: real; var flaglim, flagar, flagabs, flagvis: byte): extended;
var s1, s2, afn, bfn, k: extended;
    n, g: longint;
begin
 if flaglim = 0 then flaglim := limits(af, bf, flagar, flagabs, flagvis);
 flagar := 1;
 flagvis := 1;
 afn := af;
 bfn := bf;
 writeln('interval [', afn:0:2, ';', bfn:0:2, ']');
 if afn < -1.872 then afn := -1.872;
 if bfn < -1.872 then bfn := -1.872;
 if afn = bfn then
   writeln('area of the shape in the positive part of the OY axis: 0')
 else begin
 n := round((bfn - afn) / i);
 s1 := 0;
 s2 := 0;
 k := afn + i;
 g := 1;
 while (g <= (n - 1)) do begin
   g := g + 2;
   s1 := s1 + Y(k);
   k := k + 2;
 end;
 k := afn + 2 * i;
 g := 2;
 while (g <= (n - 2)) do begin
   g := g + 2;
   s2 := s2 + Y(k);
   k := k + 2
 end;
 integration := i/3  * (4 * s1 + 2 * s2 + Y(afn) + Y(bfn));
 writeln('area of the shape in the positive part of the OY axis: ', integration:0:3);
 end;
 writeln;
 writeln('Press Enter to return to menu');
 readln;
end;

function abserror(ao, bo, res: real; var g: real; flagar: byte; var flagabs: byte): real;
begin
 if flagar = 0 then
   writeln('The area has not been calculated yet')
 else begin
   flagabs := 1;
   if ao < -1.872 then ao := -1.872;
   if bo < -1.872 then bo := -1.872;
   if ao = bo then begin
      writeln('the absolute error: 0');
      abserror := 0;
      g := 1;
   end
   else begin
      g := F(bo) - F(ao);
      abserror := abs(g - res);
      writeln('the absolute error: ', abserror:0:4);
   end;
 end;
  writeln;
  writeln('Press Enter to return to menu');
  readln;
end;

procedure oterror(ar, gabs: real; flagar, flagabs: byte);
var ot: real;
begin
 if flagar = 0 then
   writeln('The area has not been calculated yet')
 else begin
 if flagabs = 0 then
   writeln('The absolute error has not been calculated yet')
 else begin
   ot := abs(ar / gabs) * 100;
   if ot = 0 then
     writeln('relative error: 0%')
   else
     writeln('relative error: ', ot:0:4, '%');
 end;
 end;
 writeln;
 writeln('Press Enter to return to menu');
 readln;
end;

procedure visual(lim1, lim2: real; flagvis: byte; var zoomx, zoomy: integer);
var x0, y0, x, xLeft, yLeft, xRight, yRight, n, xk, xa, xb, ya, yb, i, k, dxmod: longint;
    Gm, Gd: integer;
    fmin, fmax, mx, my, dx, y1, dy, num, ao, mod1, a, b, x1, y: extended;
    s: string;
    pressedkey: char;
begin
if flagvis = 0 then begin
  writeln('The area has not been calculated yet');
  writeln;
  writeln('Press Enter to return');
  readln;
  exit;
end
else begin
 x0 := 0;
 DetectGraph(Gd, Gm);
 InitGraph(Gd, Gm, '');
 xLeft := 50;
 yLeft := 50;
 xRight := GetmaxX - 50;
 yRight := GetmaxY - 50;
 a := lim1 - zoomx;
 b := lim2 + zoomx;
 mod1 := lim1 - round(lim1);
 dx := 1;
 if (b - a) <= 5 then dx := 0.5;
 if (b - a)  <= 0 then dx := 0.25;
 if ((b - a) >= 10) and (a mod 2 = 0) then dx := 2;
 if ((b - a) >= 20) and (a mod 5 = 0) then dx := 5;
 if ((b - a) >= 50) and (a mod 10 = 0) then dx := 10;
 if ((b - a) >= 500) and (a mod 100 = 0) then dx := 100;
 if ((b - a) >= 5000) and (a mod 500 = 0) then dx := 500;
 if ((b - a) >= 10000) and (a mod 10000 = 0) then dx := 1000;
 fmin := -5;
 fmax := 12 + zoomy;
 dy := 1;
 if zoomy <= -5 then dy := 0.5;
 if zoomy <= -10 then dy := 0.25;
 if zoomy >= 10 then dy := 2;
 if zoomy >= 20 then dy := 5;
 if zoomy >= 50 then dy := 10;
 if zoomy >= 500 then dy := 100;
 if zoomy >= 10000 then dy := 1000;
 mx := (xRight - xLeft) / (b - a);
 my := (yRight - yLeft) / (fmax - fmin);
 y0 := yRight - trunc(abs(fmin) * my);
 if a <= 0 then begin
   x0 := trunc(abs(a) * mx) + xLeft;
   if mod1 = 0 then OutTextXY(x0 - 10, y0 + 10, '0');
   xk := 0;
   k := 0;
 end
 else begin
   k := 50;
   x0 := 50;
   xk := trunc(abs(a) * mx) + xLeft;
 end;
 if b < 0 then begin
   k := GetmaxX - 50;
   x0 := GetmaxX - 50;
   xk := trunc(abs(b) * mx) + xLeft;
 end;
 SetColor(128);
 xa := x0 + round(lim1 * mx) - xk + k + round(mod1 * mx);
 line(xa, 50, xa, GetmaxY - 50);
 xb := x0 + round(lim2 * mx) - xk + k + round(mod1 * mx);
 line(xb, 50, xb, GetmaxY - 50);
 Setcolor(15);
 line(xLeft, y0, xRight + 10, y0);
 line(x0 + round(mod1 * mx), yLeft - 10, x0 + round(mod1 * mx), yRight);
 SetColor(4);
 SetTextStyle(0, 0, 1);
 OutTextXY(xRight + 20, y0 - 15, 'X');
 OutTextXY(x0 - 5, yLeft - 20, 'Y');
 SetColor(14);
 n := round((b - a) / dx) + 1;
 for i := 1 to n do begin
   num := a + (i - 1) * dx;
   x := xLeft + trunc(mx * (num - a));
   Line(x, y0 - 3, x, y0 + 3);
   if dx < 1 then str(Num:0:2, s)
   else str(Num:0:0, s);
   if abs(num) > 1E-15 then
     OutTextXY(x - TextWidth(s) div 2, y0 + 10, s)
 end;
 n := round((fmax - fmin) / dy) + 1;
 for i := 1 to n do begin
   num := fMin + (i - 1) * dy;
   y := yRight - trunc(my * (num - fmin));
   Line(x0 - 3 + round(mod1 * mx), trunc(y), x0 + 3 + round(mod1 * mx), trunc(y));
   if dy < 1 then str(num:0:2, s)
   else str(num:0:0, s);
   if abs(num) > 1E-15 then
     OutTextXY(x0 + 7 + round(mod1 * mx), trunc(y) - TextHeight(s) div 2, s)
 end;
 Setcolor(0);
 i := 0;
 while i <= 25 do begin
 line(0,i,GetmaxX,i);
 i := i + 1
 end;
 i := GetmaxX;
 while i >= GetmaxX - 19 do begin
 line(i,0,i,GetmaxY);
 i := i - 1
 end;

 x1 := a;
 i := 0;
 if (lim2 - lim1) >= 5 then dxmod := 1000;
 if (lim2 - lim1) < 5 then dxmod := 500;
 if (lim2 - lim1) >= 20 then dxmod := 1000;
 if (lim2 - lim1) >= 50 then dxmod := 5000;
 if (lim2 - lim1) >= 100 then dxmod := 10000;
 if (lim2 - lim1) >= 500 then dxmod := 50000;
 if (lim2 - lim1) >= 1000 then dxmod := 100000;
 if (lim2 - lim1) >= 5000 then dxmod := 500000;
 if (lim2 - lim1) >= 10000 then dxmod := 1000000;
 Setcolor(8);
 while x1 <= b do begin
   y1 := F1(x1);
   x := x0 + round(x1 * mx) + round(mod1 * mx);
   y := y0 - round(y1 * my);
   if (y >= yLeft) and (y <= yRight) and ((x1 <= lim1) or (x1 >= lim2) or (y1 <= 0)) then PutPixel(x - xk + k + round(mod1 * mx), trunc(y), 12);
   if (y >= yLeft) and (y <= yRight) and (x1 >= lim1) and (x1 <= lim2) and (y1 > 0) then PutPixel(x - xk + k + round(mod1 * mx), trunc(y), 2);
   if (x1 >= lim1) and (x1 <= lim2) and (y1 > 0) then begin
     i := i + 1;
     if y < 50 then y := 50;
     if (i mod dxmod = 0) then line(x - xk + k + round(mod1 * mx), trunc(y), x - xk + k + round(mod1 * mx), y0);
     xa := xa + 1;
   end;
   x1 := x1 + 0.0001;
 end;
 SetColor(15);
 SetTextstyle(3, 0, 1);
 OutTextXY(GetmaxX - 500, GetmaxY - 100, 'Press "+" to zoom in, "-" to zoom out');
 OutTextXY(GetmaxX - 500, GetmaxY - 80, 'Use the arrow keys to zoom analog the axes');
 OutTextXY(GetmaxX - 500, GetmaxY - 60, 'Up, Down for the OY axis and Right, Left for the OX axis');
 OutTextXY(GetmaxX - 500, GetmaxY - 40, 'Press Enter to close the window');

end;
 pressedkey := wincrt.readkey;
 if pressedkey = char(#13) then begin
   CloseGraph;
   exit;
 end;
 if pressedkey <> char(0) then begin
   clrscr;
   if (pressedkey = char(#43)) then begin
     if (round(a) mod 500 = 0) and (dx = 500) then begin
         zoomx := zoomx - 500;
         zoomy := zoomy - 500;
       end
       else begin
       if (round(a) mod 100 = 0) and (dx = 100) then begin
         zoomx := zoomx - 100;
         zoomy := zoomy - 100;
       end
       else begin
         if (round(a) mod 10 = 0) and ((dx = 10) or (dx = 100)) then begin
           zoomx := zoomx - 10;
           zoomy := zoomy - 10;
         end
         else begin
           if (round(a) mod 5 = 0) and ((dx = 5) or (dx = 10) or (dx = 100)) then begin
             zoomx := zoomx - 5;
             zoomy := zoomy - 5;
           end
           else begin
             if (round(a) mod 2 = 0) and ((dx = 2) or (dx = 5) or (dx = 10) or (dx = 100)) then begin
               zoomx := zoomx - 2;
               zoomy := zoomy - 2;
             end
             else begin
               zoomx := zoomx - 1;
               zoomy := zoomy - 1;
             end;
           end;
         end;
       end;
     end;
     if zoomx < (lim2 - lim1) then zoomx := 0;
     CloseGraph;
   end;
   if (pressedkey = char(#45)) then begin
     if (round(a) mod 500 = 0) and (dx = 500) then begin
       zoomx := zoomx + 500;
       zoomy := zoomy + 500;
     end
     else begin
       if (round(a) mod 100 = 0) and (dx = 100) then begin
         zoomx := zoomx + 100;
         zoomy := zoomy + 100;
       end
       else begin
         if (round(a) mod 10 = 0) and ((dx = 10) or (dx = 100)) then begin
           zoomx := zoomx + 10;
           zoomy := zoomy + 10;
         end
         else begin
           if (round(a) mod 5 = 0) and ((dx = 5) or (dx = 10) or (dx = 100)) then begin
             zoomx := zoomx + 5;
             zoomy := zoomy + 5;
           end
           else begin
             if (round(a) mod 2 = 0) and ((dx = 2) or (dx = 5) or (dx = 10) or (dx = 100)) then begin
               zoomx := zoomx + 2;
               zoomy := zoomy + 2;
             end
             else begin
               zoomx := zoomx + 1;
               zoomy := zoomy + 1;
             end;
           end;
         end;
       end;
     end;
     CloseGraph;
   end;
   closeGraph;
   visual(lim1, lim2, flagvis, zoomx, zoomy);
   exit;
 end;
 pressedkey := wincrt.readkey;
 if pressedkey = char(#77) then begin
   if (round(a) mod 500 = 0) and (dx = 500) then zoomx := zoomx + 500
   else
     if (round(a) mod 100 = 0) and (dx = 100) then zoomx := zoomx + 100
       else
         if (round(a) mod 10 = 0) and ((dx = 10) or (dx = 100)) then zoomx := zoomx + 10
         else
           if (round(a) mod 5 = 0) and ((dx = 5) or (dx = 10) or (dx = 100)) then zoomx := zoomx + 5
             else
               if (round(a) mod 2 = 0) and ((dx = 2) or (dx = 5) or (dx = 10) or (dx = 100)) then zoomx := zoomx + 2
               else zoomx := zoomx + 1;
   CloseGraph;
   clrscr;
 end;
 if pressedkey = char(#75) then begin
   if (round(a) mod 500 = 0) and (dx = 500) then zoomx := zoomx + 500
   else
     if (round(a) mod 100 = 0) and (dx = 100) then zoomx := zoomx - 100
       else
         if (round(a) mod 10 = 0) and ((dx = 10) or (dx = 100)) then zoomx := zoomx - 10
         else
           if (round(a) mod 5 = 0) and ((dx = 5) or (dx = 10) or (dx = 100)) then zoomx := zoomx - 5
           else
             if (round(a) mod 2 = 0) and ((dx = 2) or (dx = 5) or (dx = 10) or (dx = 100)) then zoomx := zoomx - 2
             else zoomx := zoomx - 1;
   if zoomx < (lim2 - lim1) then zoomx := 0;
   CloseGraph;
   clrscr;
 end;
 if pressedkey = char(#72) then begin
   if dy = 500 then zoomy := zoomy + 500
   else
     if dy = 100 then zoomy := zoomy + 100
       else
         if dy = 10 then zoomy := zoomy + 10
         else
           if dy = 5 then zoomy := zoomy + 5
           else zoomy := zoomy + 1;
   CloseGraph;
   clrscr;
 end;
 if pressedkey = char(#80) then begin
   if dy = 500 then zoomy := zoomy - 500
   else
     if dy = 100 then zoomy := zoomy - 100
       else
         if dy = 10 then zoomy := zoomy - 10
         else
           if dy = 5 then zoomy := zoomy - 5
           else zoomy := zoomy - 1;
   CloseGraph;
   clrscr;
 end;
 closeGraph;
 visual(lim1, lim2, flagvis, zoomx, zoomy);
closeGraph;
end;

procedure writemenu(var h: byte);
const menu: array[1..7] of string = ('The task', 'Set the limits of integration', 'Calculate the area of the ahape', 'Absolute error', 'Relative error', 'Visualization', 'Exit');

var k, item: byte;
    pressedkey: char;
begin
 clrscr;
 for item := 1 to length(menu) do begin
   if item = h then begin
     TextBackground(blue);
     TextColor(white);
   end
   else begin
     TextBackground(black);
     TextColor(white);
   end;
   writeln(item, '.', menu[item]);
 end;
 TextBackground(black);
 TextColor(white);
 pressedkey := readkey;
 if pressedkey = char(#13) then exit;
 if pressedkey <> char(0) then begin
   if (pressedkey = char(#49)) then h := 1;
   if (pressedkey = char(#50)) then h := 2;
   if (pressedkey = char(#51)) then h := 3;
   if (pressedkey = char(#52)) then h := 4;
   if (pressedkey = char(#53)) then h := 5;
   if (pressedkey = char(#54)) then h := 6;
   if (pressedkey = char(#55)) then h := 7;
   writemenu(h);
   exit;
 end;
 pressedkey := readkey;
 if (pressedkey = char(#72)) or (pressedkey = char(#75)) then h := h - 1;
 if (pressedkey = char(#80)) or (pressedkey = char(#77)) then h := h + 1;
 if h > length(menu) then
   h := 1
 else
   if h < 1 then h := length(menu);
 writemenu(h);
end;

var h, flaglim, flagar, flagabs, flagvis: byte;
    u, a, b, area, aerror, gt: real;
    zoomx, zoomy: integer;
    nOkey: char;
begin
clrscr;
u := 1;
h := 1;
a := 0;
b := 0;
gt := 0;
flaglim := 0;
flagar := 0;
flagabs := 0;
flagvis := 0;
zoomx := 0;
zoomy := 0;
while true do begin
 writemenu(h);
 clrscr;
 case h of
 1: begin
      info;
    end;
 2: begin
      zoomx := 0;
      zoomy := 0;
      flaglim := limits(a, b, flagar, flagabs, flagvis);
    end;
 3: begin
      area := integration(u, a, b, flaglim, flagar, flagabs, flagvis);
    end;
 4: begin
      aerror := abserror(a, b, area, gt, flagar, flagabs);
    end;
 5: begin
      oterror(aerror, gt, flagar, flagabs);
    end;
 6: begin
      visual(a, b, flagvis, zoomx, zoomy);
      writeln('Press Escape to return to menu');
      nOkey := readkey;
      while (nOkey <> char(#27)) do nOkey := readkey;
    end;
 7: exit;
end;
end;
end.


