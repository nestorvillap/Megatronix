//bus 12
//cache 8 lineas correct direct 16 bytes por linea

//palabra 4
//linea 3
//etiqueta 5


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINE 3
#define NUM_FILAS 3

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

    T_CACHE_LINE linea[16];

    unsigned char Simul_RAM[4096];

    char* cadenaTemp=malloc(1000 * sizeof(char*)); 
    char texto[100];

    for(int i=0;i<16;i++){
        linea[i].ETQ=0xFF;
        for(int j=0;j<TAM_LINE;j++){
            linea[i].Data[j]=(unsigned char)0x23f;
        }
    }

    for (int i = 1; (leerLinea("CONTENTS_RAM.bin",i,cadenaTemp))==1 ; i++)
    {
        strcat(Simul_RAM,cadenaTemp);    
    }
    
    printf("%s\n",Simul_RAM);

    for (int i = 1; (leerLinea("accesos_memoria.txt",i,cadenaTemp))==1 ; i++)
    {
        //linea == direccion
        //obtener num linea
        //if (numlinea!=label)
        // {
        //     numfallos++;
        // }
        //printf("T: %d, Acierto de CACHE, ADDR %04X Label%X linea %02X palabra %02X DATO %02X ");
        //texto[i]=caracterLeido;
        //VOLCAR CONTENIDO DE LA CACHE==HACER LA TABLA
        //sleep(1);
    }
    
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
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int*palabra, int *linea, int *bloque);