	AREA startup_code, CODE, READONLY

	;<stolen from arm docs>
	IMPORT |Image$$RO$$Limit| 	; End of ROM code (=start of ROM data)
	IMPORT |Image$$RW$$Base| 	; Base of RAM to initialize
	IMPORT |Image$$ZI$$Base| 	; Base and limit of area
	IMPORT |Image$$ZI$$Limit| 	; to zero initialize
	;</stolen from arm docs>

	IMPORT C_entry

 	ENTRY
 	b start
 	DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 	DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 	DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
start
	;<stolen from arm docs>
	ldr 	r0, =|Image$$RO$$Limit| ; Get pointer to ROM data
	ldr 	r1, =|Image$$RW$$Base| 	; and RAM copy
	ldr 	r3, =|Image$$ZI$$Base| 	; Zero init base => top of initialized data
	cmp	r0, r1 			; Check that they are different
	beq 	%F1
0 	cmp 	r1, r3 			; Copy init data
	ldrcc 	r2, [r0], #4
	ldrcc 	r2, [r1], #4
	bcc 	%B0
1	ldr 	r1, =|Image$$ZI$$Limit| ; Top of zero init segment
	mov 	r2, #0
2 	cmp 	r3, r1 			; Zero init
	strcc 	r2, [r3], #4
	bcc 	%B2
	;</stolen from arm docs>	

	mov	r13, #0x3000000
	add	r13, r13, #0x8000
	b C_entry

	END
