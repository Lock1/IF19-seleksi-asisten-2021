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

static inline char z_inst(reg *r1) {
    // Secara efektif hanya mempermudah penulisan operasi boolean
    return r1->bit1 == 0
        && r1->bit2 == 0
        && r1->bit3 == 0
        && r1->bit4 == 0
        && r1->bit5 == 0
        && r1->bit6 == 0
        && r1->bit7 == 0
        && r1->bit8 == 0;
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
    // ???
    cpy_reg(r2, &reg3);
    cpy_reg(r1, r2);
mul_loop:
    if (!z_inst(&reg3)) {
        add_inst(r1, r2);
        dec_inst(&reg3);
        printf("\nExec\n");
        print_binary_reg(r1);
        print_binary_reg(&reg3);
        goto mul_loop;
    }
}

int main(int argc, char* argv[]) {
    // FILE *file = fopen(argv[1], "r");
    // char c;
    // if (file == NULL) {
    //     printf("File not found!\n");
    //     exit(1);
    // }
    //
    // while ((c = fgetc(file)) != EOF) {
    //
    // }
    reg1.bit4 = 1;

    reg2.bit1 = 1;
    reg2.bit2 = 1;
    reg2.bit3 = 0;
    reg2.bit4 = 1;
    reg2.bit5 = 0;
    reg2.bit6 = 0;
    reg2.bit7 = 0;
    reg2.bit8 = 0;
    print_binary_reg(&reg1);
    print_binary_reg(&reg2);
    printf("exec\n");

    mul_inst(&reg1, &reg2);

    printf("\nres\n");
    print_binary_reg(&reg1);
    print_binary_reg(&reg2);
    return 0;
}
