TITLE Fibonacci sequence     (Project02.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 02                Date: 10/3/2016
; Description:  This program will introduce the programmer, print instructions,
;                  get user input, validate input, generate and print a
;                  fibonacci sequence, exit
;

INCLUDE Irvine32.inc

.data
messageTitle       BYTE  "            DWORD Fibonacci Sequence         by       Jeremy Prater", 0
messageEnterName   BYTE  "What is your name? ", 0
messageHello       BYTE  "Hello, ", 0
messageInstruction BYTE  "Enter a number between [1..46] and I'll show you the Fibonacci sequence", 0
messageGetSequence BYTE  "Enter the number of Fibonacci terms to display: ", 0
messageOutOfRange  BYTE  "Sorry, that number is out of range" ,0
messageVerified    BYTE  "Verified by Jeremy Prater" ,0
messageExit1       BYTE  "Good bye " ,0
messageExit2       BYTE  "!" ,0

messageTab         BYTE  "   ", 9, 0

messageEC1         BYTE  "** EC1: Display in aligned columns" ,0

storageName        BYTE 30 DUP (?) ; Memory to store user name
storageNameLength  DWORD ($-storageName)

fibacc             DWORD 1 ; Initial Term
columnNumber       DWORD 2

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
	
	; I tried to use QWORD for EC2, but the Irvine library can't print 64 bit integers.
	; I was going to use adc (add with carry) on QWORD memory addresses to add two 64 bit integers.

	;mov	edx, OFFSET messageEC2
	;call	WriteString
	;call	CrLf
	
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
    mov     edx, OFFSET messageInstruction
	call    WriteString
	call    CrLf

; Get sequence number
    mov     edx, OFFSET messageGetSequence
	call    WriteString
	call    ReadInt                        ; Result is in EAX

; Verify input is int the range [1..46]
	; Input number is in EAX
	cmp     eax, 1
	jl      SHOWINSTRUCTIONS
	cmp     eax, 46
	jg      SHOWINSTRUCTIONS
	jmp     INPUTPASSED

; show error and get new input
	mov     edx, OFFSET messageOutOfRange
	call    WriteString
	call    CrLf
	call    CrLf
	jmp     SHOWINSTRUCTIONS

INPUTPASSED:
; Display the Fibonacci sequence for the input
    
	; EAX already contains our sequence number
	; so move that to the loop counter

	mov     ecx, eax
	mov     eax, fibacc  ; Setup the initial Fibonacci counter
	mov     ebx, fibacc

	; Display the initial 2 terms

	; This is odd. Since we print the first two terms, and the first term
	; we calculate is actually the 3rd term, we need to subract two from
	; the sequence counter and politely exit.

	call    WriteDec
	mov     edx, OFFSET messageTab
	call    WriteString
    call    WriteString
	dec     ecx
	cmp     ecx, 0
	jle     GOODBYE

	call    WriteDec
	mov     edx, OFFSET messageTab
	call    WriteString
    call    WriteString
	dec     ecx
	cmp     ecx, 0
	jle     GOODBYE


FIBONACCIPRINT:
	mov     eax, fibacc  ; Get the Fibonacci counter
    add     eax, ebx     ; Add the current count to the total
	jo      GOODBYE      ; Overflow Occured!

	mov     fibacc, ebx  ; Update the Fibonacci counter
	mov     ebx, eax
	call    WriteDec

	cmp     eax, 10000   ; Add extra tab if column isn't wide enough
	jge     SKIPTAB2
	mov     edx, OFFSET messageTab
	call    WriteString

SKIPTAB2:
	mov     edx, OFFSET messageTab
	call    WriteString
	
; Add a line break every 5 columns
	inc    columnNumber
	mov    eax, columnNumber
	cmp    eax, 5
	jne    SKIPCRLF
	mov    eax, 0
	mov    columnNumber, eax
	call   CrLf

SKIPCRLF:
	loop FIBONACCIPRINT

GOODBYE:
; Show goodbye
	call    CrLf
	call    CrLf
	mov     edx, OFFSET messageVerified
	call    WriteString
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
