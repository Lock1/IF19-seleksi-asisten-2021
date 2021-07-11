// Low-level calculator
// Semua fungsi selain static inline dan main(), merupakan prosedur void
// Fungsi static inline mengembalikan hasil operasi boolean yang ditujukan
//      untuk mengurangi clutter pada source code, tidak bertujuan untuk melanggar
//      konstrain "... (termasuk pembuatan method yang mengembalikan nilai)"
// Program menggunakan 6 register dan tidak mengimplementasikan akar, modulo, dan pangkat

// Ketentuan register umum
// r1 digunakan sebagai akumulator
// r2 digunakan sebagai penyimpan 1 bilangan sementara
// r3 & r4 direserve untuk kepentingan counter operasi aritmatika
// r5 digunakan sebagai 1 digit sementara pada parsing
// r6 digunakan sebagai penyimpanan operator pada parsing

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int bit1 : 1;
    unsigned int bit2 : 1;
    unsigned int bit3 : 1;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6 : 1;
    unsigned int bit7 : 1;
    unsigned int bit8 : 1;
} reg;

reg reg1;
reg reg2;
reg reg3;
reg reg4;
reg reg5;
reg reg6;





// Fungsi pembantu
void print_binary_reg(reg *r1) {
    printf("%d", r1->bit8);
    printf("%d", r1->bit7);
    printf("%d", r1->bit6);
    printf("%d", r1->bit5);
    printf("%d", r1->bit4);
    printf("%d", r1->bit3);
    printf("%d", r1->bit2);
    printf("%d", r1->bit1);
    printf("\n");
}

void xor_inst(reg *r1, reg *r2) {
    r1->bit1 = (r1->bit1 != r2->bit1) ? 1 : 0;
    r1->bit2 = (r1->bit2 != r2->bit2) ? 1 : 0;
    r1->bit3 = (r1->bit3 != r2->bit3) ? 1 : 0;
    r1->bit4 = (r1->bit4 != r2->bit4) ? 1 : 0;
    r1->bit5 = (r1->bit5 != r2->bit5) ? 1 : 0;
    r1->bit6 = (r1->bit6 != r2->bit6) ? 1 : 0;
    r1->bit7 = (r1->bit7 != r2->bit7) ? 1 : 0;
    r1->bit8 = (r1->bit8 != r2->bit8) ? 1 : 0;
}

void cpy_reg(reg *rsrc, reg *rdst) {
    rdst->bit8 = rsrc->bit8;
    rdst->bit7 = rsrc->bit7;
    rdst->bit6 = rsrc->bit6;
    rdst->bit5 = rsrc->bit5;
    rdst->bit4 = rsrc->bit4;
    rdst->bit3 = rsrc->bit3;
    rdst->bit2 = rsrc->bit2;
    rdst->bit1 = rsrc->bit1;
}





