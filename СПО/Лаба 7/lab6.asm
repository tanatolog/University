.386
.model flat

extrn GetComputerNameA:DWORD
extrn MessageBoxA:DWORD
extrn ExitProcess:DWORD

.code
_start:
push offset bufferSize
push offset buffer
call GetComputerNameA

push 40h
push offset caption
push offset buffer
push 0
call MessageBoxA

push 0
call ExitProcess

.data

caption db 'Name',0
buffer db 256 dup(0)
bufferSize dd 256

end _start
