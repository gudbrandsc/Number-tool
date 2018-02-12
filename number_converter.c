#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include<limits.h>

#define MAX_STR_LEN 64


unsigned int change_bit_width(int width, unsigned int value){
  unsigned  mask;
  unsigned int new_value;
  mask = (1 << width) - 1;
  new_value = value & mask;
  return new_value;
}

unsigned int get_value_from_bitrange(int lsb, int msb, unsigned int value ){
  unsigned int result = (value >> lsb) & ~(~0 << (msb-lsb+1));
  return result;

}
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
int bits_to_unsigned(char *bits, unsigned int* unsigned_value){
  unsigned int value = 0;
  size_t bit_length = strlen(bits);
 
  if(bit_length > 34){
    return 1;
  }
  if (bits[2] == '1' && strlen(bits) == 34){
    char* flipbit = bit_flip(bits);
    value = (bits_to_int(flipbit) + 1) * -1;
    free(flipbit);
  }else{
    value = bits_to_int(bits);
  }
  *unsigned_value = value;

  return 0;
}

/*Prints a whitespace for each 4th bit*/
void print_bit_in_group(int number_of_bits,char* bits){
  int count = 0;
  size_t bit_length = strlen(bits);
  int start = bit_length - number_of_bits;
  for(int i = start ; i <= bit_length;i++){
    if(count%4 == 0 && count != 0){
      printf(" ");
    }
    printf("%c",bits[i]);
    count += 1;
  }
  printf(" (Base 2)\n");
}

/*Prints bit value with 0b prefix*/
void print_bits_with_prefix(int number_of_bits,char* bits){
  int count = 0;
  size_t bit_length = strlen(bits);
  int start = bit_length - number_of_bits;
  printf("0b");
  for(int i = start ; i <= bit_length;i++){
    printf("%c",bits[i]);
    count += 1;
  }
  printf(" (Base 2)\n");
}


/*Prints bit value with 0b prefix*/
void print_hexadecimal(int number_of_bits,char* bits){
  int count = 0;
  size_t bit_length = strlen(bits);
  int start = bit_length - number_of_bits;
  printf("0b");
  for(int i = start ; i <= bit_length;i++){
    printf("%c",bits[i]);
    count += 1;
  }
  printf(" (Base 2)\n");
}

/*Return a unsigned int value of the bit*/
int hex_to_unsigned(char *bits, unsigned int* unsigned_value){
  int value = 0;
  size_t bit_length = strlen(bits);
  int power = 1;
  int place = 0;
  for(int i = bit_length-1; i > 1; i--){
    switch(bits[i]) {
    case '0' :
      break;
    case '1' :
      place = 1;
      break;
    case '2' :
      place = 2;
      break;
    case '3' :
      place = 3;
      break;
    case '4' :
      place = 4;
      break;
    case '5' :
      place = 5;
      break;
    case '6' :
      place = 6;
      break;
    case '7' :
      place = 7;
      break;
    case '8' :
      place = 8;
      break;
    case '9' :
      place = 9;
      break;
    case 'A' :
      place = 10;
      break;
    case 'B' :
      place = 11;
      break;
    case 'C' :
      place = 12;
      break;
    case 'D' :
      place = 13;
      break;
    case 'E' :
      place = 14;
      break;
    case 'F' :
      place = 15;
      break;
    }
    value += place * power;
    if(value < 0){
      return 1;
    }
    power *= 16;
  }
  *unsigned_value = (unsigned)value;

 return 0;
}
/*Convert char array of numbers to unsigned int*/
int pos_int_to_unsigned(char* value, unsigned int* unsigned_value) {
  int int_value = 0;
  int multi = 1;
  int currVal;

  for(int i = strlen(value)-1; i >= 0; i--){
    int_value += ((value[i]-'0') * multi);
    if(int_value < 0){
      return 1;
    }
    multi = (multi*10);
  }
  
  *unsigned_value = (unsigned)int_value;

 return 0;
}

int negativ_int_to_unsigned(char* value, unsigned int* unsigned_value){
  int int_value = 0;
  int multi = 1;
  int curr_val;

  for(int i = strlen(value) - 1; i >= 1; i--){
    int_value += ((value[i] - '0') * multi); 
    if(int_value < 0){
      return 1;
    }
   
    multi = (multi * 10);
  }

  int_value = int_value * (-1);
  
 
  *unsigned_value = (unsigned int) int_value;
  
  return 0;
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
      printf("%c is not a valid hex char\n",value[i]);
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
/*Convert char array of numbers to unsigned int*/
int chararray_to_integer(char* value) {
  int int_value = 0;
  int multi = 1;
  int currVal;

  for(int i = strlen(value)-1; i >= 0; i--){
    int_value += ((value[i]-'0') * multi);
    if(int_value < 0){
      return 1;
    }
    multi = (multi*10);
  }
  
  return int_value;
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
  }
  return;
}

