## What is number tool?
Number tool can convert values between different number systems and also perform "bit twiddling." 
The program supports all 32 bit values represented in any of the following number systems:
- Binary number
- Hexadecimal number 
- Integer number (Ranging from -2147483648 to 4294967295)

_Note that binary numbers must start with 0b, and hexadecimal with 0x._

## Application Execution

**Compile:**
```
gcc -o nt number_converter.c
```
**Run:**
```
./nt 0b000010100000 -> Binary
./nt 0xE3 -> Hexadecimal
./nt 713 -> Unsigned integer
./nt -713 -> Signed integer
```
**Changing the Bit Width**

The default bit width for nt is 32. You can change this default with the -b option:
The program supports the following bit widths: 4, 8, 12, 16, 20, 24, 28, 32.
```
./nt -b 16 713

```
**Bit Twiddling**

You can select the range of bits to use for conversion using the -r option:
```
$ nt -b 4 -r 4,7 0b000010100000

```
Note that the first value in the range specifies the LSB and the second value in the range specifies the MSB. The range values start at 0 and they are inclusive.

**Output**
```
$ nt -713
1111 1111 1111 1111 1111 1101 0011 0111 (base 2) 
0b11111111111111111111110100110111 (base 2)
0xFFFFFD37 (base 16)
4294966583 (base 10 unsigned)
-713 (base 10 signed)
```

