@********************************************************************
@*	Nintendo of America Developer Support                           *
@*  Scott Perras                                                    *
@*                                                                  *
@*  task.s                                                          *
@********************************************************************
  .INCLUDE    "AgbDefine.s"
  .INCLUDE    "AgbMemoryMap.s"
  .INCLUDE    "AgbMacro.s"
  .TEXT

	.EXTERN 	systemStack
	.EXTERN		systemRA
	.EXTERN		global_activeTask
	.EXTERN   getNextTask

@--->task structure equates
@--->if task structure is changed, these MUST be updated!
FP_OFFSET					= 44
IP_OFFSET					= 48
SP_OFFSET					= 52
LR_OFFSET					= 56
CPSR_OFFSET				= 64
WAITSTATE_OFFSET  = 68
ALLOC_OFFSET 			= 72


TASK_STACK_SIZE		= 2048
TASK_STRUCT_SIZE	= 120
TOTAL_TASK_STACK_SIZE = TASK_STACK_SIZE	+ TASK_STRUCT_SIZE

.macro DEFINE_SPACE label,size
\label = ADDR
ADDR = ADDR+\size
.endm

.macro RESERVE_SPACE size
ADDR = ADDR+\size
.endm

	.GLOBAL task1Stack
  .GLOBAL task2Stack
  .GLOBAL task3Stack
  .GLOBAL task4Stack
  .GLOBAL task5Stack

ADDR = 0x02000000

	DEFINE_SPACE	task1Stack, TOTAL_TASK_STACK_SIZE
	DEFINE_SPACE	task2Stack, TOTAL_TASK_STACK_SIZE
	DEFINE_SPACE	task3Stack, TOTAL_TASK_STACK_SIZE
	DEFINE_SPACE	task4Stack, TOTAL_TASK_STACK_SIZE
	DEFINE_SPACE	task5Stack, TOTAL_TASK_STACK_SIZE


@--------------------------------------------------------------------
@- saveSystemStack
@-
@- Save current stack pointer into systemStack var
@-
@--------------------------------------------------------------------
	.GLOBAL		saveSystemStack
  .ALIGN
  .CODE 32
saveSystemStack:
  ldr 	r0, =systemStack
	str		sp, [r0]
	bx		lr

@--------------------------------------------------------------------
@- setSystemStack
@-
@- Set stack pointer to systemStack
@-
@--------------------------------------------------------------------
	.GLOBAL		setSystemStack
  .ALIGN
  .CODE 32
setSystemStack:
  ldr 	r0, =systemStack
	ldr   sp, [r0]
	bx		lr

@--------------------------------------------------------------------
@- sleep
@-
@- r0 = Num frames to sleep
@-
@--------------------------------------------------------------------
	.GLOBAL		sleepme
  .ALIGN
  .CODE 32
sleepme:

	@---->push r0 (num sleeps)
	stmfd sp!, {r0}

	@---->get active task ptr in r0
  ldr 	r0, =global_activeTask
	@--->get address of task struct
  ldr		r0, [r0]

	@--->make sure there is an active task
	cmp		r0, #0
	bne		.activeTask

	@--->no active tasks, pop r0 and return
	ldmfd sp!, {r0}
	bx lr