int verify_argv_value(char* value){
  int value_size = strlen(value);
  int valid_number_type;

  if(value[0]=='-' && isdigit(value[1])){//If value is negativ
    if(check_if_negativ_int(value_size, value) == 0){
      valid_number_type = 1;
    }
  }else if(value[0]=='0' && value[1]=='x' && value_size > 2){//If value is hexadecimal
    if(check_if_hexadecimal(value_size, value) == 0){
      valid_number_type = 2;
    }
  }else if(value[0]=='0' && value[1]=='b'){// If value is a binary
    if(check_if_binary(value_size, value) == 0){
      valid_number_type = 3;
    }
  }else if(check_if_int(value_size, value)==0){ //If value is a possetiv integer
    valid_number_type = 4;
  }else{
    valid_number_type = 0;
  }

  return valid_number_type;
}

void print_info_to_consol(int bitwidth, unsigned int value){
  char binstr[MAX_STR_LEN];
  int_to_bits(binstr, value);
  print_bit_in_group(bitwidth,binstr);
  print_bits_with_prefix(bitwidth,binstr);
  if(bitwidth==32){
    printf("0x%08X (base 16)\n",value);
  }else{
    printf("0x%X (base 16)\n",value);
  }
  
  printf("%u (base 10 unsigned)\n",value);
  printf("%d (base 10 signed)\n",value);
}

void bitwidth_handler(char* bitwidth_input, char* value){
  unsigned int unsigned_value;
  unsigned int updated_value;
  int bitwidth_argv_length = strlen(bitwidth_input);
  int bitwidth;
  int value_type;
  if(check_if_int (bitwidth_argv_length, bitwidth_input) == 0){
	bitwidth = chararray_to_integer(bitwidth_input);
	if((bitwidth <= 32) && (bitwidth % 4 == 0)){
	  value_type = verify_argv_value(value);	
	  if(value_type == 0){
	    printf("Invalid value\n");
	  }else{
	    convert_value(value_type,value, &unsigned_value);
	    if(bitwidth == 32){
	      print_info_to_consol(bitwidth,unsigned_value);
	    }else{
	      updated_value = change_bit_width(bitwidth, unsigned_value);
	      print_info_to_consol(bitwidth, updated_value);
	    }
	  }
	}else{
	  printf("bitwidth not supported\n");
	}
  }else{
    printf("Invalid bitwidth\n");
  }
}
void get_bitrange(char* values){
  
}
void bit_twiddel_handler(char* range_input, char* value){
  unsigned int unsigned_value;
  unsigned int updated_value;
  int value_type;
  int msb;
  int lsb;

    
  
  value_type = verify_argv_value(value);	
  if(value_type == 0){
    printf("Invalid value\n");
  }else{
    convert_value(value_type,value, &unsigned_value);
    char *pt;
    int values[2];
    int i = 0;
    pt = strtok (range_input,",");
    while (pt != NULL) {
      values[i] = atoi(pt);
      pt = strtok (NULL, ",");
      i+=1;
    }
  
    msb = values[1];// TODO ; change
    lsb = values[0];
printf("lsb %d\n",lsb);printf("msb %d\n",msb);
    updated_value = get_value_from_bitrange(lsb,msb,unsigned_value);
    printf("value is : %u\n", updated_value);
  }
}

int args_handler(int argc, char** argv){
  unsigned int unsigned_value;
  int bitwidth_argv_length;
  int bitwidth;
  int value_type;
  unsigned int updated_value;

  if(argc == 2){
    value_type = verify_argv_value(argv[1]);	
    if(value_type == 0){
      printf("Invalid value\n");
    }else{
      convert_value(value_type,argv[1], &unsigned_value);
      print_info_to_consol(32,unsigned_value);
    }
    
  }else if(argc == 4){
    char* first_argv = argv[1];
    char* sec_argv = argv[2];
    char* third_argv = argv[3];
    
    if(first_argv[0] =='-' && first_argv[1] == 'b'){
      bitwidth_handler(sec_argv, third_argv);
    }else if(sec_argv[0] =='-' && sec_argv[1] == 'b'){
      bitwidth_handler(third_argv, first_argv);
    }else if(first_argv[0] == '-' && first_argv[1] == 'r'){
      bit_twiddel_handler (sec_argv, third_argv);
    }else if(sec_argv[0] == '-' && sec_argv[1] == 'r'){
      bit_twiddel_handler (third_argv, first_argv);
    }
  }else{
    printf("Invalid argument input\n");
    return 1;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  //unsigned int unsigned_value = verify_argv_value(argv[1]);
  //unsigned int new_width = change_bit_width (8,unsigned_value);
  int success = args_handler(argc, argv);
  return 0;
}
