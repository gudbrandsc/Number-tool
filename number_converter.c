#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*Flips all bits in a bit array and returns it*/
char* bit_flip(char *bits){
  char *flipBits = (char *)malloc(strlen(bits)+1);
  size_t bit_length = strlen(bits);
  strcpy(flipBits,bits);
  size_t flip_length = strlen(flipBits);

  for(int i = 3; i < flip_length; i++){
    if(bits[i]=='1'){
      flipBits[i]='0';
    }else{
      flipBits[i]='1';
    }
  }
  return flipBits;
}
/*Method to get the bitvalue from a signed or unsigned integer*/
char *int_to_bits(int n) {
  int nbits = sizeof(n) * 8;
  char *s = malloc(nbits+1);  // +1 for '\0' terminator
  s[nbits] = '\0';
  // forcing evaluation as an unsigned value prevents complications
  // with negative numbers at the left-most bit

  unsigned int u = *(unsigned int*)&n;
  int i;
  unsigned int mask = 1 << (nbits-1); // fill in values right-to-left
  for (i = 0; i < nbits; i++, mask >>= 1){
    s[i] = ((u & mask) != 0) + '0';
  }
  return s;
}

/*Iterates over a bitvalue and returns value*/
unsigned bits_to_int(char *bits){
  unsigned int val = 0;
  size_t bit_length = strlen(bits);
  printf("length%u\n",bit_length);
  if(bit_length != 34){
    for(int i = 2; i < bit_length; i++){
      if (bits[i] == '1'){
	val = val * 2 + 1;
      }else if (bits[i] == '0'){
	val *= 2;
      }
    }
  }else{
    for(int i = 3; i < bit_length; i++){
      if (bits[i] == '1'){
	val = val * 2 + 1;
      }else if (bits[i] == '0'){
	val *= 2;
      }
    }
  }
  return val;
}

/*Return a unsigned int value of the bit*/
unsigned bits_to_unsigned(char *bits){
  unsigned int val = 0;
  printf("%",strlen(bits));
  if (bits[2]=='1' && strlen(bits)==34){
    char* flipbit = bit_flip(bits);
    //Check if i should cast this
    val = (bits_to_int(flipbit) + 1) * -1;
    free(flipbit);
  }else{
    val = bits_to_int(bits);
  }
  return val;
}

/*Prints a whitespace for each 4th bit*/
void format_and_print_bits(char* bits){
  int count = 0;
  for(int i = 0; i <= strlen(bits);i++){
    if(count%4==0 && count != 0){
      printf(" ");
    }
    printf("%c",bits[i]);
    count += 1;
  }
  printf(" (Base 2)\n");
}

/*Return a unsigned int value of the bit*/
unsigned hex_to_unsigned(char *bits){
  unsigned int val = 0;
  size_t bit_length = strlen(bits);
  int power = 1;

  for(int i = bit_length-1; i > 1; i--){
    switch(bits[i]) {
    case '0' :
      break;
    case '1' :
      val += power * 1;
      break;
    case '2' :
      val += power * 2;
      break;
    case '3' :
      val += power * 3;
      break;
    case '4' :
      val += power * 4;
      break;
    case '5' :
      val += power * 5;
      break;
    case '6' :
      val += power * 6;
      break;
    case '7' :
      val += power * 7;
      break;
    case '8' :
      val += power * 8;
      break;
    case '9' :
      val += power * 9;
      break;
    case 'A' :
      val += power * 10;
      break;
    case 'B' :
      val += power * 11;
      break;
    case 'C' :
      val += power * 12;
      break;
    case 'D' :
      val += power * 13;
      break;
    case 'E' :
      val += power * 14;
      break;
    case 'F' :
      val += power * 15;
      break;
    }
    power *= 16;
  }
  printf("%d\n",val );
  return val;
}
/*Convert char array of numbers to unsigned int*/
int pos_int_to_unsigned(char* value) {
  unsigned int intvalue = 0;
  int multi = 1;
  int currVal;

  for(int i = strlen(value)-1; i>=0; i--){
    intvalue+= ((value[i]-'0')*multi);
    multi= (multi*10);
  }
  return intvalue;
}
unsigned int negativ_int_to_unsigned(char* value){
  unsigned int unsigned_val;
  int int_value = 0;
  int multi = 1;
  int curr_val;

  for(int i = strlen(value)-1; i>=1; i--){
    int_value+= ((value[i]-'0')*multi);
    multi= (multi*10);
  }
  int_value = int_value * (-1);
  unsigned_val = (unsigned) int_value;
  return unsigned_val;
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
unsigned int convert_value(int type, char* value){

  if(type==1){
    printf("%s\n","its a negatv" );
    return negativ_int_to_unsigned (value);
  }else if(type==2){
    return hex_to_unsigned(value);
  }else if(type==3){
    return bits_to_unsigned(value);
  }else if(type==4){
    return pos_int_to_unsigned(value);
  }else if(type==0){
    printf("%s\n","its not a valid number" );
  }
  return 0;
}

unsigned int verify_argv_value(char* value){
  int value_size = strlen(value);

  unsigned int unsigned_value = 0;

  if(value[0]=='-' && isdigit(value[1])){//If value is negativ
    if(check_if_negativ_int(value_size, value) == 0){
      unsigned_value = convert_value(1, value);
      printf("%d\n",unsigned_value);
      format_and_print_bits(int_to_bits(unsigned_value));
      printf("0b%s (base 2)\n",int_to_bits(unsigned_value));
      printf("0x%X (base 16)\n",unsigned_value);
      printf("%u (base 10 unsigned)\n",unsigned_value);
      printf("%d (base 10 signed)\n",unsigned_value);
      return unsigned_value;
    }
  }else if(value[0]=='0' && value[1]=='x' && value_size > 2){//If value is hexadecimal
    if(check_if_hexadecimal(value_size, value) == 0){
      unsigned_value = convert_value(2, value);
      format_and_print_bits(int_to_bits(unsigned_value));
      printf("0b%s (base 2)\n",int_to_bits(unsigned_value));
      printf("0x%X (base 16)\n",unsigned_value);
      printf("%u (base 10 unsigned)\n",unsigned_value);
      printf("%d (base 10 signed)\n",unsigned_value);

      return unsigned_value;
    }
  }else if(value[0]=='0' && value[1]=='b'){// If value is a binary
    if(check_if_binary(value_size, value) == 0){
      unsigned_value = convert_value(3, value);
      printf("0x%X (base 16)\n",unsigned_value);
      printf("%u (base 10 unsigned)\n",unsigned_value);
      printf("%d (base 10 signed)\n",unsigned_value);
      return unsigned_value;
    }
  }else if(check_if_int(value_size, value)==0){ //If value is a possetiv integer
    unsigned_value = convert_value(4, value);
    format_and_print_bits(int_to_bits(unsigned_value));
    printf("0b%s (base 2)\n",int_to_bits(unsigned_value));
    printf("0x%X (base 16)\n",unsigned_value);
    printf("%u (base 10 unsigned)\n",unsigned_value);
    printf("%d (base 10 signed)\n",unsigned_value);
    return unsigned_value;
  }
  return 0;
}



int main(int argc, char* argv[]) {
  /*if(strlen(argv[1] > 33)){
    printf("invalid input\n");
    }
  */

  unsigned int value = verify_argv_value(argv[1]);




  return 0;
}
