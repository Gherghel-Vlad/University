bits 32 
; testing one
extern _fopen
extern _fprintf

 

global _determine_minimum_from_array

 

global _write_number_in_file

 

segment data public data use32
    
    minimumNumber dw 0
    fileName db "min.txt", 0
    number dd 0
    fileDescriptor dd 0
    writeMode db "w", 0
    formatNumber db "%x", 0

 


segment code public code use32

 

    _determine_minimum_from_array:
        
        push EBP ; create the stack frame
        mov EBP, ESP
        
        mov eax, 0 ; clear EAX
        
        ; [EBP] will have the caller's EBP
        ; [EBP+4] will have the return address
        ; [EBP+8] will have the address of my array
        ; [EBP + 12] the length of my arrray
        
        mov ECX, [EBP+12] ; for the loop
        
        mov EBX, [EBP+8] ; EBX stores the array
        
        jecxz Done 
        
        mov EAX, 0
        mov AX, [EBX]
        mov [minimumNumber], AX
        
        sub ECX, 1
        
        jecxz DoneMinimum
        
        repeat1:
            
            add EBX, 4 ; iterate through the array
            mov AX, [EBX]
            
            cmp AX, word [minimumNumber] ; if the number is less than minim save it as minim
            jge NoNewMinimumNumber
            
            mov [minimumNumber], AX
            
            NoNewMinimumNumber:
        
        loop repeat1
        
        
        DoneMinimum:
        mov EAX, 0
        mov AX, [minimumNumber]
        
        
        Done:
        mov ESP, EBP ; clears the stack frame we created in the begining
        pop EBP
        
    ret

 

    _write_number_in_file:
        
        
        push EBP ; creating stack frame
        mov EBP, ESP
        
        mov EAX, [EBP+8] ; stores the number in EAX
        mov [number], EAX
        
        push dword writeMode ; opens file in write mode
        push dword fileName
        call _fopen
        add ESP, 4*2
        
        mov [fileDescriptor], EAX ; saves the descriptor in EAX
        
        push dword [number] ; prints the number in te file
        push dword formatNumber
        push dword [fileDescriptor]
        call _fprintf
        add ESP, 4*3
        
        mov ESP, EBP ; clears the stack frame we created in the begining
        pop EBP
        
    ret