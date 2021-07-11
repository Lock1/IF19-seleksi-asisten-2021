; Rigged-NIM game inspired by Matt Parker :)
global _start



section .text
_start:
    call      _main

    mov       rax, 60        ; system call for exit
    mov       rdi, 0         ; exit code 0
    syscall                  ; invoke syscall to exit



; input
_bgets:
    push      rax
    push      rdx
    push      rsi
    push      rdi

    mov       rdx, rsi      ; Byte count
    mov       rsi, rdi      ; Buffer address
    mov       rax, 0        ; Syscall for read
    mov       rdi, 0        ; File descriptor
    syscall

    pop       rdi
    pop       rsi
    pop       rdx
    pop       rax
    ret

; output
_bputs:
    push      rax
    push      rdx
    push      rsi
    push      rdi

    mov       rdx, rsi      ; Byte count
    mov       rsi, rdi      ; Buffer to write
    mov       rax, 1        ; Syscall for write
    mov       rdi, 1        ; File descriptor
    syscall

    pop       rdi
    pop       rsi
    pop       rdx
    pop       rax
    ret





_main:
    mov       rbp, rsp
    sub       rsp, 0x10
    mov       byte [rsp], '8'
    mov       rbx, 8            ; rbx -> c_counter

    mov       rbp, 0x10

    mov       rdi, starting_message
    mov       rsi, 40
    call      _bputs


_gameloop:
    mov       rdi, coin_message
    mov       rsi, 12
    call      _bputs

    ; puts(char_c_counter)
    lea       rdi, [rsp]
    mov       rsi, 1
    call      _bputs

    ; puts("\n")
    mov       rdi, new_line
    mov       rsi, 1
    call      _bputs

    ; puts()
    mov       rdi, input_message
    mov       rsi, 17
    call      _bputs


    ; fgets(stdin, s, 2);
    lea       rdi, [rsp+1]
    mov       rsi, 2               ; Number + Newline
    call      _bgets

    sub       byte [rsp+1], 48     ; ASCII numeric to actual number
    movzx     r8, byte [rsp+1]     ; Zero extend 1 byte to 8 byte register
    sub       rbx, r8
    lea       rax, [rbx+48]
    mov       [rsp], rax           ; char_c_counter = (char) c_counter

    ; puts("\n");
    mov       rdi, new_line
    mov       rsi, 1
    call      _bputs


    ; bot section
    cmp       r8, 1
    jne       _user_take_2

    sub       rbx, 3 ; c_counter -= 3
    sub       byte [rsp], 3

    ; puts()
    mov       rdi, bot_t_3
    mov       rsi, 15
    call      _bputs

    ; puts("\n")
    mov       rdi, new_line
    mov       rsi, 1
    call      _bputs

    jmp       _exitloop_cmp
_user_take_2:
    cmp       r8, 2
    jne       _user_take_3

    sub       rbx, 2 ; c_counter -= 2
    sub       byte [rsp], 2

    ; puts()
    mov       rdi, bot_t_2
    mov       rsi, 15
    call      _bputs

    ; puts("\n")
    mov       rdi, new_line
    mov       rsi, 1
    call      _bputs

    jmp       _exitloop_cmp
_user_take_3:
    sub       rbx, 1 ; c_counter -= 1
    sub       byte [rsp], 1

    ; puts()
    mov       rdi, bot_t_1
    mov       rsi, 15
    call      _bputs

    ; puts("\n")
    mov       rdi, new_line
    mov       rsi, 1
    call      _bputs



_exitloop_cmp:
    cmp       bx, 0
    jg        _gameloop

    ; out from gameloop
    add       rsp, 0x10

    ; puts()
    mov       rdi, lose_message
    mov       rsi, 13
    call      _bputs

    ; puts("\n")
    mov       rdi, new_line
    mov       rsi, 1
    call      _bputs
    ret





section .data
starting_message:
    db        "Pengambil koin terakhir adalah pemenang", 10

coin_message:
    db        "Sisa koin : "

input_message:
    db        "Ambil (1, 2, 3): "

bot_t_1:
    db        "Bot mengambil 1"

bot_t_2:
    db        "Bot mengambil 2"

bot_t_3:
    db        "Bot mengambil 3"

lose_message:
    db        "Anda kalah :)"

new_line:
    db        10
