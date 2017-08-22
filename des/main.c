#include <stdio.h>
#include "des.h"

int main(int argc, char *argv[])
{
	int i=0;
	unsigned char mykey[8] = "12345678";
	unsigned char myinput[8] = "abcdefgh";
	unsigned char myoutput[8];
	des_context my_des_context ;

	unsigned char iv_en[8]="25145695";
	unsigned char iv_de[8]="25145695";

	des_setkey_enc(&my_des_context, mykey);
	des_crypt_ecb(&my_des_context, myinput, myoutput);
	for(i=0; i<8; i++)
		printf("%x", myinput[i]);
	printf("\n");
	for (i=0; i<8; i++)
		printf("%x", myoutput[i]);
	printf("\n");
	des_setkey_dec(&my_des_context, mykey);
	des_crypt_ecb(&my_des_context, myoutput, myoutput);
	printf("after:\n");
	for (i=0; i<8; i++)
		printf("%x", myoutput[i]);
	printf("\n*********\n\n");


	des_setkey_enc(&my_des_context, mykey);
	des_crypt_cbc(&my_des_context, DES_ENCRYPT, 8 ,iv_en, myinput, myoutput);
	for(i=0; i<8; i++)
		printf("%x", myinput[i]);
	printf("\n");
	for (i=0; i<8; i++)
		printf("%x", myoutput[i]);
	printf("\n");
	des_setkey_dec(&my_des_context, mykey);
	des_crypt_cbc(&my_des_context, DES_DECRYPT, 8, iv_de, myoutput, myinput);
	printf("after:\n");
	for (i=0; i<8; i++)
		printf("%x", myinput[i]);
	printf("\n*********\n\n");
	return 0;
}
