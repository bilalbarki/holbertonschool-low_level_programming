section .text
	global main

main:
	mov edx, no
	mov ecx, str
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov ebx, 0
	mov eax, 1
	int 0x80

section .data

str:	db "Hello, asm", 0xa
	no equ $-str
