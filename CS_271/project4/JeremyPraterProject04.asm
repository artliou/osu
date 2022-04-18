TITLE Composite Numbers (Project04.asm)

; Author: Jeremy Prater
; Course / Project ID : CS-271 / Project 04                Date: 11/06/2016
; Description:  Write a program to calculate composite numbers. First, the user is
; instructed to enter the number of composites to be displayed, and is prompted to
; enter an integer in the range [1,400]
;
; The range has been extended to [1, 300000] allow for pausing of the printed output
;

INCLUDE Irvine32.inc

.data
messageTitle        BYTE  "            Composite Numbers         by       Jeremy Prater", 0
messageEC1          BYTE  "** EC1: Align output columns." ,0
messageEC2          BYTE  "** EC2: Display more composites, but show them one page at a time.", 0

messageEnterName    BYTE  "What is your name? ", 0
messageHello        BYTE  "Hello, ", 0

messageInstruction1 BYTE  "Enter the number of composite numbers you would like to see.", 0
messageInstruction2 BYTE  "The maximum number of composites to display is 300000.", 0

messageGetNumber    BYTE  "Enter the number number of composites to display [1, 300000] : ", 0
messageRangeError   BYTE  " is out of range. Try again.", 0

messageExit1        BYTE  "Assembly language is pretty powerful.", 0
messageExit2        BYTE  "I should make a real-time thread scheduler!" ,0
messageExit3        BYTE  "Good bye ", 0
messageExit4        BYTE  "!" ,0

messageSpace        BYTE  " " ,0

storageName         BYTE 30 DUP (?) ; Memory to store user name
storageNameLength   DWORD ($-storageName)

maxUserInput        DWORD 300000
columnNumber        DWORD 0
rowNumber           BYTE  0
cNumbersFound       DWORD 0

.code

;--------------------------------------------------------
;
; Display the introduction
;
;--------------------------------------------------------

displayIntro PROC
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
	ret
displayIntro ENDP

;--------------------------------------------------------
;
; Get and print the user name
;
;--------------------------------------------------------

getUsername PROC
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

	ret
getUsername ENDP

;--------------------------------------------------------
;
; Display the instructions for the application
;
;--------------------------------------------------------

displayInstructions PROC
	; Display instructions

    mov     edx, OFFSET messageInstruction1
	call    WriteString
	call    CrLf

    mov     edx, OFFSET messageInstruction2
	call    WriteString
	call    CrLf

	ret
displayInstructions ENDP

;--------------------------------------------------------
;
; Get user input
;
;--------------------------------------------------------

getInput PROC

USERINPUT:
    mov     edx, OFFSET messageGetNumber
	call    WriteString
	call    ReadInt                        ; Result is in EAX

	; Check input and return to start if it is out of range
	cmp     eax, 1
	jl      INPUTINVALID
	cmp     eax, maxUserInput
	jg      INPUTINVALID

	; The input is valid
	jmp     INPUTVALID

INPUTINVALID:
	; The invalid number is in eax, print the error and return to the start of user input
    call    WriteDec
	mov     edx, OFFSET messageRangeError
	call    WriteString
	call    CrLf
	jmp     GETINPUT
	
INPUTVALID:
	ret
getInput ENDP

;--------------------------------------------------------
;
; Display the exit text for the application
;
;--------------------------------------------------------

displayExit PROC
; Show goodbye
	call    CrLf
	call    CrLf
	mov     edx, OFFSET messageExit1
	call    WriteString
	call    CrLf
	mov     edx, OFFSET messageExit2
	call    WriteString
	call    CrLf
	mov     edx, OFFSET messageExit3
	call    WriteString
	mov     edx, OFFSET storageName
	call    WriteString
	mov     edx, OFFSET messageExit4
	call    WriteString
	call    CrLf
	ret
displayExit ENDP

;--------------------------------------------------------
;
; Pause the output and wait for user input
;
;--------------------------------------------------------

PauseOutput PROC
	call CrLf
	call WaitMsg
	call CrLf
	call CrLf
	ret
PauseOutput ENDP

;--------------------------------------------------------
;
; Display spaces based on the size of the number
;
;--------------------------------------------------------

WriteColumnSpaces PROC
	mov     edx, OFFSET messageSpace

	;cmp     eax, 1000000
	;jge     COLUMNSPACE1
	;call    WriteString

;COLUMNSPACE1:
	cmp     eax, 100000
	jge     COLUMNSPACE2
	call    WriteString

COLUMNSPACE2:
	cmp     eax, 10000
	jge     COLUMNSPACE3
	call    WriteString

COLUMNSPACE3:
	cmp     eax, 1000
	jge     COLUMNSPACE4
	call    WriteString

COLUMNSPACE4:
	cmp     eax, 100
	jge     COLUMNSPACE5
	call    WriteString

COLUMNSPACE5:
	cmp     eax, 10
	jge     COLUMNSPACE6
	call    WriteString

COLUMNSPACE6:
	call    WriteString
	ret
WriteColumnSpaces ENDP

;--------------------------------------------------------
;
; Entry point for displaying composite numbers
;
;--------------------------------------------------------

showComposites PROC
	mov  ecx, eax ; Move the user value into the loop counter
	mov  eax, 2

COMPOSITELOOP:
	push ecx
	call isComposite ; This function modifies ECX
	pop  ecx
	inc eax
	cmp cNumbersFound, ecx
	jne COMPOSITELOOP

	ret
showComposites ENDP

;--------------------------------------------------------
;
; A function to print a single number as a composite
;
;--------------------------------------------------------

isComposite PROC
	; EAX contains the number to check as a composite
	mov    ecx, eax ; Setup loop counter
	dec    ecx      ; We don't want to divide by it's self, so reduce count by one

	mov    ebx, eax ; EBX will contain the original number
COMPOSITECHECKLOOP:
	cmp   ecx, 1    ; 1 is not a composite number
	je    NOTCOMPOSITE

	mov    eax, ebx ; Restore the original number into eax
	mov    edx, 0   ; Clear edx
	div    ecx      ; Divide by the loop counter
	cmp    edx, 0   ; If there is no remainder, then this is a composite number
	jne    NOTCOMPOSITE

	mov    edx, cNumbersFound
	inc    edx
	mov    cNumbersFound, edx

	mov    eax, ebx ; Restore the original number into eax
	call   WriteColumnSpaces
	call   WriteDec

	mov    eax, columnNumber
	inc    eax
	mov    columnNumber, eax

	; We have printed 10 numbers, so do a CrLf
	cmp    eax, 10
	jne    COMPOSITECOLUMN
	mov    columnNumber, 0
	call   CrLf

	; Pause the print out and display message if we have hit the console size
	
	mov    eax, 0
	mov    al, rowNumber
	inc    al
	mov    rowNumber, al
	call   GetMaxXY
	cmp    rowNumber, dh
	jne    COMPOSITECOLUMN
	
	mov    rowNumber, 0
	call   PauseOutput

COMPOSITECOLUMN:

	mov    eax, ebx ; Restore the original number into eax
	ret             ; Exit the procedure now that we found the composite number

NOTCOMPOSITE:
	loop COMPOSITECHECKLOOP
	mov    eax, ebx ; Restore the original number into eax
	ret
isComposite ENDP

;--------------------------------------------------------
;
; Program entry point
;
;--------------------------------------------------------

main PROC
	
	call displayIntro
	call getUsername
	call displayInstructions
	call getInput
	call showComposites

	call displayExit
	exit	; exit to operating system
main ENDP

END main
