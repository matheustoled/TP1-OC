andi x2, x1, 0b10000      # Base binária
andi x2, x1, 020          # Base octal
andi x2, x1, 0x10         # Base hexadecimal
andi x2, x1, 16           # Base decimal

addi x3, x2, 0b11111111111111111111111111011001 # Base binária
addi x3, x2, 037777777777 # Base octal
addi x3, x2, 0xFFFFFFD9   # Base hexadecimal
addi x3, x2, -243         # Base decimal
