//tamaño direccion: 12bits

//linea: 3bits
//etiqueta: 5bits
//palabra: 4bits

// RAM

//bloques: 256
//tamaño: 4096 bytes

//CACHE correct direct

//tamaño cache = 128bytes
//lineas: 8
//tamaño de linea: 16bytes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define TAM_LINE 16
#define NUM_FILAS 8
//
//
//------------------ 16 bytes = 128 bits ETQ= 5bits data 
//
//
//
//
//
//
//
//
//
typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINE];
} T_CACHE_LINE;

int leerLinea(char nombre[], int linea, char* cadenaTemp);
void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int*palabra, int *linea, int *bloque);

int main (int argc, char* argv[]){

    //DECLARAMOS E INICIALIZAMOS TODO

    int globaltime=0,numfallos=0;

    T_CACHE_LINE tbl[16];

    unsigned char Simul_RAM[4096];
    
    char* cadenaTemp=malloc(1000 * sizeof(char*)); 
    char texto[100];

    unsigned int addr;
    int ETQ,palabra,linea,bloque;

    for(int i=0;i<16;i++){
        tbl[i].ETQ=0xFF;
        for(int j=0;j<TAM_LINE;j++){
            tbl[i].Data[j]=0x23;
        }
    }

    for (int i = 1; (leerLinea("CONTENTS_RAM.bin",i,cadenaTemp)) == 1 ; i++)
    {
        strcat(Simul_RAM,cadenaTemp);    
    }

    for (int i = 1; (leerLinea("accesos_memoria.txt",i,cadenaTemp)) == 1 ; i++)
    {

        // TENGO UN DIRECCION EN HEX
        // ETQ/LINEA/PALABRA
        ParsearDireccion(strtol(cadenaTemp, NULL, 16),&ETQ,&palabra,&linea,&bloque);
        if (tbl[linea].ETQ!=ETQ)
        {
            //Sumar fallo
            numfallos++;
            //Mensaje de fallo
            printf("T: %d, Fallo de CACHE %d, ADDR %04X Label %X linea %02X palabra %02X bloque %02X\n",globaltime,numfallos,addr,ETQ,linea,palabra,bloque);
            //Copiar el bloque de la ram
            printf("se está cargando el bloque %02X en la línea %02X\n",bloque,linea);
            //actulizar ETQ Y DATOS
            tbl[linea].ETQ=ETQ;
            for (int i = 0; i < TAM_LINE; ++i)
            {
                tbl[linea].Data[i]=Simul_RAM[bloque*TAM_LINE+i];
            }
        }
        //texto[i]=caracterLeido;
        VolcarCACHE(tbl);
        sleep(1);
    }
    //printf("T: %d, Acierto de CACHE, ADDR %04X Label%X linea %02X palabra %02X DATO %02X ",globaltime,addr,ETQ,linea,palabra,dato);
    return  0;
}

int leerLinea(char nombre[], int linea,char* cadenaTemp){

    FILE *archivo;

    archivo = fopen(nombre,"r");
    
    if (archivo == NULL)
    {
        printf("Error, mal nomnbre de archivo\n");
        exit(-1);
    }

    for (int i = 0; (i < linea); i++)
    {
        if (feof(archivo))
        {
            return -1;
        }

        fgets(cadenaTemp,4096,archivo); 
    } 

    fclose(archivo);

    return 1;
}

void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl){
    for (int i = 0; i < 8; i++)
    {
        printf("ETQ:FF DATA ",tbl[i].ETQ);
        for (int j = 0; j < 16; j++)
        {
            printf("%X ", tbl[i].Data[j]);
        }
        printf("\n");
    }
    printf("\n");
}
void ParsearDireccion(unsigned int addr, int *ETQ, int*palabra, int *linea, int *bloque){
    *palabra = addr & 0b1111;
    *bloque = addr >> 4;
    *linea = (*bloque & 0b111);
    *ETQ = (*bloque & 0b11111000)>>3;
}