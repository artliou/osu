TITLE Integer Accumulator (Project03.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 03                Date: 10/25/2016
; Description:  This program will introduce the programmer, print instructions,
;                  get user input, validate input, generate and print a
;                  fibonacci sequence, exit
;

INCLUDE Irvine32.inc

.data
messageTitle        BYTE  "            Integer Accumulator         by       Jeremy Prater", 0
messageEnterName    BYTE  "What is your name? ", 0
messageHello        BYTE  "Hello, ", 0
messageInstruction1 BYTE  "Enter a numbers between [-100,-1].", 0
messageInstruction2 BYTE  "Enter a positive number to exit.", 0
messageGetNumber    BYTE  ": Enter a number : ", 0
messageNumberRange  BYTE  " is out of range.", 0
messageTotal1       BYTE  "You entered " ,0
messageTotal2       BYTE  " valid numbers." ,0
messageSum          BYTE  "The sum of valid negative integers is : " ,0
messageAvgInt       BYTE  "The integer average of the valid negative integers is : ", 0
messageAvgFloat     BYTE  "The floating point average of the valid negative integers is : ", 0
messageExit1        BYTE  "Good bye " ,0
messageExit2        BYTE  "!" ,0

messageEC1          BYTE  "** EC1: Number the lines during user input." ,0
messageEC2          BYTE  "** EC2: Calculate and display the average in floating point to the nearest .001", 0

storageName         BYTE 30 DUP (?) ; Memory to store user name
storageNameLength   DWORD ($-storageName)


FloatRounder       WORD 1000     ; This is actually 1/1000 = .001. Used for float rounding
FloatDividend      DWORD ?       ; first integer entered by user
FloatDivisor       DWORD ?       ; second integer entered by user

.code
main PROC

;Main procedure requirements
; introduction
	mov		edx, OFFSET messageTitle
	call	WriteString
	call	CrLf
	call	CrLf

; Display extra credit information
	mov		edx, OFFSET messageEC1
	call	WriteString
	call	CrLf
	mov	edx, OFFSET messageEC2
	call	WriteString
	call	CrLf
	call	CrLf

; Get the user name
	mov		edx, OFFSET messageEnterName
	call	WriteString
	mov		edx, OFFSET storageName
	mov		ecx, storageNameLength
	call	ReadString

; Display the username
	mov     edx, OFFSET messageHello
	call    WriteString
	mov     edx, OFFSET storageName
	call    WriteString
	call    CrLf

SHOWINSTRUCTIONS:

; Display instructions
    mov     edx, OFFSET messageInstruction1
	call    WriteString
	call    CrLf

    mov     edx, OFFSET messageInstruction2
	call    WriteString
	call    CrLf

	; Setup the Accumulator and Counter
	mov     ebx, 0 ; This is the accumulator
	mov     ecx, 0 ; This is the counter

NEXTINPUT:

; Get integer input
    mov     eax, ecx ; Move the counter into eax
	inc     eax      ; Add one for the user count
	call    WriteDec
    mov     edx, OFFSET messageGetNumber
	call    WriteString
	call    ReadInt                        ; Result is in EAX

; Verify input is int the range [-100, -1]
	; Input number is in EAX
	cmp      eax, 0
	jge      CALCRESULTS
	cmp      eax, -100
	jge      ACCUMULATEINT

	; The input is below -100 and above -1
	; Print error and return to input
    call     WriteInt
	mov      edx, OFFSET messageNumberRange
	call     WriteString
	call     CrLf
	jmp      NEXTINPUT
	
	;jl      SHOWINSTRUCTIONS
	;cmp     eax, 46
	;jg      SHOWINSTRUCTIONS
ACCUMULATEINT:
	
	; Input is valid
	; eax contains the user input
	; ebx is the accumulator
	; ecx is the counter

	add      ebx, eax
	inc      ecx
	jmp      NEXTINPUT

CALCRESULTS:
	; ebx contains the integer accumulator
	; ecx contains the counter

	; Print the total sum
	mov      edx, OFFSET messageSum
	call     WriteString
	mov      eax, ebx
	call     WriteInt
	call     CrLf

	; Print the integer average
	; Move total into EAX
	mov      eax, ebx
	; Sign extend into EDX
	cdq
	; Preform signed division into eax:edx
	idiv     ecx
	; Print result from EAX
	; We discard the remainder at this point by loading a string offset into EDX
	mov     edx, OFFSET messageAvgInt
	call    WriteString
	call    WriteInt
	call    CrLf

	; Now print the floating point answer
	; EBX - sum
	; ECX - counter
	; Preform floating point division
	mov     FloatDividend, ebx
	mov     FloatDivisor, ecx
	fild    FloatDividend    ; Load first operand into ST(0) Convert DWORD->REAL
	fidiv   FloatDivisor     ; Loadn and divide first/second and store result in ST(0)
	fimul   FloatRounder     ; Multiply ST(0) by 1000
	frndint                  ; Round the float number to integer
	fidiv   FloatRounder     ; Divide ST(0) by 1000 (round to .001)

	; Print float division messsage and result
	mov     edx, OFFSET messageAvgFloat
	call    WriteString
	call    WriteFloat
	call    CrLf


GOODBYE:
; Show goodbye
	call    CrLf
	call    CrLf
	mov     edx, OFFSET messageExit1
	call    WriteString
	mov     edx, OFFSET storageName
	call    WriteString
	mov     edx, OFFSET messageExit2
	call    WriteString
	call    CrLf

	exit	; exit to operating system
main ENDP

END main
