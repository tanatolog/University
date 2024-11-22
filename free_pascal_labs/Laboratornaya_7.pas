program laba7;
uses graph, wincrt, LevyCurve;
const step = 10;
      scale = 50;
var
 Gd, Gm, code, depth: integer;
 x, y, xmax, ymax, dimensions: real;
 pressedkey: char;
 s: Boolean = true;


procedure ShowInfo;
begin
  OutTextXY(10, 10, 'Levy Curve');
  OutTextXY(10, 30, '<up> - move to the up');
  OutTextXY(10, 50, '<down> - move to the down');
  OutTextXY(10, 70, '<right> - move to the right');
  OutTextXY(10, 90, '<left> - move to the left');
  OutTextXY(10, 110, '<q> - increase the depth');
  OutTextXY(10, 130, '<a> - reduce the depth');
  OutTextXY(10, 150, '<w> - zoom in');
  OutTextXY(10, 170, '<s> - zoom out');
  OutTextXY(10, 190, '<e> - reset');
  OutTextXY(10, 210, '<Esc> - Exit');
end;

begin
DetectGraph(Gd, Gm);
InitGraph(Gd, Gm, '');
xmax := getMaxX;
ymax := getMaxY;
dimensions := 500;
x := xmax / 2 - dimensions / 2;
y := ymax / 2 + dimensions / 4;
depth := 7;
SetTextstyle(0, 0, 2);
repeat
  if s then begin
    cleardevice;
    levy(x, y, 0, dimensions, depth);
    ShowInfo;
  end;
  s := true;
  pressedkey := readkey;
  code := ord(pressedkey);
  if code = 0 then begin
    pressedkey := readkey;
    code := ord(pressedkey);
    case code of
      72 : begin  // up
             if y > 0 + dimensions / 4 then
               y := y - step;
            end;
      80 : begin  // down
             if y < (ymax + dimensions / 4) then
               y := y + step;
           end;
      75 : begin  //left
             if x > 0 - dimensions / 2 then
               x := x - step;
           end;
      77 : begin  // right
             if x < (xmax - dimensions / 2) then
               x := x + step;
             end;
      else s := false;
    end;
  end else
    case code of
      113: begin  //q
             if depth < 17 then
               depth := depth + 1
             else s := false;
           end;
      97: begin  //a
              if depth > 0 then
                depth := depth - 1
              else s := false;
            end;
      119: begin  //w
             if dimensions < 1000 then begin
               dimensions := dimensions + scale;
             end;
           end;
      115: begin  //s
             if dimensions > 50 then begin
               dimensions := dimensions - scale;
             end;
           end;
     101: begin  //e
           dimensions := 500;
           x := xmax / 2 - dimensions / 2;
           y := ymax / 2 + dimensions / 4;
           depth := 7;
         end;
    else s := false;
  end;
until code = 27;
CloseGraph;
end.

