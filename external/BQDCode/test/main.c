#include "bqdcode.h"

int main(){
     struct Barcode_Item * bc;
     bc = BQDBarcode_Create("123456789012");
     FILE * QF = fopen("test.txt","w");
     BQDBarcode_Print(bc,QF,BARCODE_NO_ASCII);
     printf("Barcode test finish!");
    
}