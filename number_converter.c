#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


struct Input_value_info {
    char * number;
    int type;
    int bit_width;
    int start_range;
    int end_range;
};

//Change bit_width of value
unsigned int
change_bit_width(int width, unsigned int value) {
    unsigned  mask;
    unsigned int new_value;
    if(width != 32){
      mask = (1 << width) - 1;
      new_value = value & mask;
    }else{
      new_value  =  value;
	}
    return new_value;
}

/*Flips all bits in a char bit array and returns it*/
char *
bit_flip(char * bits, int start) {
    char * flip_bits = (char * ) malloc(strlen(bits) + 1);
    strcpy(flip_bits, bits);
    size_t flip_length = strlen(flip_bits);

    for (int i = start; i < flip_length; i++) {
        if (bits[i] == '1') {
            flip_bits[i] = '0';
        } else {
            flip_bits[i] = '1';
        }
    }
    return flip_bits;
}

/*Method to get the bit value from a signed or unsigned integer*/
void
int_to_bits(char * s, unsigned int v) {
    int i;
    int bp = 31;
    int bv = 0;
   
    for (i = 0; i < 32; i++) {
        bv = (v >> bp) & 0b1;
        s[i] = bv ? '1' : '0';
        bp -= 1;
    }
    s[i] = '\0';
}

/*Iterates over a bit value and returns value*/
unsigned int
bits_to_int(char * bits) {
    unsigned int value = 0;
    size_t bit_length = strlen(bits);

    if (bit_length != 34) {
        //If bit length is less than then start from first bit value
        for (int i = 2; i < bit_length; i++) {
            if (bits[i] == '1') {
                value = (value * 2) + 1;
            } else if (bits[i] == '0') {
                value *= 2;
            }
        }
    } else {
        //Start from 2. bit value since first is negative operator
        for (int i = 3; i < bit_length; i++) {
            if (bits[i] == '1') {
                value = (value * 2) + 1;
            } else if (bits[i] == '0') {
                value *= 2;
            }
        }
    }
    return value;
}

//Converts the bits from a given range in a bit array to a unsigned int
unsigned int
bits_to_int_range(char * bits, int msb, int lsb) {
    unsigned int value = 0;
    int start_bit = 32 - (msb + 1);
    int end_bit = 32 - (lsb + 1);

    for (int i = start_bit; i <= end_bit; i++) {
        if (bits[i] == '1') {
            value = (value * 2) + 1;
        } else if (bits[i] == '0') {
            value *= 2;
        }
    }
    return value;
}

/*Return a unsigned int value of the bit*/
int
bits_to_unsigned(char * bits, unsigned int * unsigned_value) {
    unsigned int value = 0;
    size_t bit_length = strlen(bits);

    if (bit_length > 34) {
        return 1;
    }
    if (bits[2] == '1' && strlen(bits) == 34) {
        char * flip_bit = bit_flip(bits,3);
        value = (bits_to_int(flip_bit) + 1) * -1;
    } else {
        value = bits_to_int(bits);
    } * unsigned_value = value;
    return 0;
}

/*Return a unsigned int value of the bit*/
void
bits_to_unsigned_with_range(char * bits, unsigned int * unsigned_value, int msb, int lsb) {
    unsigned int value = 0;
    int first = 32 - msb;

    if (bits[first] == '1') {
        char * flip_bit = bit_flip(bits, msb);
        value = (bits_to_int_range(flip_bit, msb, lsb) + 1) * -1;
        free(flip_bit);
    } else {
        value = bits_to_int_range(bits, msb, lsb);
    }
    * unsigned_value = value;

}

//Get signed integer value from a bit_width
int bit_width_to_signed(char *bits, int msb){
    int value = 0;
    size_t bit_length = strlen(bits);
    int start = 32 - msb;
    if(bits[start]=='1'){
        for (int i = start; i < bit_length; i++) {
            if (bits[i] == '1') {
                value *= 2;
            } else if (bits[i] == '0') {
                value = (value * 2) + 1;
            }
        }
        value = (value + 1) * -1;
    }else{
        for (int i = start; i < bit_length; i++) {
            if (bits[i] == '1') {
                value = (value * 2) + 1;
            } else if (bits[i] == '0') {
                value *= 2;
            }
        }
    }
    return value;
}

