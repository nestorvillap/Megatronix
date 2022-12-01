//bus 12
//cache 8 lineas correct direct 16 bytes por linea

//palabra 4
//linea 3
//etiqueta 5


#include <stdio.h>
#include <stdlib.h>

#define TAM_LINE 3
#define NUM_FILAS 3

typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINE];
} T_CACHE_LINE;

void leerArchivo(char nombre[],unsigned char contenido[]);
void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int*palabra, int *linea, int *bloque);

int main (int argc, char* argv[]){

    //DECLARAMOS E INICIALIZAMOS TODO

    int globaltime=0,numfallos=0;

    T_CACHE_LINE linea[16];

    unsigned char Simul_RAM[4096];

    for(int i=0;i<16;i++){
        linea[i].ETQ=0xFF;
        for(int j=0;j<TAM_LINE;j++){
            linea[i].Data[j]=(unsigned char)0x23f;
        }
    }
    
    leerArchivo("CONTENTS_RAM.bin",Simul_RAM);

    //Leer dirs_memoria.txt
        //LINEA = DIRECCION -> LEER 1
        //OBT NUM LINEA ?= LABEL
            //SI NO NUMFALLOS++
            //T: %d, Acierto de CACHE, ADDR %04X Label%X linea %02X palabra %02X DATO %02X // T ES INSTANTE=GLOBALTIME // GLOBALTIME ++
            //cada caracter leido se añade a texto[100]
            //VOLVAR CONTENIDO DE LA CACHE == HACER LA TABLA
            //SLEEP 1
    //REPETIR TODAS LAS LINEAS

    return  0;
}

void leerArchivo(char nombre[],unsigned char contenido[]){

    FILE    *infile;
    long    numbytes;

    infile = fopen(nombre, "r");

    if(infile == NULL){
        printf("Error con el nombre del archivo\n");
        exit(-1);
    }  

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    
    fseek(infile, 0L, SEEK_SET);    
     
    fread(contenido, sizeof(char), numbytes, infile);
    fclose(infile);

}
void LimpiarCACHE(T_CACHE_LINE tbl[NUM_FILAS]);
void VolcarCACHE(T_CACHE_LINE *tbl);
void ParsearDireccion(unsigned int addr, int *ETQ, int*palabra, int *linea, int *bloque);
