andi x2, x1, 0b10000      # Base binária
andi x2, x1, 020          # Base octal
andi x2, x1, 0x10         # Base hexadecimal
andi x2, x1, 16           # Base decimal

andi x2, x1, 0b11111      # binário
andi x2, x1, 037          # octal
andi x2, x1, 0x1F         # hexadecimal
andi x2, x1, 31           # decimal

andi x2, x1, 0b11111111   # binário
andi x2, x1, 0377         # octal
andi x2, x1, 0xFF         # hexadecimal
andi x2, x1, 255          # decimal

andi x2, x1, 0b1010       # binário
andi x2, x1, 012          # octal
andi x2, x1, 0xA          # hexadecimal
andi x2, x1, 10           # decimal

andi x2, x1, 0b1000000    # binário
andi x2, x1, 0100         # octal
andi x2, x1, 0x40         # hexadecimal
andi x2, x1, 64           # decimal

andi x2, x1, 0b1111111    # binário
andi x2, x1, 0177         # octal
andi x2, x1, 0x7F         # hexadecimal
andi x2, x1, 127          # decimal

addi x3, x2, 0b11111111111111111111111100001101 # Base binária
addi x3, x2, 03777777035 # Base octal
addi x3, x2, 0xFFFFFF0D   # Base hexadecimal
addi x3, x2, -243         # Base decimal