/*Prints a whitespace for each 4th bit*/
void
print_bit_in_group(int number_of_bits, char * bits) {
    int count = 0;
    int bit_length = strlen(bits);
    int start = bit_length - number_of_bits;
    for (int i = start; i <= bit_length; i++) {
        if (count % 4 == 0 && count != 0) {
            printf(" ");
        }
        printf("%c", bits[i]);
        count += 1;
    }
    printf(" (Base 2)\n");
}

/*Prints bit value with 0b prefix*/
void
print_bits_with_prefix(int number_of_bits, char * bits) {
    int count = 0;
    int bit_length = strlen(bits);

    int start = bit_length - number_of_bits;
    printf("0b");
    for (int i = start; i <= bit_length; i++) {
        printf("%c", bits[i]);
        count += 1;
    }
    printf(" (Base 2)\n");
}

/*Return a unsigned int value of the bit*/
int
hex_to_unsigned(char * bits, unsigned int * unsigned_value) {
    int value = 0;
    int bit_length = strlen(bits);
    int base = 1;    
    
    for (int i = bit_length - 1; i > 1; i--) {
      if(bits[i] >= '0' && bits[i] <='9'){
	value += (bits[i] - 48)*base;
	base = base * 16;
      }else if(bits[i] >= 'A' && bits[i] <= 'F'){
	value += (bits[i] - 55)*base;
	base = base * 16;
      }
      printf("Value %d\n",bits[i]);
    }
    if(value <= 0){
      return 1;
      }
    * unsigned_value = (unsigned) value;
    return 0;
}

/*Convert char array of numbers to unsigned int*/
int
pos_int_to_unsigned(char * value, unsigned int * unsigned_value) {
    int new_value = 0;
    int old_value = 0;
    int multi = 1;
    int value_length = strlen(value);
    for (int i = value_length - 1; i >= 0; i--) {
        new_value += ((value[i] - '0') * multi);
        if (old_value >  new_value) {
            return 1;
        }
        old_value = new_value;
        multi = (multi * 10);

    }
    * unsigned_value = (unsigned)new_value;

    return 0;
}

int
negative_int_to_unsigned(char *value, unsigned int *unsigned_value) {
    int int_value = 0;
    int multi = 1;
    int value_length = strlen(value);

    for (int i = value_length - 1; i >= 1; i--) {
        int_value += ((value[i] - '0') * multi);
        if (int_value < 0) {
            return 1;
        }
        multi = (multi * 10);
    }
    int_value = int_value * (-1);
    * unsigned_value = (unsigned int) int_value;

    return 0;
}

int
check_if_negative_int(int value_size, char *value) {
    for (int i = 1; i < value_size; i++) {
        if (!isdigit(value[i])) {
            return 1;
        }
    }
    return 0;
}

int
check_if_int(int value_size, char * value) {
    for (int i = 0; i < value_size; i++) {
        if (!isdigit(value[i])) {
            return 1;
        }
    }
    return 0;
}

int
check_if_hexadecimal(int value_size, char * value) {
    for (int i = 2; i < value_size; i++) {
        if (!isxdigit(value[i])) {
            return 1;
        }
    }
    return 0;
}

int
check_if_binary(int value_size, char * value) {
    for (int i = 2; i < value_size; i++) {
        if (!((value[i] == '1') || (value[i] == '0'))) {
            return 1;
        }
    }
    return 0;
}

/*Convert char array of numbers to unsigned int*/
int
chararray_to_integer(char * value) {
    int int_value = 0;
    int multi = 1;

    for (int i = strlen(value) - 1; i >= 0; i--) {
        int_value += ((value[i] - '0') * multi);
        if (int_value < 0) {
            return 1;
        }
        multi = (multi * 10);
    }
    return int_value;
}

//Remove som verify argv value can call methods
int
convert_value(int type, char * value, unsigned int * unsigned_value) {
    int valid_32bit;
    if (type == 1) {
        valid_32bit = negative_int_to_unsigned(value, unsigned_value);
    } else if (type == 2) {
        valid_32bit = hex_to_unsigned(value, unsigned_value);
    } else if (type == 3) {
        valid_32bit = bits_to_unsigned(value, unsigned_value);
    } else if (type == 4) {
        valid_32bit = pos_int_to_unsigned(value, unsigned_value);
    }
    return valid_32bit;
}

