MOV AL, 1
MOV a, AL
MOV AL, 1
MOV b, AL
MOV AL, 3
MOV c, AL
WHILELABEL1: 
MOV AL, c
MOV BL, 0
XCHG AL, BL
XCHG AL, BL
CMP AL, BL
JLE LABEL1
MOV BL, c
XCHG AL, BL
MOV AL, b
MUL AL
XCHG AL, BL
MOV b, BL
MOV BL, c
XCHG AL, BL
XCHG AL, BL
MOV AL, 1
SUB BL, AL
MOV c, BL
JMP WHILELABEL1
LABEL1: 
