;
; ArmExclusive.s (bug free version of LDREX and STREX)
;

                AREA    |.text|, CODE, READONLY

_LdrExW         PROC
                EXPORT  _LdrExW               [WEAK]
                LDREX   R1, [R0]
                MOV     R0, R1
                BX      LR
                ENDP

_LdrExH         PROC
                EXPORT  _LdrExH               [WEAK]
                LDREXH  R1, [R0]
                MOV     R0, R1
                BX      LR
                ENDP

_LdrExB         PROC
                EXPORT  _LdrExB               [WEAK]
                LDREXB  R1, [R0]
                MOV     R0, R1
                BX      LR
                ENDP

_StrExW         PROC
                EXPORT  _StrExW               [WEAK]
                STREX   R2, R1, [R0]
                MOV     R0, R2
                BX      LR
                ENDP

_StrExH         PROC
                EXPORT  _StrExH               [WEAK]
                STREX   R2, R1, [R0]
                MOV     R0, R2
                BX      LR
                ENDP

_StrExB         PROC
                EXPORT  _StrExB               [WEAK]
                STREX   R2, R1, [R0]
                MOV     R0, R2
                BX      LR
                ENDP

                END

