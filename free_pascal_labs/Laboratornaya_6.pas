Program MakeQueue;
Uses crt, heaptrc, DSQueue;
type lot = longint;
     pen = ansistring;
     commands = array of string;
     strr = record
       text: String;
       countSpaces: longint;
     end;

Const row = 120;
      max = 255;
      cmdList: array of String = ('purify', 'exit', 'vacuous', 'help', 'insert', 'show', 'remove', 'clrscr');

Var buffer, cmdEl: commands;
    bs, h: string;
    s: pen;
    ch: Char;
    x, y, curY, curCom: lot;
    w: boolean = true;
    q: Queue;

Procedure WriteCom(Var s: pen; yy: lot);
var i: lot = 0;
    a, b, c: lot;
Begin
  gotoxy(1, curY);
  clreol;
  while i < yy do begin
    gotoxy(1, wherey + 1);
    clreol;
    inc(i);
  end;
  a := (x + length(h) + 2) mod row;
  if a = 0 then begin
    a := x + length(h) + 2;
    b := 0;
  end
  else b := (x + length(h) + 2) div row;
  c := (x + length(h) + 3) div row;
  if curY + c > 25 then begin
    curY := curY - c;
    i := 0;
    while i < c do begin
      writeln;
      inc(i);
    end;
  end;
  gotoxy(1, curY);
  write(h, ' ');
  write(s);
  gotoxy(a,curY+b);
end;

Procedure DeleteChar(var s: pen);
var y1: lot;
begin
  if x >= length(h) then begin
    x := x - 1;
    delete(s, x + 1, 1);
    y1 := (length(h) + length(s) + 2) div row;
    WriteCom(s, y1);
  end;
end;

Procedure AddChar(var s: pen; ch: char);
var y1: lot;
Begin
  if length(s) < max then begin
    x := x + 1;
    s := copy(s, 1, x - 1) + ch + copy(s, x, length(s));
    y1 := (length(h) + length(s) + 2) div row;
    WriteCom(s, y1);
  end;
end;

procedure SaveCommand;
var c: lot;
begin
  c := length(buffer);
  buffer[c - 1] := s;
  setlength(buffer, c + 1);
  curCom := c;
end;

procedure ChangeCommand(c: lot);
var l: lot;
begin
  if curCom >= 0 then begin
    y := (length(h) + length(s) + 2) div row;
    buffer[curCom] := s;
    if (c = 1) and (curCom > 0) then begin
      curCom := curCom - 1;
    end
    else 
    if (c = 2) and (curCom < length(buffer)-1) then 
      begin
      curCom := curCom + 1;
    end;
    s := buffer[curCom];
    x := length(s);
    WriteCom(s,y);
  end;
end;

function Spaces(s: pen):strr;
var i: lot;
    str: strr;
begin
    i:=0;
    while s[i+1]=' ' do i:=i+1;
    delete(s,1,i);
    str.text := s;
    str.countSpaces := i;
    Exit(str);
end;

procedure SProcessing(str:string);
var i: lot = 2;
    c: lot = 0;
    s1: strr;
begin
    s1 := Spaces(str);
    if length(s1.text)>0 then
    begin
        setLength(cmdEl,1);
        cmdEl[c]:=s1.text[1];
    end;
    while i <= length(s1.text) do
    begin
        if (s1.text[i-1]=' ') and (s1.text[i]<>' ') then
        begin
            Inc(c);
            setLength(cmdEl,length(cmdEl)+1);
            cmdEl[c]:=s1.text[i];
        end
        else if s1.text[i]<>' ' then
        begin
            cmdEl[c]:=cmdEl[c]+s1.text[i];
        end;
        Inc(i);
    end;
end;

procedure Info;
begin
  writeln('Implementing the queue data structure');
  writeln('Commands: ');
  writeln('help - show all commands;');
  writeln('purify - clear the queue;');
  writeln('exit - exit the program;');
  writeln('vacuous - shows whether there are items in the queue or not;');
  writeln('insert <element> - inserting an item at the end of the queue;');
  writeln('show - shows all items;');
  writeln('remove - removes an item from the beginning of the queue;');
  writeln('clrscr - clears the screen;');
end;

function Args(c: lot): boolean;
var i: longint;
begin
    if length(cmdEl)-1 = c then
    begin
        Exit(true);
    end
    else
    begin
        for i:=c+1 to length(cmdEl)-1 do
        begin
            writeln('Unknown argument: ', cmdEl[i]);
        end;
    end;
    Exit(false);
