unit DSQueue;

Interface
type QElement = longint;
     node = record
       data: QElement;
       next: ^node;
     end;
     Queue = record
       beginQ, endQ: ^node;
     end;

procedure CreateQueue(var q: queue);
function Hollow(var q: Queue): boolean;
procedure InsertQ(var q: Queue; d: QElement);
function Remove(var q: Queue; var n: QElement): boolean;
procedure ShowQueue(var q: Queue);
procedure Purify(var q: Queue);

Implementation

procedure CreateQueue(var q: queue);
begin
  q.beginQ := nil;
  q.endQ := nil;
end;

function Hollow(var q: Queue): boolean;
begin
  Exit(q.beginQ = nil);
end;

procedure InsertQ(var q: Queue; d: QElement);
begin
  if q.beginQ = nil then begin
    new(q.beginQ);
    q.endQ := q.beginQ;
  end
  else begin
    new(q.endQ^.next);
    q.endQ := q.endQ^.next;
  end;
  q.endQ^.data := d;
  q.endQ^.next := nil;
end;

function Remove(var q: Queue; var n: QElement): boolean;
var t: ^node;
begin
  if Hollow(q) then Exit(false);
  n := q.beginQ^.data;
  t := q.beginQ;
  q.beginQ := q.beginQ^.next;
  if q.beginQ = nil then q.endQ := nil;
  dispose(t);
  Exit(true);
end;

procedure ShowQueue(var q: Queue);
var t: ^node;
    p: word;
begin
  if Hollow(q) then begin
    Write('The queue is hollow.');
    Exit;
  end;
  t := q.beginQ;
  p := 1;
  while t <> nil do begin
    write(p, ':', t^.data, ', ');
    t := t^.next;
    p := p + 1;
  end;
end;

procedure Purify(var q: Queue);
var wok: boolean;
    n: QElement;
begin
  while Hollow(q) = false do wok := remove(q, n);
end;

end.