int
get_value_type(char * value) {
    int value_size = strlen(value);
    int valid_number_type;

    if (value[0] == '-' && isdigit(value[1])) { //If value is negative
        if (check_if_negative_int(value_size, value) == 0) {
            valid_number_type = 1;
        }
    } else if (value[0] == '0' && value[1] == 'x' && value_size > 2) { //If value is hexadecimal
        if (check_if_hexadecimal(value_size, value) == 0) {
            valid_number_type = 2;
        }
    } else if (value[0] == '0' && value[1] == 'b') { // If value is a binary
        if (check_if_binary(value_size, value) == 0) {
            valid_number_type = 3;
        }
    } else if (check_if_int(value_size, value) == 0) { //If value is a positive integer
        valid_number_type = 4;
    } else {

        valid_number_type = 0;
    }

    return valid_number_type;
}
//Print value to console
void print_info_to_console(int bit_width, unsigned int value) {
    char bin_str[33];
    
    int_to_bits(bin_str, value);
    print_bit_in_group(bit_width, bin_str);
    print_bits_with_prefix(bit_width, bin_str);
    if (bit_width == 32) {
        printf("0x%08X (base 16)\n", value);
    } else {
        printf("0x%X (base 16)\n", value);
    }
    printf("%u (base 10 unsigned)\n", value);
    int new_value = bit_width_to_signed(bin_str, bit_width);
    printf("%d (base 10 signed)\n", new_value);
    }

int verify_bit_width(int bit_width) {
    if ((bit_width <= 32) && (bit_width % 4 == 0)) {
        return 0;
    }
    return 1;

}
int verify_range(int msb, int lsb) {
    if (msb <= lsb ||msb > 32|| lsb < 0) {
        return 1;
    }
    return 0;

}

// Make so returns value
void get_ranges(char * ranges, int * values){
    char * pt;
    int i = 0;
    pt = strtok(ranges, ",");
    while (pt != NULL) {
        values[i] = atoi(pt);
        pt = strtok(NULL, ",");
        i += 1;
    }

}

void bit_twiddle_handler(unsigned int value, int msb, int lsb, unsigned int *updated_value) {
    char bit_value[33];
    if(msb==32 && lsb==0){
        *updated_value = value;
    }else{
    unsigned int new_value;
    int_to_bits(bit_value, value);
    bits_to_unsigned_with_range(bit_value, &new_value, msb, lsb);
    *updated_value =  new_value;
    }
}

void build_input_struct(struct Input_value_info **value_info, char *number, int type, int bit_width, int start_range, int end_range){
    struct Input_value_info temp;
    temp.number = number;
    temp.type = type;
    temp.bit_width = bit_width;
    temp.start_range = start_range;
    temp.end_range = end_range;
    **value_info = temp;

}

//Function that handles input values from args
void args_handler(int argc, char * * argv, struct Input_value_info* value_info) { //point struct
    int bit_width = 32;
    int start_range = 0;
    int end_range = 32;
    int ranges[2];
    int value_type = 0;
    char * input_number;


    if(argc == 2 || argc == 4 || argc == 6){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i],"-b") == 0){
                bit_width = chararray_to_integer(argv[i+1]);
                i+=1;
            }else if(strcmp(argv[i],"-r") == 0){
                get_ranges(argv[i+1],ranges);
                start_range = ranges[0];
                end_range = ranges[1];
                i+=1;
            }else{
                input_number = argv[i];
                value_type = get_value_type(input_number);
            }
        }
    }
    build_input_struct(&value_info, input_number, value_type, bit_width, start_range, end_range);
}
int main(int argc, char * argv[]) {
    struct Input_value_info input_info;
    unsigned int unsigned_value;
    unsigned int updated_value;


    args_handler(argc, argv, &input_info);
    int valid_32bit = convert_value(input_info.type,input_info.number, &unsigned_value);

    if(input_info.type == 0 || verify_bit_width(input_info.bit_width) == 1 || verify_range(input_info.end_range,input_info.start_range) == 1 || valid_32bit == 1){
        printf("Usage: nt <32 bit number> [-r start_range,end_range] [-b bit_width]\n");
    }else{
        bit_twiddle_handler(unsigned_value, input_info.end_range, input_info.start_range, &updated_value);
        updated_value = change_bit_width(input_info.bit_width, unsigned_value);
        print_info_to_console(input_info.bit_width, unsigned_value);
    }
    return 0;
}