end;

procedure Action(cmd: string);
var a: longint;
    b: integer;
begin
  case cmd of
  'clrscr': begin
              if Args(0) then clrscr;
            end;
  'exit': begin
            if Args(0) then
                begin
                  w := false;
                  exit;
                end;
            end;
  'vacuous': begin
               if Args(0) then
                 if Hollow(q) then writeln('The queue is empty.')
                 else writeln('The queue is not empty.');
             end;
  'help': begin
            if Args(0) then Info;
          end;
  'insert': begin
              if Args(1) then begin
                val(cmdEl[1],a,b);
                if b = 0 then begin
                  InsertQ(q, a);
                  writeln('Carried out');
                end
                else writeln('You entered an invalid value.');
              end;
            end;
  'show': begin
            if Args(0) then begin
              ShowQueue(q);
              writeln;
            end;
          end;
  'remove': begin
              if Args(0) then begin
                if Remove(q, a) then writeln('Item ',a, ' deleted.')
                else writeln('The queue is empty.');
              end;
            end;
  'purify': begin
              if Args(0) then begin
                Purify(q);
                writeln('Carried out');
              end;
            end;
  else writeln('There is no such command!');
  end;
end;

procedure RunCommand;
begin
  SProcessing(s);
  if length(cmdEl) > 0 then Action(cmdEl[0]);
end;

function EnterCommand(y: lot): lot;
var a, b: lot;
begin
  if y < 25 then y := wherey + 1;
  x := 0;
  b := (length(s) + length(h) + 2) div row;
  if b > 0 then a := (length(s) + length(h) + 2) mod row
  else a := length(s) + length(h) + 2;
  gotoxy(a, curY + b);
  writeln;
  RunCommand;
  cmdEl := nil;
  SaveCommand;
  s := '';
  write(h, ' ');
  Exit(y);
end;

procedure AutoComplection;
var i: longint;
    str: strr;
begin
    str := Spaces(s);
    for i:=0 to length(cmdList)-1 do
    begin
        if pos(str.text,cmdList[i]) = 1 then
        begin
            Delete(s,str.countSpaces+1,Length(s));
            Insert(cmdList[i],s,str.countSpaces+1);
            x:=length(s);
            WriteCom(s,1);
            break;
        end;
    end;
end;

procedure cursorLeft;
var a, b: lot;
begin
    if x > 0 then begin
        x:=x-1;
        a:=(x+length(h)+2) mod row;
        if a = 0 then
        begin
            a:=x+length(h)+2;
            b:=0;
        end
        else begin
            b:=(x+length(h)+2) div row;
        end;
        gotoxy(a,curY+b);
    end;
end;

procedure cursorRight;
var a, b: lot;
begin
    if x < length(s) then begin
        x:=x+1;
        a:=(x+length(h)+2) mod row;
        if a = 0 then
        begin
            a:=x+length(h)+2;
            b:=0;
        end
        else
        begin
            b:=(x+length(h)+2) div row;
        end;
        gotoxy(a,curY+b);

    end;
end;

procedure SpecialKey(s: pen);
var code: lot;
    chr: char;
begin
  chr := ReadKey;
  code := ord(chr);
  Case code of
  75: begin //<-
        cursorLeft;
      end;
  77: begin //->
        cursorRight;
      end;
  72: begin //up
        ChangeCommand(1);
      end;
  80: begin //down
        ChangeCommand(2);
      end;
  end;
end;

function choiceCommand(ch: char; var y: lot): boolean;
var code: lot;
begin
  code := ord(ch);
  Case code of
  13: begin // Enter
        y := EnterCommand(y);
        curY := wherey;
        if w = false then exit(false);
      end;
   8: begin //Backspace
        DeleteChar(s);
      end;
   9: begin //Tab
        AutoComplection;
      end;
   0: SpecialKey(s);
      Else
      if (code in [48..57]) or (code in [97..122]) or (code = 45) or (code = 32) or (code in [65..90]) then AddChar(s,ch);
  end;
  exit(true);
end;

Begin
CreateQueue(q);
ClrScr;
s := '';
x := 0;
h := '>';
curCom := -1;
write(h,' ');
setlength(buffer,1);
curY := WhereY;
While w do begin
  ch := ReadKey;
  w := choiceCommand(ch, curY);
end;
Purify(q);
buffer := nil;
End.
