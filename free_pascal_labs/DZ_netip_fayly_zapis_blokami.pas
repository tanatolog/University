Program Task2;
uses crt;

type currency = (RUB, USD, GRP, EUR, JPY);
     account = record      // счёт
       number: string[8];  // номер счёта
       cur: currency;      // валюта
       keeping: integer;   // размер денежных средств
     end;

var buf: array[1..5] of string[8];
    a: account;
    bank: file of account;
    output: file;
    i, k: byte;
    c: currency;

begin
assign(bank,'bank');
assign(output,'output');
reset(bank);
rewrite(output, sizeof(string[8]) * 5);
{$I-}
writeln('enter the currency (RUB, USD, GRP, EUR, JPY)');
readln(c);
while IOResult <> 0 do begin
  writeln('enter the currency (RUB, USD, GRP, EUR, JPY)');
  readln(c);
end;
{$I+}
i := 1;
while not eof(bank) do begin
  read(bank, a);
  if a.cur = c then begin
    buf[i] := a.number;
    if i = 5 then begin            {запись в нетипизированный файл номеров счетов}
      BlockWrite(output,buf,1);    {принадлежащих заданной валюте блоками по 5}
      i := 0;
    end;
    i := i + 1;
  end;
end;
if i <> 1 then begin
  for k := i + 1 to 5 do buf[k] := '';
  blockwrite(output,buf,1);
end;
close(bank);
close(output);
end.


