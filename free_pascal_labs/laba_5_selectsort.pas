program selectasc;

type integ = -1000000..1000000;
     quant = 0..1000;
     numbers = array of integ;
     comparator = function(a,b: integ): boolean;

function ASC(a, b: integ): boolean;
begin
  Exit(a > b);
end;

function DESC(a,b:integ):boolean;
begin
  Exit(a<b);
end;

procedure Swap(var a, b: integ);
var c: integ;
begin
  c := a;
  a := b;
  b := c;
end;

procedure SelectionSort(var arr: numbers; c: comparator);
var n, i, j, r: quant;
begin
  n := length(arr);
  for i := 0 to (n - 2) do begin
    r := i;
    for j := (i + 1) to (n - 1) do
      if c(arr[r],arr[j]) then r := j;
    if (r <> i) then Swap(arr[i],arr[r]);
  end;
end;

procedure ReadFile(var arr: numbers; var input: text);
var i, a, c: quant;
begin
  Reset(input);
  read(input,c);
  SetLength(arr, c);
  c := c - 1;
  for i := 0 to c do
    read(input, arr[i]);
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
    Assign(input, '.\input.txt');
    Assign(output, '.\output.txt');
    ReadFile(a,input);
    SelectionSort(a,@ASC);
    WriteFile(a,output);
end.
