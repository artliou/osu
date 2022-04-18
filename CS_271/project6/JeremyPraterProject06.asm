TITLE Low Level IO (Project06.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 06                Date: 11/30/2016
; Description:  
;

INCLUDE Irvine32.inc

.data
messageTitle        BYTE  "       Low-level I/O Proc and Macro      by       Jeremy Prater", 0
messageEC1          BYTE  " -- NO EC this week. Getting ready for the holidays." ,0

messageIntro1       BYTE  "Please enter 10 unsigned integers", 0
messageIntro2       BYTE  "Please enter numbers less than max uint32.", 0
messageIntro3       BYTE  "Once all numbers are entered, the sum and average will be displayed.", 0

messageUserGetCount BYTE  "Please enter a 32 bit unsigned integer : ", 0
messageUserInvalid  BYTE  "ERROR : Invalid number.", 0
messageNumberArray  BYTE  "You entered the following numbers:", 0
messageNumberSep    BYTE  ", ", 0
messageNumberSum    BYTE  "The sum of the numbers is : ", 0
messageNumberAvg    BYTE  "The average of the numbers is : ", 0
messsageGoodBye     BYTE  "Thanks for playing!", 0

userString          BYTE  (32) DUP (?)
userData            DWORD (10) DUP (?)
userSum             DWORD 0

.code

;--------------------------------------------------------
;
; MACRO : getString
;         Read a string from the user input
;
; PARAMETERS : memory address to store number
;
;--------------------------------------------------------

getString MACRO buffer
	push ecx
	push edx
	mov  edx, OFFSET buffer
	mov  ecx, (SIZEOF buffer)-1
	call ReadString
	pop  edx
	pop  ecx
ENDM

;--------------------------------------------------------
;
; MACRO : displayString
;         Write a string to the console
;
; PARAMETERS : OFFSET mem - memory address of the string to write
;              BOOL (0/1) - Print CrLf
;
;--------------------------------------------------------

displayString MACRO buffer, eol
	LOCAL NOCRLF

	push edx
	mov  edx, OFFSET buffer
	call WriteString
	push eax
	mov  eax, eol
	cmp  eax, 0
	je   NOCRLF
	call CrLf
NOCRLF:
	pop  eax
	pop  edx
ENDM

;--------------------------------------------------------
;
; PROCEDURE : displayIntro
;             Display the introduction
;
; PARAMETERS : None
;
;--------------------------------------------------------

displayIntro PROC
; introduction
	displayString  messageTitle, 1
	call	CrLf

; Display extra credit information
	displayString messageEC1, 1
	call	CrLf
	ret
displayIntro ENDP

;--------------------------------------------------------
;
; PROCEDURE : displayInstructions
;             Display the instructions for the application
;
; PARAMETERS : None
;
;--------------------------------------------------------

displayInstructions PROC
	; Display instructions
    displayString messageIntro1, 1
    displayString messageIntro2, 1
    displayString messageIntro3, 1
	ret
displayInstructions ENDP

;--------------------------------------------------------
;
; PROCEDURE : ReadVal
;             Read unsigned integer from input into register
;
; -- Uses getString Macro to get input string
; PARAMETERS : Memory address to store converted string integer
;
;--------------------------------------------------------

ReadVal PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer
	push    eax
	push    ebx
	push    ecx
	push    edx

START:
	displayString messageUserGetCount ,0
	getString     userString
	; EAX contains string length

	cmp    eax, 11
	jg     INPUTFAIL
    mov    ecx, eax
	mov    esi, OFFSET userString
	mov    edx, [ebp+8]
	mov    eax, 0
	mov    [edx], eax
	

PROCESSINPUT:
	mov    eax, 0
	lodsb
	sub    eax, 30h
	cmp    eax, 10
	jae    INPUTFAIL
	; eax contains the decimal number at the current 10's position defined by ecx

	; Setup and multiply current number by the base-10 position
	push   ecx
	push   eax
	mov    eax, 1
	mov    ebx, 10
	dec    ecx ; Decrease the 10's place by 1
	cmp    ecx, 0 ; Check if it is the last place
	je     TENMULDONE
TENMUL:
	mul    ebx
	loop   TENMUL
TENMULDONE:
	mov    ebx, eax
	pop    eax
	pop    ecx
	; The base-10 multiplier is in ebx (1,10,100,1000,etc...)
	mul    ebx
	JC INPUTFAIL
	JO INPUTFAIL

	; Copy new value into memory
	mov    edx, [ebp+8]
	mov    edx, [edx]
	add    edx, eax
	JC INPUTFAIL
	JO INPUTFAIL
	push   ecx
	mov    ecx, [ebp+8]
	mov    [ecx], edx
	pop    ecx
	
	loop   PROCESSINPUT	
	jmp    INPUTPASS

INPUTFAIL:
	displayString messageUserInvalid, 1
	jmp    START

INPUTPASS:
	pop    edx
	pop    ecx
	pop    ebx
	pop    eax
	pop    esp
	ret    4 ; Discard stack storage
ReadVal ENDP

;--------------------------------------------------------
;
; PROCEDURE : WriteVal
;             Write unsigned integer from register to output
;
; -- Uses displayString Macro to output the value
; PARAMETERS : None
;
;--------------------------------------------------------

WriteVal PROC
	push    esp      ; Save stack pointer
	mov     ebp, esp ; copy stack into base pointer
	push    eax
	push    ebx
	push    ecx
	push    edx
	
	; IMPORTANT! Allocate space on the stack to store
	; local variable if we have printed a non-zero number
	; This is to delete leading zeros and determine if the
	; actual number is zero
	sub     esp, 4
	mov     BYTE PTR [ebp - 4], 0

START:
	mov    edi, OFFSET userString
	mov    edx, 0
	mov    ecx, 10
	mov    eax, [ebp+8]
	mov    eax, [eax]

DIVIDETENS:

	; Setup and multiply current number by the base-10 position
	push   ecx
	push   eax
	mov    eax, 1
	mov    ebx, 10
	dec    ecx ; Decrease the 10's place by 1
	cmp    ecx, 0 ; Check if it is the last place
	je     TENMULDONE
TENMUL:
	mul    ebx
	loop   TENMUL
TENMULDONE:
	mov    ebx, eax
	pop    eax
	pop    ecx
	; The base-10 multiplier is in ebx (1,10,100,1000,etc...)
	push   eax
	mov    edx, 0
	div    ebx

	cmp    BYTE PTR [ebp - 4], 0
	jne    STOREDATA
	cmp    eax, 0
	je     SKIPZERO
	mov    BYTE PTR [ebp - 4], 1

STOREDATA:
	add    eax, 30h
	stosb
	sub    eax, 30h
	mul    ebx
	mov    ebx, eax	
	jmp    CONTINUEZERO

SKIPZERO:
	mov    ebx, 0

CONTINUEZERO:
	pop    eax
	sub    eax, ebx
	loop   DIVIDETENS

	; Check if we ever stored any data (the number could be zero)
	cmp    BYTE PTR [ebp - 4], 0
	jne    DATAVALID
	; Add a zero
	mov    eax, 30h
	stosb

DATAVALID:
	; Add trailing null
	mov    eax, 00h
	stosb
	displayString userString, 0
	pop    eax
	pop    edx
	pop    ecx
	pop    ebx
	pop    eax
	pop    esp
	ret    4 ; Discard stack storage
WriteVal ENDP

;--------------------------------------------------------
;
; Program entry point
;
;--------------------------------------------------------

main PROC
	
	call displayIntro
	call displayInstructions
	mov  ecx, 10

GETUSERDATA:
	; Setup array position into eax
	mov  eax, ecx
	dec  eax
	imul eax, 4
	add  eax, OFFSET userData
	; Call read value to populate userData
	push eax
	call ReadVal
	loop GETUSERDATA

	call CrLf
	displayString messageNumberArray, 1

	mov  ecx, 10
PRINTUSERDATA:
	; Setup array position into eax
	mov  eax, ecx
	dec  eax
	imul eax, 4
	add  eax, OFFSET userData
	; Call read value to populate userData
	push eax
	call WriteVal

	cmp  ecx, 1
	je NOCOMMA

	displayString messageNumberSep, 0

NOCOMMA:
	inc  ebx
	loop PRINTUSERDATA

	call CrLf

	; Print sum of numbers
	mov  ecx, 10
	mov  ebx, 0
SUMUSERDATA:
	; Setup array position into eax
	mov  eax, ecx
	dec  eax
	imul eax, 4
	add  eax, OFFSET userData
	mov  eax, [eax]
	add  ebx, eax
	loop SUMUSERDATA
	mov  ecx, OFFSET userSum
	mov  [ecx], ebx
	; Display the sum of the numbers
	call CrLf
	displayString messageNumberSum, 0
	push ecx
	call WriteVal
	call CrLf
	; Load the sum data into registers
	mov  ecx, OFFSET userSum
	mov  eax, [ecx]
	mov  edx, 0
	mov  ebx, 10
	div  ebx
	mov  ecx, OFFSET userSum
	mov  [ecx], eax

	; Print division average
	displayString messageNumberAvg, 0
	push ecx
	call WriteVal
	call CrLf
	call CrLf

	displayString messsageGoodBye, 1

	exit	; exit to operating system
main ENDP

END main
