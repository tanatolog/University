program Task;
var file1, file2: text;
    s: string[27];  // 27 символов - максимальная длинна строки, 15 на фамилию и 12 на оценки и пробелы
    i: integer;

begin
assign(file1,'fileT1.txt');
assign(file2,'fileT2.txt');
reset(file1);
rewrite(file2);
while not Eof(file1) do begin
  readln(file1,s);
  if Pos('2',s) = 0 then begin  // поиск фамилий студентов, не имеющих 2
    Delete(s,Pos(' ',s),12);    // удаление оценок
    write(file2,s + ' ');       // запись этих фамилий в другой файл через пробел
  end;
end;
close(file1);
close(file2);
end.




