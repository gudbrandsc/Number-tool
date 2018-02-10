#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define MAX_STR_LEN 64

/*Flips all bits in a bit array and returns it*/
char* bit_flip(char *bits){
  char *flip_bits = (char *)malloc(strlen(bits)+1);
  size_t bit_length = strlen(bits);
  strcpy(flip_bits,bits);
  size_t flip_length = strlen(flip_bits);

  for(int i = 3; i < flip_length; i++){
    if(bits[i]=='1'){
      flip_bits[i]='0';
    }else{
      flip_bits[i]='1';
    }
  }

  return flip_bits;
}

/*Method to get the bitvalue from a signed or unsigned integer*/
void int_to_bits(char* s, unsigned int v) {
  int i;
  int bp = 31;
  int bv = 0;

  s[0] = '\0';

  for (i = 0; i < 32; i++) {
    bv = (v >> bp) & 0b1;
    s[i] = bv ? '1' : '0';
    bp -= 1;
  }

  s[i] = '\0';

  return;
}

/*Iterates over a bitvalue and returns value*/
unsigned int bits_to_int(char *bits){
  unsigned int value = 0;
  size_t bit_length = strlen(bits);

  if(bit_length != 34){
    for(int i = 2; i < bit_length; i++){
      if (bits[i] == '1'){
	value = (value * 2) + 1;
      }else if (bits[i] == '0'){
	value *= 2;
      }
    }
  }else{
    for(int i = 3; i < bit_length; i++){
      if (bits[i] == '1'){
	value = (value * 2) + 1;
      }else if (bits[i] == '0'){
	value *= 2;
      }
    }
  }

  return value;
}

/*Return a unsigned int value of the bit*/
void bits_to_unsigned(char *bits, unsigned int* unsigned_value){
  unsigned int value = 0;

  if (bits[2] == '1' && strlen(bits) == 34){
    char* flipbit = bit_flip(bits);
    value = (bits_to_int(flipbit) + 1) * -1;
    free(flipbit);
  }else{
    value = bits_to_int(bits);
  }
  *unsigned_value = value;

  return;
}

/*Prints a whitespace for each 4th bit*/
void format_and_print_bits(char* bits){
  int count = 0;
  for(int i = 0; i <= strlen(bits);i++){
    if(count%4 == 0 && count != 0){
      printf(" ");
    }
    printf("%c",bits[i]);
    count += 1;
  }
  printf(" (Base 2)\n");
}

/*Return a unsigned int value of the bit*/
void hex_to_unsigned(char *bits, unsigned int* unsigned_value){
  unsigned int value = 0;
  size_t bit_length = strlen(bits);
  int power = 1;

  for(int i = bit_length-1; i > 1; i--){
    switch(bits[i]) {
    case '0' :
      break;
    case '1' :
      value += power * 1;
      break;
    case '2' :
      value += power * 2;
      break;
    case '3' :
      value += power * 3;
      break;
    case '4' :
      value += power * 4;
      break;
    case '5' :
      value += power * 5;
      break;
    case '6' :
      value += power * 6;
      break;
    case '7' :
      value += power * 7;
      break;
    case '8' :
      value += power * 8;
      break;
    case '9' :
      value += power * 9;
      break;
    case 'A' :
      value += power * 10;
      break;
    case 'B' :
      value += power * 11;
      break;
    case 'C' :
      value += power * 12;
      break;
    case 'D' :
      value += power * 13;
      break;
    case 'E' :
      value += power * 14;
      break;
    case 'F' :
      value += power * 15;
      break;
    }
    power *= 16;
  } 
 *unsigned_value = value;

 return;
}
/*Convert char array of numbers to unsigned int*/
void pos_int_to_unsigned(char* value, unsigned int* unsigned_value) {
  unsigned int intvalue = 0;
  int multi = 1;
  int currVal;

  for(int i = strlen(value)-1; i >= 0; i--){
    intvalue += ((value[i]-'0') * multi);
    multi = (multi*10);
  }
 *unsigned_value = intvalue;

 return;
}

void negativ_int_to_unsigned(char* value, unsigned int* unsigned_value){
  int int_value = 0;
  int multi = 1;
  int curr_val;

  for(int i = strlen(value) - 1; i >= 1; i--){
    int_value += ((value[i] - '0') * multi);
    multi = (multi * 10);
  }
  int_value = int_value * (-1);
  *unsigned_value = (unsigned int) int_value;
  return;
}

int check_if_negativ_int(int value_size, char* value) {
  for(int i = 1; i < value_size; i++){
    if(!isdigit(value[i])){
      return 1;
    }
  }
  return 0;
}

int check_if_int(int value_size, char* value) {
  for(int i = 0; i < value_size; i++){
    if(!isdigit(value[i])){
      return 1;
    }
  }
  return 0;
}

int check_if_hexadecimal(int value_size, char* value) {
  for(int i = 2; i < value_size; i++){
    if(!isxdigit(value[i])){
      printf("%c\n",value[i]);
      return 1;
    }
  }
  return 0;
}

int check_if_binary(int value_size, char* value) {
  for(int i = 2; i < value_size; i++){
    if(!((value[i]=='1') || (value[i]=='0'))){
      return 1;
    }
  }
  return 0;
}


//Remove som verify argv value can call methods
void convert_value(int type, char* value, unsigned int* unsigned_value){

  if(type == 1){
    negativ_int_to_unsigned (value, unsigned_value);
  }else if(type == 2){
    hex_to_unsigned(value, unsigned_value);
  }else if(type == 3){
    bits_to_unsigned(value, unsigned_value);
  }else if(type == 4){
    pos_int_to_unsigned(value, unsigned_value);
  }else if(type == 0){
    printf("%s\n","its not a valid number" );
  }
  return ;
}

unsigned int verify_argv_value(char* value){
  int value_size = strlen(value);
  char binstr[MAX_STR_LEN];
   unsigned int unsigned_value;

  if(value[0]=='-' && isdigit(value[1])){//If value is negativ
    if(check_if_negativ_int(value_size, value) == 0){
      convert_value(1, value, &unsigned_value);
    }
  }else if(value[0]=='0' && value[1]=='x' && value_size > 2){//If value is hexadecimal
    if(check_if_hexadecimal(value_size, value) == 0){
      convert_value(2, value, &unsigned_value);
    }
  }else if(value[0]=='0' && value[1]=='b'){// If value is a binary
    if(check_if_binary(value_size, value) == 0){
      convert_value(3, value, &unsigned_value);
    }
  }else if(check_if_int(value_size, value)==0){ //If value is a possetiv integer
    convert_value(4, value, &unsigned_value);
  }
  int_to_bits(binstr, unsigned_value);
  format_and_print_bits(binstr);
  printf("0b%s (base 2)\n",binstr);
  printf("0x%08X (base 16)\n",unsigned_value);
  printf("%u (base 10 unsigned)\n",unsigned_value);
  printf("%d (base 10 signed)\n",unsigned_value);
  return unsigned_value;
}

int main(int argc, char* argv[]) {
  unsigned int unsigned_value = verify_argv_value(argv[1]);
  printf("%u",unsigned_value);
  return 0;
}
