; f-f-f-fire intro for the GBA!
; Made by Martin 'Klorathy' Zettergren and Johan 'Xory' Törnqvist 2000-09-22

; Note: We have never coded any ARM assembly language nor have we
; infact seen a gba devkit so this is to take as is.

; contact us at martin@xponential.net or johan@xponential.net

; Don't forget to visit: www.klorathy.com and www.consoledev.com

	AREA fireintro, CODE, READONLY

	ENTRY
	b start
	DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	DCD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

start

	; DMA palette file
	ldr 	r3,palSize
	mov 	r0,#0x5000000
	adrl	r1,colours
	mov 	r2,#0x4000000
	add	r2,r2,#0xd4
	str	r1,[r2],#4
	str	r0,[r2],#4
	str	r3,[r2]

	; setup colors for fire
	mov	r0,#0x5000000
	mov	r1,#0x0
	mov	r2,#0x1f
s_loop
	strh	r1,[r0],#0x2
	add	r1,r1,#0x1
	strh	r1,[r0],#0x2
	add	r1,r1,#0x020
	add	r1,r1,#0x1
	strh	r1,[r0],#0x2
	add	r1,r1,#0x020
	add	r1,r1,#0x1
	strh	r1,[r0],#0x2
	add	r1,r1,#0x420
	add	r1,r1,#0x1
	subs	r2,r2,#0x4
	bge	s_loop

	mov	r1,#0x4
	orr	r1,r1,#0x400
	mov	r0,#0x4000000
	strh	r1,[r0]

	; setup buffer pointers for the fire effect
	adrl 	r10,buffer1
	adrl 	r11,buffer2
	str 	r10,pointer1
	str	r11,pointer2

	; initialize fire movetables index
	mov 	r12,#0
	str 	r12,tabIndex

	; initialize regs used by textwriter
	mov 	r6,#0
	mov 	r7,#0
	adrl 	r8,text
	ldr 	r9,textStartOffset

mainloop

	mov 	r0,#0x04
	add 	r0,r0,#0x400
	mov 	r1,#0x4000000
	str 	r0,[r1]
	mov 	r2,#20
	add 	r1,r1,#6

	; wait for line 20!!!
loop
	ldr 	r0,[r1]
	and 	r0,r0,#0xff
	cmp 	r0,r2
	bne 	loop

	; write some pixels to firebuffer for processing
	; Get pointer and add 240*36 to it
	ldr 	r1,pointer1
	add 	r1,r1,#0x2100
	add 	r1,r1,#0xc0
	; Get x and y value from tables and add them to pointer
	adrl 	r2,firemove
	ldr 	r12,tabIndex
	add 	r2,r2,r12
	ldrb 	r2,[r2]
	and  	r2,r2,#0xff
	add 	r1,r1,r2
	adrl 	r3,firemove2
	add  	r3,r3,r12
	ldrb 	r3,[r3]
	mov 	r4,#240
	mul 	r4,r3,r4
	add 	r1,r1,r4
 
	adrl 	r2,firePic
	; we will write 31 (highest pal index for the fire) to the buffer
	mov 	r5,#0x1f

	; 4 y-lines 
	mov 	r4,#4
	; subtract by y move (so we will only copy btw 0 and 4 lines of the pixels)
	sub 	r4,r4,r3

	; x counter (200 pixels)
	mov 	r0,#200
	; write inner loop (checks for 0 as transparent i.e no write)
writeloop
 	ldrb 	r3,[r2],#1
 	cmp  	r3,#0
 	beq  	transparent
 	strb 	r5,[r1]
transparent
	add 	r1,r1,#1
	subs 	r0,r0,#1
	bne 	writeloop
 	add 	r1,r1,#40	 
 	subs 	r4,r4,#1
	mov 	r0,#200
 	bne 	writeloop

	; Do fire effect

	; Fetch pointer to buffers
	ldr 	r4,pointer1
	ldr 	r0,pointer2

	; Offset some more pointers so we get a diamond shape of reads!
	mov 	r3,r4
	add 	r4,r4,#240
	mov 	r1,r4
	add 	r1,r1,#240
	sub 	r4,r4,#1

	; Decide which innerloop to use (one of them fades the fire)
	ldr 	r2,InnerLoopSwitch
 	cmp 	r2,#0
	beq 	OtherLoop

	; Do fireeffect innerloop
	mov 	r2,#240*40
