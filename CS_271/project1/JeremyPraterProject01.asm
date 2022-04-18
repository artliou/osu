TITLE Elementary Arithemic     (Project01.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 01                Date: 9/21/2016
; Description:  This program will introduce the programmer, and project name,
;               get input from user, calculate output values, print results,
;               display exit message.
;
; Write and test a MASM program to perform the following tasks:
; 1. Display your name and program title on the output screen.
; 2. Display instructions for the user.
; 3. Prompt the user to enter two numbers.
; 4. Calculate the sum, difference, product, (integer) quotient and remainder of the numbers.
; 5. Display a terminating message. 

INCLUDE Irvine32.inc

.data
messageTitle       BYTE  "              Mostly Elementary Arithmetc            by       Jeremy Prater" ,0
messageInstruction BYTE  "Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder." ,0
messageFirstNum    BYTE  "Enter First Number (q to quit): " ,0
messageSecondNum   BYTE  "Enter Second Number: " ,0
messageDivideByZ   BYTE  "ERROR: You can not : -- DIVIDE BY ZERO --" ,0
messageExit        BYTE  "x86 Assembly is pretty cool, eh? Bye!" ,0

messageLessthan    BYTE  "The second input must be less than or equal to the first!!" ,0

messageEC1         BYTE  "** EC1: Repeat until the user chooses to quit" ,0
messageEC2         BYTE  "** EC2: Validate the second number to be less than the first" ,0
messageEC3         BYTE  "** EC3: Calculate and display the quotient as a floating point number, rounded to nearest .001" ,0
messageEC4         BYTE  "** EC4: Catch divide by zero :)" ,0

mathAdd            BYTE  " + " ,0
mathSub            BYTE  " - " ,0
mathMul            BYTE  " * " ,0
mathDiv            BYTE  " / " ,0
mathEqual          BYTE  " = " ,0
mathRemainder      BYTE  " remainder " ,0

inputFirstNum      DWORD ?       ; first integer entered by user
inputSecondNum     DWORD ?       ; second integer entered by user

storageAddResult   DWORD ?       ; Memory to store the add result
storageSubResult   DWORD ?       ; Memory to store the sub result
storageMulResult   DWORD ?       ; Memory to store the mul result
storageDivResult   DWORD ?       ; Memory to store the div result
storageDivRem      DWORD ?       ; Memory to store the div remainder

primaryInput       BYTE 30 DUP (?); Memory to check if we are quitting
primaryInputLength DWORD ($-primaryInput)

FloatRounder       WORD 1000     ; This is actually 1/1000 = .001. Used for float rounding

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

	mov		edx, OFFSET messageEC2
	call	WriteString
	call	CrLf

	mov		edx, OFFSET messageEC3
	call	WriteString
	call	CrLf

	mov		edx, OFFSET messageEC4
	call	WriteString
	call	CrLf
	call	CrLf

; Main loop
MAINLOOP:

; get the data
	mov		edx, OFFSET messageInstruction
	call	WriteString
	call	CrLf

	mov		edx, OFFSET messageFirstNum
	call	WriteString

	mov		edx, OFFSET primaryInput
	mov		ecx, primaryInputLength
	call	ReadString

; Check if we should exit now
    MOV     AL, primaryInput
	CMP     AL, 'q'
	JE      USEREXIT

; Continue processing

	; Convert string to integer!
	mov		edx, OFFSET primaryInput
	mov		ecx, primaryInputLength
	call    ParseInteger32
	mov		inputFirstNum, eax

	; Continue with user data
	mov		edx, OFFSET messageSecondNum
	call	WriteString

	call	ReadInt
	mov		inputSecondNum, eax

; Check if inputSecondNum < inputFirstNum
	; Second num is already in EAX
	CMP     EAX, inputFirstNum
	JLE     INPUTPASSED     ; User input is ok, jump to calculations

	; Tell user to fix input and try again!
	; This should be allowed with floating point division. IE: 3/4 = .75
	; But it's extra credit!
	mov		edx, OFFSET messageLessthan
	call	WriteString
	call	CrLf
	call	CrLf
	JMP MAINLOOP

; calculate the required values
INPUTPASSED:
	; Preform addition
	mov		eax, inputFirstNum
	add     eax, inputSecondNum
	mov     storageAddResult, eax
	
	; Preform subtraction
	mov		eax, inputFirstNum
	sub     eax, inputSecondNum
	mov     storageSubResult, eax
	
	; Preform mul
	mov		eax, inputFirstNum
	mul     inputSecondNum
	mov     storageMulResult, eax

	; Check for div/0
	mov		eax, inputFirstNum
	cmp     inputSecondNum ,0    ; Check operand 2 for zero - prevent division by zero error
	je      DISPLAYRESULTS
	
	; Preform integer division
	div     inputSecondNum
	mov     storageDivResult, eax
	mov     storageDivRem   , edx

	; Preform floating point division
	fild    inputFirstNum    ; Load first operand into ST(0) Convert DWORD->REAL
	fidiv   inputSecondNum   ; Loadn and divide first/second and store result in ST(0)
	fimul   FloatRounder     ; Multiply ST(0) by 1000
	frndint                  ; Round the float number to integer
	fidiv   FloatRounder     ; Divide ST(0) by 1000 (round to .001)

DISPLAYRESULTS:
; display the results

	; Print addition
	mov     eax, inputFirstNum
	call    WriteInt
	mov		edx, OFFSET mathAdd
	call	WriteString
	mov     eax, inputSecondNum
	call    WriteInt
	mov		edx, OFFSET mathEqual
	call	WriteString
	mov     eax, storageAddResult
	call    WriteInt
	call    CrLf

	; Print subtraction
	mov     eax, inputFirstNum
	call    WriteInt
	mov		edx, OFFSET mathSub
	call	WriteString
	mov     eax, inputSecondNum
	call    WriteInt
	mov		edx, OFFSET mathEqual
	call	WriteString
	mov     eax, storageSubResult
	call    WriteInt
	call    CrLf

	; Print mul
	mov     eax, inputFirstNum
	call    WriteInt
	mov		edx, OFFSET mathMul
	call	WriteString
	mov     eax, inputSecondNum
	call    WriteInt
	mov		edx, OFFSET mathEqual
	call	WriteString
	mov     eax, storageMulResult
	call    WriteInt
	call    CrLf

	; Check for zero in second operand
	CMP    inputSecondNum, 0
	JNE    SHOWDIVISON  ; The second operand is not zero!

	mov		edx, OFFSET messageDivideByZ     ; Print dov/0 error!!
	call	WriteString
	call	CrLf
	call	CrLf

	JMP    MAINLOOP

SHOWDIVISON:
	; Print division
	mov     eax, inputFirstNum
	call    WriteInt
	mov		edx, OFFSET mathDiv
	call	WriteString
	mov     eax, inputSecondNum
	call    WriteInt
	mov		edx, OFFSET mathEqual
	call	WriteString
	mov     eax, storageDivResult
	call    WriteInt
	mov		edx, OFFSET mathRemainder
	call	WriteString
	mov     eax, storageDivRem
	call    WriteInt
	call    CrLf

	; Print floating point division
	mov     eax, inputFirstNum
	call    WriteInt
	mov		edx, OFFSET mathDiv
	call	WriteString
	mov     eax, inputSecondNum
	call    WriteInt
	mov		edx, OFFSET mathEqual
	call	WriteString
	call    WriteFloat       ; The result is already in ST(0)
	call    CrLf


; return to main loop (this should be a procedure!)
	JMP     MAINLOOP

USEREXIT:
; say goodbye 
	mov		edx, OFFSET messageExit
	call	WriteString
	call	CrLf
	call	CrLf

	exit	; exit to operating system
main ENDP

END main


