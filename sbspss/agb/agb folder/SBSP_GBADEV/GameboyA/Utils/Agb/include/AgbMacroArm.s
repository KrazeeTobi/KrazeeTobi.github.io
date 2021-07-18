;********************************************************************
;*          AgbMacroArm.s                                           *
;*            AGB Standard Macro Functions (ARMASM)                 *
;*                                                                  *
;*          Copyright (C) 1999-2000 Nintendo of America Inc.        *
;********************************************************************


;--------------------------------------------------------------------
;-                      System Call                                 -
;--------------------------------------------------------------------

    MACRO
        SystemCall16 $No
            swi    $No
    MEND
    MACRO
        SystemCall32 $No
            swi    $No <<  16
    MEND

    MACRO
        Halt                $Bits    ; HALT
            SystemCall$Bits 2
    MEND
    MACRO
        Stop                $Bits    ; STOP
            SystemCall$Bits 3
    MEND


	END