fireloop
	; read 4 pixels in a diamond shape and put average in the other buffer
	ldrb 	r5,[r4],#2
	ldrb 	r10,[r4]
	add  	r5,r5,r10
	ldrb 	r10,[r1],#1
	add  	r5,r5,r10
	ldrb 	r10,[r3],#1
	add  	r5,r5,r10
	mov  	r5,r5,lsr #2
	strb 	r5,[r0],#1
	sub  	r4,r4,#1
	subs 	r2,r2,#1
	bne 	fireloop

 	b 	EndOfLoop

OtherLoop
 	mov 	r2,#240*40
fireloop2
	; read 4 pixels in a diamond shape and put average in the other buffer subtracted by 1
 	ldrb 	r5,[r4],#2
 	ldrb 	r10,[r4]
 	add  	r5,r5,r10
 	ldrb 	r10,[r1],#1
 	add  	r5,r5,r10
 	ldrb 	r10,[r3],#1
 	add  	r5,r5,r10
 	mov  	r5,r5,lsr #2
 	subs 	r5,r5,#1
 	bhi  	no_floor
 	mov  	r5,#0
no_floor
 	strb 	r5,[r0],#1
 	sub  	r4,r4,#1
 	subs 	r2,r2,#1
 	bne 	fireloop2

EndOfLoop

	; Do count on InnerLoopSwitch (each 4th time we will run the subtracting one)
 	ldr 	r0,InnerLoopSwitch
 	add 	r0,r0,#1
 	and 	r0,r0,#3
 	str 	r0,InnerLoopSwitch

	; Now we will start waiting for the vblank
 	mov 	r0,#0x04
 	add 	r0,r0,#0x400
 	mov 	r1,#0x4000000
 	str 	r0,[r1]
 	mov 	r3,#161
 	add 	r1,r1,#6

	; wait for line 161!!!
