.text
	.global textchanger
	
textchanger:
	mov eax,ebp+8
	mov [eax],'h'