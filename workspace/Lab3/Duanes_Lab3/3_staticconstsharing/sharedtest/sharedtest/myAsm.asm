
.global _textchanger
	
_textchanger:
	mov eax,ebp+8
	mov [eax],'h'