loop2
	ldr 	r0,[r1]
	and 	r0,r0,#0xff
 	cmp 	r0,r3
 	bne 	loop2

 	; We are in vblank here

	bl 	LogoMove

	; copy fireeffect to bottom of screen with DMA (prepared before waiting for vblank!!!
	ldr 	r3,fireSize
	mov 	r0,#0x6000000		; screen pointer
	add 	r0,r0,#0x7300		; add 240*124 to get to the last 36 lines
	add 	r0,r0,#0x50
	ldr	r1,pointer2		; pointer to write buffer for fire
	mov 	r2,#0x4000000
	add	r2,r2,#0xd4
	str	r1,[r2],#4
	str	r0,[r2],#4
	str	r3,[r2]

	; increase tabIndex
	ldr	r12,tabIndex
	add	r12,r12,#1
	str	r12,tabIndex
	cmp	r12,#52
	bne	not_reached_end
	mov	r12,#0
	str	r12,tabIndex
not_reached_end

	; switch buffers
 	ldr  	r0,pointer1
 	ldr  	r1,pointer2
 	str  	r1,pointer1
 	str  	r0,pointer2

	; if we are wiping jump to the wipe routine now!
 	ldr 	r0,wipeActive
 	cmp 	r0,#1
 	beq 	doWipeNow

 	; delay register for textwriter
 	add 	r6,r6,#1
 	and 	r6,r6,#1

	; Handle textwriter fetch of chars and handling of control codes (i.e 0,1 and 2)
	ldr	r0,[r8]
	and	r0,r0,#0xff
	cmp	r0,#32
	bne	not_space
	; don't do delay on spaces
	mov	r6,#0
not_space
	; if delay reg isn't 0 then we won't go on with the textwriting
	cmp	r6,#0
	bne	noOperation
	; get next char!
	add	r8,r8,#1
	ldr	r0,[r8]
	and	r0,r0,#0xff
	cmp	r0,#1
	bne	not_newline
	; handle newline by fetching next char and add a line to register r9 (holds vertical pos)
	add	r8,r8,#1
	ldr	r0,[r8]
	and	r0,r0,#0xff
	add	r9,r9,#240*16
	; reset xpos (note the add just below)
	mov	r7,#-1
not_newline
	; go to next xpos
	add	r7,r7,#1
	cmp	r0,#2
	bne	not_newscreen
	; handle newscreen by fetching next char and go to the clrtext code
	add	r8,r8,#1
	ldr	r0,[r8]
	b	clrtext
not_newscreen
	cmp	r0,#0
	bne	not_eot

	; reset textpointer since we have come to the end!!!
	adrl	r8,text
	ldr	r0,[r8]
	and	r0,r0,#0xff
clrtext
	mov	r7,#0
	ldr	r9,textStartOffset

	; set us into wipe mode and call the wipe code
	mov	r0,#1
	str	r0,wipeActive
	b	doWipeNow
not_eot

	; fetch pointer to charachter
	adrl	r1,fonts
	mov	r2,r0
	sub	r0,r0,#32
	mov	r2,#8
	mul	r0,r2,r0
	add	r1,r1,r0
	; fetch pointer to screen
	mov	r0,#0x6000000
	mov	r10,#8
	mul	r10,r7,r10
	add	r0,r0,r10
	add	r0,r0,r9

	; copy a char to screen (unrolled the x-loop)!!!
	mov	r2,#16
charcopy_loop
	ldr	r4,[r1],#4
	str	r4,[r0],#4
	ldr	r4,[r1],#4
	str	r4,[r0],#4
	add	r0,r0,#240-8
	add	r1,r1,#512-8
	subs	r2,r2,#1
	bne	charcopy_loop

	; Now we have written the char to screen!!!
noOperation

	b	mainloop

doWipeNow
	; uses r6 at pointer to which line we are clearing
	ldr	r0,textStartOffset
	add	r0,r0,r6
	mov	r1,#0x6000000
	add	r1,r1,r0
	mov	r2,#480/4
	mov	r3,#0
	; This loop will clear to lines of the text each tick! 
clrLoop
	str	r3,[r1],#4
	subs	r2,r2,#1
	bne	clrLoop
	add	r6,r6,#480
	ldr	r4,textTotalHeight
	cmp	r6,r4
	ble	noOperation
	mov	r6,#0
	str	r6,wipeActive
	b	noOperation


; Logomoving routines
LogoMove
	ADRL	r4,OLD_LOGOCNT
	ldr	r0,[r4],#4	; X position
	ldr	r1,[r4],#4	; Y position
	ldr	r2,[r4],#4	; Y inc
	ldr	r3,[r4],#4	; X inc

	mov	r5,lr
	BL	ClearScreen

	ADRL	r4,LOGOCNT
	ldr	r0,[r4],#4	; X position
	ldr	r1,[r4],#4	; Y position
	ldr	r2,[r4],#4	; Y inc
	ldr	r3,[r4],#4	; X inc

	BL	DrawPicture
	mov	lr,r5
	add	r1,r1,r2
	cmp	r1,#40
	BLT	keepdirection
	MVN	r2,r2
	add	r2,r2,#1
keepdirection	
	cmp	r1,#0
	BGT	keepdirection2
	MVN	r2,r2
	add	r2,r2,#1
keepdirection2
	add	r0,r0,r3
	CMP	r0,#179
	BLT	keepdirection3
	MVN	r3,r3
	add	r3,r3,#1
keepdirection3
	cmp	r0,#0
	BGT	keepdirection4
	MVN	r3,r3
	add	r3,r3,#1
keepdirection4
	ADRL	r4,LOGOCNT
	ADRL	r10,OLD_LOGOCNT
	ldr	r5,[r4],#4
	str	r5,[r10],#4
	ldr	r5,[r4],#4
	str	r5,[r10],#4
	ldr	r5,[r4],#4
	str	r5,[r10],#4
	ldr	r5,[r4],#4
	str	r5,[r10],#4
	ADRL	r4,LOGOCNT
	str	r0,[r4],#4	; X position
	str	r1,[r4],#4	; Y position
	str	r2,[r4],#4	; Y inc
	str	r3,[r4],#4	; X inc
	mov	pc,lr		;Return

ClearScreen
	STMFD   sp!, {r0-r6}	; save some working registers

	mov	r2,r1,lsl #1	; Lookup Y value in table
	ADRL	r6,YTABLE
	add	r6,r6,r2
	ldrh	r1,[r6],#4

	mov	r5,#0x6000000	; lr = pointer to screen
	add	r0,r0,r1		; Combine x and y
	add	r5,r5,r0		; Offset screen pointer
	ADRL    r0, PIC			; r0 = pointer to source block
	mov	r3, #0
	mov	r2, #60
	mov	r4, #20
line_wordclr
	STRB	r3, [r5], #1	; store a word to the destination
	SUBS    r2, r2, #1		; decrement the counter
	BNE     line_wordclr	; ... copy more
	ADD	r5,r5,#180
	mov	r2,#60
	SUBS    r4, r4, #1	; decrement the counter
	BNE     line_wordclr	; ... copy more

	LDMFD   sp!,{r0-r6}	; don't need these now - restore originals
	MOV     pc, lr		; Return

; This functions expects x position in r0 and y position in r1
DrawPicture
	STMFD   sp!, {r0-r6}	; save some working registers

	mov	r2,r1,lsl #1	; Lookup Y value in table
	ADRL	r6,YTABLE
	add	r6,r6,r2
	ldrh	r1,[r6],#4

	mov	r5,#0x6000000	; lr = pointer to screen
	add	r0,r0,r1		; Combine x and y
	add	r5,r5,r0		; Offset screen pointer
	ADRL    r0, PIC			; r0 = pointer to source block
	mov	r2, #60
	mov	r4, #20
line_wordcopy
	LDRB	r3, [r0], #1	; we can only write bytes if we want to move per pixel...
	STRB	r3, [r5], #1	; store a word to the destination
	SUBS    r2, r2, #1		; decrement the counter
	BNE     line_wordcopy	; ... copy more
	ADD	r5,r5,#180
	mov	r2,#60
	SUBS    r4, r4, #1		; decrement the counter
	BNE     line_wordcopy	; ... copy more

	LDMFD   sp!,{r0-r6}		; don't need these now - restore originals
	MOV     pc, lr			; Return

stop
	MOV     r0, #0x18       ; angel_SWIreason_ReportException
	LDR     r1, =0x20026    ; ADP_Stopped_ApplicationExit
	SWI     0x123456        ; Angel semihosting ARM SWI

	INCLUDE YTABLE.S

    AREA BlockData, DATA, READWRITE

wipeActive		DCD 0			; if 1 the wipe is active...
LOGOCNT			DCD 1,1,1,2		; Counters for logo movement
OLD_LOGOCNT		DCD 1,1,1,2		; Counters for logo movement
InnerLoopSwitch DCD 0				; Counter for which innerloop to use (0 means subtracting one)

pointer1		DCD 0			; pointer to buffer read
pointer2		DCD 0			; pointer to buffer write
tabIndex		DCD 0			; index to fire movetables

firemove
			DCB 0,1,38,2,4,7,39,39,10,14,18,20,20,20,20,0,0,23,28,3,34,39,20,20,20,20
			DCB 39,38,2,37,35,32,0,0,29,25,21,20,20,20,20,39,39,16,11,35,5,0,20,20,20,20

firemove2
			DCB 0,0,0,0,1,1,0,0
			DCB 0,0,0,1,0,0,0,0
			DCB 0,0,0,0,0,0,0,1
			DCB 0,0,1,0,0,0,1,1
			DCB 0,0,0,0,1,0,0,0
			DCB 0,0,0,0,1,0,0,0
			DCB 0,0,0,0


colours
			INCBIN pic.pal
textStartOffset
			DCD 240*70
textTotalHeight	
			DCD 240*48
palSize
		        DCD 0x84000100
fireSize
			DCD 0x840021c0

fonts
			INCBIN 8x16.raw

text
			DCB "          F-F-F-FIRE          "
			DCB 1
  			DCB "    WRITTEN FOR THE GBA BY    "
			DCB 1
			DCB "      KLORATHY AND XORY       "
			DCB 2
			DCB " FOR ALL YOUR CONSOLE HACKING "
			DCB 1
  			DCB "      WWW.CONSOLEDEV.COM      "
			DCB 1
			DCB "THE ONLY SITE YOU'LL EVER NEED"
			DCB 2
			DCB "   GREETS TO THE FOLLOWING:   "
			DCB 1
  			DCB "  REBELS, FAIRLIGHT, RAM JAM  "
			DCB 1
			DCB "      PHOENIX AND YODEL!      "
			DCB 0

firePic
			INCBIN fire.raw
PIC
			INCBIN  pic.raw

	AREA buffers, DATA, READWRITE

buffer1			% 240*42
buffer2			% 240*42

	END 

