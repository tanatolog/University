program heapdesc;

type integ = -1000000000..1000000000;
     quant = 0..1000000;
     numbers = array of integ;
     comparator = procedure(a, b: quant; c: integ; var d: numbers);

procedure ASC(index, count: quant; current: integ; var arr: numbers);
var child: quant;
begin
while index < count div 2 do begin
  child := (index + 1) * 2 - 1;
  if (child < count - 1) and (arr[child] < arr[child + 1]) then
    child := child + 1;
  if current >= arr[child] then break;
  arr[index] := arr[child];
  index := child
end;
arr[index] := current
end;

procedure DESC(index, count: quant; current: integ; var arr: numbers);
var child: quant;
begin
while index < count div 2 do begin
  child := (index + 1) * 2 - 1;
  if (child < count - 1) and (arr[child] > arr[child + 1]) then
    child := child + 1;
  if current <= arr[child] then break;
  arr[index] := arr[child];
  index := child
end;
arr[index] := current
end;

procedure HeapSort (var arr: numbers; c: comparator);
var i, count: quant;
    current: integ;
begin
count := length(arr);
for i := (count div 2) - 1 downTo 0 do
  c(i, count, arr[i], arr);
  for i := count - 1 downTo 0 do begin
    current := arr[i];
    arr[i] := arr[0];
    c(0, i, current, arr)
  end
end;


procedure ReadFile(var arr: numbers; var input: text);
var a: integ;
    c, i: quant;
begin
  Reset(input);
  read(input,c);
  SetLength(arr, c);
  c := c - 1;
  for i := 0 to c do begin
    read(input, a);
    arr[i] := a;
  end;
  Close(input);
end;

procedure WriteFile(var arr: numbers; var output: text);
var l, i: quant;
begin
  Rewrite(output);
  l := length(arr) - 1;
  for i := 0 to l do
    write(output,arr[i], ' ');
  Close(output);
end;

var input, output: text;
    a: numbers;
begin
  Assign(input,'.\input.txt');
  Assign(output,'.\output.txt');
  ReadFile(a, input);
  Heapsort(a, @DESC);
  WriteFile(a, output);
end.

