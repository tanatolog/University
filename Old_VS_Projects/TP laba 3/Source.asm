.686
.MODEL FLAT, C
.CODE

Kramer PROC C a: dword, x1:ptr dword, x2:ptr dword
	push edi
	push esi
	FINIT
	mov edi, dword ptr [ebp+8]; *a
	mov esi, dword ptr [ebp+12]; *x1

	fld dword ptr [edi+16]; a[4]
	fld dword ptr [edi]; a[0]

	fmul st(0), st(1); a[0] * a[4]

	fxch st(1)
	fstp dword ptr [esi]

	fld dword ptr [edi+12]; a[3]
	fld dword ptr [edi+4]; a[1]

	fmul st(0), st(1); a[3] * a[1]

	fxch st(1)
	fxch st(2)

	fsub st(0), st(1); a[0] * a[4] - a[1] * a[3]

	mov eax, 0
	fst dword ptr [esi]
	cmp dword ptr [esi], 0
	jz BOOL
	mov eax, 1
	BOOL:

	fxch st(2)
	fstp dword ptr [esi]
	fstp dword ptr [esi]

	fld dword ptr [edi+8]; a[2]
	fld dword ptr [edi+16]; a[4]

	fmul st(0), st(1); a[2] * a[4]

	fxch st(1)
	fstp dword ptr [esi]

	fld dword ptr [edi+4]; a[1]
	fld dword ptr [edi+20]; a[5]

	fmul st(0), st(1); a[1] * a[5]

	fxch st(1)
	fxch st(2)

	fsub st(0), st(1); a[2] * a[4] - a[1] * a[5]

	fxch st(2)
	fstp dword ptr [esi]
	fstp dword ptr [esi]

	fld dword ptr [edi]; a[0]
	fld dword ptr [edi+20]; a[5]

	fmul st(0), st(1); a[0] * a[5]

	fxch st(1)
	fstp dword ptr [esi]

	fld dword ptr [edi+8]; a[2]
	fld dword ptr [edi+12]; a[3]

	fmul st(0), st(1); a[2] * a[3]

	fxch st(1)
	fxch st(2)

	fsub st(0), st(1); a[0] * a[5] - a[2] * a[3]

	fxch st(2)
	fstp dword ptr [esi]
	fstp dword ptr [esi]

	fdiv st(0), st(2); det2 / det
	mov esi, dword ptr [ebp+16]
	fstp dword ptr [esi]

	fdiv st(0), st(1); det2 / det
	mov esi, dword ptr [ebp+12]
	fstp dword ptr [esi]

	pop esi
	pop edi
	ret
Kramer ENDP

END