.activeTask:

	@---->store r1-r3 into task struct (to make avail)
	str		r1, [r0, #4]
	str		r2, [r0, #8]
	str		r3, [r0, #12]

	@---->pop r0 into r1 (num sleeps)
	ldmfd sp!, {r1}

	@---->store num sleeps into waitState
	str		r1, [r0, #WAITSTATE_OFFSET]

	@---->store r0 into task struct
	str		r1, [r0, #0]

	@---->get alloc pointer from task structure
	ldr		r2, [r0, #ALLOC_OFFSET]
	@---->load checksum from stack
	ldr		r2, [r2]

	@---->verify checksum on stack is intact
	mov 	r3, #0x3a800000
	orr		r3, r3, #0x3140
	cmp		r2, r3

	@---->bad news!
	bne		_stackFail

	@---->move cpsr into r1 and save
	mrs		r1, cpsr
	str		r1, [r0, #CPSR_OFFSET]		@cpsr

	@---->save registers r4-r14
	add 	r1, r0, #16
	stmia r1!, {r4-r14}

	@str 	r4,  [r1, #16]
	@str 	r5,  [r1, #20]
	@str 	r6,  [r1, #24]
	@str 	r7,  [r1, #28]
	@str 	r8,  [r1, #32]
	@str 	r9,  [r1, #36]
	@str 	r10, [r1, #40]
	@str 	r11, [r1, #44]    @fp
	@str 	r12, [r1, #48]    @ip
	@str 	r13, [r1, #52]		@sp
	@str 	r14, [r1, #56]		@lr

	bl getNextTask		@returns activeTask in r0
	b restoreTaskRegisters


@--------------------------------------------------------------------
@- _stackFail
@-
@-	Loops forever signaling a stack failure
@-
@--------------------------------------------------------------------
	.ALIGN
	.EXTERN stackFailMessage
  .CODE 32
_stackFail:
	bl stackFailMessage
	b 	_stackFail

@--------------------------------------------------------------------
@- executeTaskingSystem
@-
@-	r0 = Main Task pointer (first task created)
@-
@--------------------------------------------------------------------
	.GLOBAL		executeTaskingSystem
  .ALIGN
  .CODE 32
executeTaskingSystem:

	@---->set system stack
  ldr 	r1, =systemStack
	str		sp, [r1]

	@--->set systemRA
	ldr		r1, =systemRA
	str		r14, [r1]

	@---->save current fp and ip regs into mainTask struct
	str	r11, [r0, #FP_OFFSET]
	str r12, [r0, #IP_OFFSET]

	@---->set sp for mainTask
	ldr r13, [r0, #SP_OFFSET]

	@---->set lr to mainTask function
	ldr r14, [r0, #LR_OFFSET]

	@---->branch to address
	bx	lr

	.GLOBAL		returnFromTaskingSystem
	.ALIGN
	.CODE 32
returnFromTaskingSystem:

  ldr 	r0, =systemStack
	ldr   sp, [r0]

	ldr		r0, =systemRA
	ldr		r14, [r0]
	bx		lr



#IF 0
@--------------------------------------------------------------------
@- restoreTaskRegisters_oneTime
@-
@- r0 = task pointer
@-
@--------------------------------------------------------------------
	.GLOBAL		restoreTaskRegisters_oneTime
  .ALIGN
  .CODE 32
restoreTaskRegisters_oneTime:

	@---->set registers r1-r10
	add r13, r0, #4
	ldmia r13!, {r1-r10}

	@ldr r1,  [r0, #4 ]
	@ldr r2,  [r0, #8 ]
	@ldr r3,  [r0, #12]
	@ldr r4,  [r0, #16]
	@ldr r5,  [r0, #20]
	@ldr r6,  [r0, #24]
	@ldr r7,  [r0, #28]
	@ldr r8,  [r0, #32]
	@ldr r9,  [r0, #36]
	@ldr r10, [r0, #40]

	@ DO NOT TOUCH THESE FOR NOW!
	@@ldr r11, [r0, #28]		@fp
	@@ldr r12, [r0, #32]   @ip
	@ DO NOT TOUCH THESE FOR NOW!

	@---->set sp
	ldr r13, [r0, #SP_OFFSET]

	@ WHAT ABOUT THIS??
	@---->set cpsr
	@ldr r14, [r0, #CPSR_OFFSET]
	@msr	cpsr, r14
	@ WHAT ABOUT THIS??

	@---->set lr
	ldr r14, [r0, #LR_OFFSET]

	@---->set r0 last
	ldr r0,  [r0]

	@---->branch to address
	bx	lr
#ENDIF

@--------------------------------------------------------------------
@- restoreTaskRegisters
@-
@- r0 = task pointer
@-
@--------------------------------------------------------------------
	.GLOBAL		restoreTaskRegisters
  .ALIGN
  .CODE 32
restoreTaskRegisters:

	@---->set registers r1-r12
	add r13, r0, #4
	ldmia r13!, {r1-r12}

	@ldr r1,  [r0, #4 ]
	@ldr r2,  [r0, #8 ]
	@ldr r3,  [r0, #12]
	@ldr r4,  [r0, #16]
	@ldr r5,  [r0, #20]
	@ldr r6,  [r0, #24]
	@ldr r7,  [r0, #28]
	@ldr r8,  [r0, #32]
	@ldr r9,  [r0, #36]
	@ldr r10, [r0, #40]
	@ldr r11, [r0, #44]		@fp
	@ldr r12, [r0, #48]   @ip

	@---->set sp
	ldr r13, [r0, #SP_OFFSET]

	@---->set cpsr
	ldr r14, [r0, #CPSR_OFFSET]
	msr	cpsr, r14

	@---->set lr
	ldr r14, [r0, #LR_OFFSET]

	@---->set r0 last
	ldr r0,  [r0]

	@---->branch to address
	bx	lr

	.END