// Fungsi static inline berikut digunakan hanya untuk
//      mempermudah penulisan operasi boolean
static inline char gt_inst(reg *r1, reg *r2) {
    if (r1->bit8 > r2->bit8)
        return 1;
    else if (r1->bit8 < r2->bit8)
        return 0;
    else {
        if (r1->bit7 > r2->bit7)
            return 1;
        else if (r1->bit7 < r2->bit7)
            return 0;
        else {
            if (r1->bit6 > r2->bit6)
                return 1;
            else if (r1->bit6 < r2->bit6)
                return 0;
            else {
                if (r1->bit5 > r2->bit5)
                    return 1;
                else if (r1->bit5 < r2->bit5)
                    return 0;
                else {
                    if (r1->bit4 > r2->bit4)
                        return 1;
                    else if (r1->bit4 < r2->bit4)
                        return 0;
                    else {
                        if (r1->bit3 > r2->bit3)
                            return 1;
                        else if (r1->bit3 < r2->bit3)
                            return 0;
                        else {
                            if (r1->bit2 > r2->bit2)
                                return 1;
                            else if (r1->bit2 < r2->bit2)
                                return 0;
                            else {
                                if (r1->bit1 > r2->bit1)
                                    return 1;
                                else
                                    return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

static inline char z_inst(reg *r1) {
    return r1->bit1 == 0
        && r1->bit2 == 0
        && r1->bit3 == 0
        && r1->bit4 == 0
        && r1->bit5 == 0
        && r1->bit6 == 0
        && r1->bit7 == 0
        && r1->bit8 == 0;
}

static inline char eq_inst(reg *r1, reg *r2) {
    return r1->bit1 == r2->bit1
        && r1->bit2 == r2->bit2
        && r1->bit3 == r2->bit3
        && r1->bit4 == r2->bit4
        && r1->bit5 == r2->bit5
        && r1->bit6 == r2->bit6
        && r1->bit7 == r2->bit7
        && r1->bit8 == r2->bit8;
}

static inline char nz_inst(reg *r1) {
    return !z_inst(r1);
}





// Increment & Decrement + 4 operasi aritmatika umum
void inc_inst(reg *r1) {
    if (r1->bit1 == 1) {
        r1->bit1 = 0;
        if (r1->bit2 == 1) {
            r1->bit2 = 0;
            if (r1->bit3 == 1) {
                r1->bit3 = 0;
                if (r1->bit4 == 1) {
                    r1->bit4 = 0;
                    if (r1->bit5 == 1) {
                        r1->bit5 = 0;
                        if (r1->bit6 == 1) {
                            r1->bit6 = 0;
                            if (r1->bit7 == 1) {
                                r1->bit7 = 0;
                                if (r1->bit8 == 1) {
                                    r1->bit8 = 0;
                                }
                                else
                                    r1->bit8 = 1;
                            }
                            else
                                r1->bit7 = 1;
                        }
                        else
                            r1->bit6 = 1;
                    }
                    else
                        r1->bit5 = 1;
                }
                else
                    r1->bit4 = 1;
            }
            else
                r1->bit3 = 1;
        }
        else
            r1->bit2 = 1;
    }
    else
        r1->bit1 = 1;
}

void dec_inst(reg *r1) {
    if (r1->bit1 == 0) {
        r1->bit1 = 1;
        if (r1->bit2 == 0) {
            r1->bit2 = 1;
            if (r1->bit3 == 0) {
                r1->bit3 = 1;
                if (r1->bit4 == 0) {
                    r1->bit4 = 1;
                    if (r1->bit5 == 0) {
                        r1->bit5 = 1;
                        if (r1->bit6 == 0) {
                            r1->bit6 = 1;
                            if (r1->bit7 == 0) {
                                r1->bit7 = 1;
                                if (r1->bit8 == 0) {
                                    r1->bit8 = 1;
                                }
                                else
                                    r1->bit8 = 0;
                            }
                            else
                                r1->bit7 = 0;
                        }
                        else
                            r1->bit6 = 0;
                    }
                    else
                        r1->bit5 = 0;
                }
                else
                    r1->bit4 = 0;
            }
            else
                r1->bit3 = 0;
        }
        else
            r1->bit2 = 0;
    }
    else
        r1->bit1 = 0;
}

void add_inst(reg *r1, reg *r2) {
    cpy_reg(r2, &reg4);
add_loop:
    if (!z_inst(&reg4)) {
        inc_inst(r1);
        dec_inst(&reg4);
        goto add_loop;
    }
}

void sub_inst(reg *r1, reg *r2) {
    cpy_reg(r2, &reg4);
sub_loop:
    if (!z_inst(&reg4)) {
        dec_inst(r1);
        dec_inst(&reg4);
        goto sub_loop;
    }
}

void mul_inst(reg *r1, reg *r2) {
    cpy_reg(r2, &reg3);
    cpy_reg(r1, r2);
    xor_inst(r1, r1);
mul_loop:
    if (nz_inst(&reg3)) {
        add_inst(r1, r2);
        dec_inst(&reg3);
        goto mul_loop;
    }
}

void div_inst(reg *r1, reg *r2) {
    xor_inst(&reg3, &reg3);
div_loop:
    if (gt_inst(r1, r2)) {
        sub_inst(r1, r2);
        inc_inst(&reg3);
        goto div_loop;
    }
    else {
        if (eq_inst(r1, r2))
            inc_inst(&reg3);
        cpy_reg(&reg3, r1);
    }
}





// Fungsi pembantu kalkulasi
void mul_by_10(reg *r1, reg *rbuf) {
    xor_inst(rbuf, rbuf);
    rbuf->bit2 = 1;
    rbuf->bit4 = 1;
    mul_inst(r1, rbuf);
}

void div_by_10(reg *r1, reg *rbuf) {
    xor_inst(rbuf, rbuf);
    rbuf->bit2 = 1;
    rbuf->bit4 = 1;
    div_inst(r1, rbuf);
}

void div_by_100(reg *r1, reg *rbuf) {
    xor_inst(rbuf, rbuf);
    rbuf->bit3 = 1;
    rbuf->bit6 = 1;
    rbuf->bit7 = 1;
    div_inst(r1, rbuf);
}

void mod_by_10(reg *r1, reg *rbuf, reg *rbuf2) {
    // rbuf = div(r1, 10)
    xor_inst(rbuf, rbuf);
    xor_inst(rbuf2, rbuf2);
    cpy_reg(r1, rbuf);
    div_by_10(rbuf, rbuf2);

    // rbuf = 10 * div(r1, 10)
    xor_inst(rbuf2, rbuf2);
    rbuf2->bit2 = 1;
    rbuf2->bit4 = 1;
    mul_inst(rbuf, rbuf2);

    // rbuf = r1 - 10 * div(r1, 10)
    cpy_reg(r1, rbuf2);
    sub_inst(r1, rbuf);
}

void mod_by_100(reg *r1, reg *rbuf, reg *rbuf2) {
    // rbuf = div(r1, 100)
    xor_inst(rbuf, rbuf);
    xor_inst(rbuf2, rbuf2);
    cpy_reg(r1, rbuf);
    div_by_100(rbuf, rbuf2);

    // rbuf = 100 * div(r1, 100)
    xor_inst(rbuf2, rbuf2);
    rbuf2->bit3 = 1;
    rbuf2->bit6 = 1;
    rbuf2->bit7 = 1;
    mul_inst(rbuf, rbuf2);

    // rbuf = r1 - 100 * div(r1, 100)
    cpy_reg(r1, rbuf2);
    sub_inst(r1, rbuf);
}



void bin_reg_to_1_digit(reg *r1) {
    if (r1->bit1 && r1->bit2 && r1->bit3)
        printf("7");
    else if (r1->bit1 && r1->bit3)
        printf("5");
    else if (r1->bit2 && r1->bit3)
        printf("6");
    else if (r1->bit1 && r1->bit2)
        printf("3");
    else if (r1->bit1 && r1->bit4)
        printf("9");
    else if (r1->bit1)
        printf("1");
    else if (r1->bit2)
        printf("2");
    else if (r1->bit3)
        printf("4");
    else if (r1->bit4)
        printf("8");
    else if (z_inst(r1))
        printf("0");
    else {
        printf("Error");
        exit(1);
    }
}

void print_evaluated_decimal_reg() {
    xor_inst(&reg2, &reg2);
    xor_inst(&reg3, &reg3);
    xor_inst(&reg4, &reg4);
    xor_inst(&reg5, &reg5);
    xor_inst(&reg6, &reg6);

    // First digit (100)
    cpy_reg(&reg1, &reg2);
    div_by_100(&reg2, &reg5);
    bin_reg_to_1_digit(&reg2);

    // Second digit (10)
    cpy_reg(&reg1, &reg2);
    mod_by_100(&reg2, &reg5, &reg6);
    div_by_10(&reg2, &reg5);
    bin_reg_to_1_digit(&reg2);

    // Third digit (1)
    cpy_reg(&reg1, &reg2);
    mod_by_10(&reg2, &reg5, &reg6);
    bin_reg_to_1_digit(&reg2);
}


// Digunakan untuk memperjelas parsing
void char_to_bit_reg(reg *r1, char c) {
    // Akan mengosongkan r1
    xor_inst(r1, r1);
    switch (c) {
        case '1':
            r1->bit1 = 1;
            break;
        case '2':
            r1->bit2 = 1;
            break;
        case '3':
            r1->bit1 = 1;
            r1->bit2 = 1;
            break;
        case '4':
            r1->bit3 = 1;
            break;
        case '5':
            r1->bit1 = 1;
            r1->bit3 = 1;
            break;
        case '6':
            r1->bit2 = 1;
            r1->bit3 = 1;
            break;
        case '7':
            r1->bit1 = 1;
            r1->bit2 = 1;
            r1->bit3 = 1;
            break;
        case '8':
            r1->bit4 = 1;
            break;
        case '9':
            r1->bit1 = 1;
            r1->bit4 = 1;
            break;
        case '0':
            break;
    }
}

void eval_last_operator() {
    if (z_inst(&reg6))
        cpy_reg(&reg2, &reg1);
    else if (reg6.bit1)
        add_inst(&reg1, &reg2);
    else if (reg6.bit2)
        sub_inst(&reg1, &reg2);
    else if (reg6.bit3)
        mul_inst(&reg1, &reg2);
    else if (reg6.bit4)
        div_inst(&reg1, &reg2);
    else {
        printf("Error\n");
        exit(1);
    }

    xor_inst(&reg2, &reg2);
    xor_inst(&reg6, &reg6);
}


int main(int argc, char* argv[]) {
    FILE *file = fopen(argv[1], "r");
    char c;
    if (argc < 2) {
        printf("Missing argument\n");
        exit(1);
    }
    else if (file == NULL) {
        printf("File not found!\n");
        exit(1);
    }



    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
        switch (c) {
            case '+':
                eval_last_operator();
                reg6.bit1 = 1;
                break;
            case '-':
                eval_last_operator();
                reg6.bit2 = 1;
                break;
            case '*':
                eval_last_operator();
                reg6.bit3 = 1;
                break;
            case '/':
                eval_last_operator();
                reg6.bit4 = 1;
                break;


            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                mul_by_10(&reg2, &reg5);
                char_to_bit_reg(&reg5, c);
                add_inst(&reg2, &reg5);
        }
    }

    printf("\nResult\nBinary  = ");
    eval_last_operator();
    print_binary_reg(&reg1);
    printf("Decimal = ");
    print_evaluated_decimal_reg(&reg1);
    printf("\n\n");
    return 0;
}
