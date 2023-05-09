#include <stdlib.h>
#include <stdio.h>
#include "matrizes.h"

//Definido as dimens�es da matriz complexa
int linhas = 3;
int colunas = 2;

/*
A fun��o est� sendo chamada para alocar mem�ria para a matriz complexa, 
retornando a vari�vel mtx do tipo complexMatrix
*/
complexMatrix mtx = allocateComplexMatrix(linhas, colunas);

//Preenchendo a matriz complexa
for (int l = 0; l < mtx.linhas; ++l) {
    for (int c = 0; c < mtx.colunas; ++c) {
        mtx.mtx[l][c].real = 2 * l;
        mtx.mtx[l][c].imag = 2 * c;
    }
}

//Imprimindo o valor da matriz complexa
for (int l = 0; l < mtx.linhas; ++l) {
    for (int c = 0; c < mtx.colunas; ++c) {
        printf("mtx[%d][%d]: ", l, c);
        printComplex(mtx.mtx[l][c]);
    }
}

/*
Agora a fun��o que foi chamada anteriormente vai alocar mem�ria
para a matriz complexa
*/
complexMatrix allocateComplexMatrix(int linhas, int colunas) {
    
    complexMatrix matrix; //Criando a vari�vel matrix do tipo complexMatrix
    matrix.linhas = linhas;
    matrix.colunas = colunas;

    /*
    Reservando a quantidade de mem�ria necess�ria para armazenar as linhas
    da matriz complexa 
    */
    matrix.mtx = (complex**)malloc(linhas * sizeof(complex*));
    
    //Caso haja algum erro na aloca��o, o programa � interrompido
    if (matrix.mtx == NULL) {
        printf("Falha na aloca��o de mem�ria\n");
        exit(1);
    }

    /*
    Esse la�o est� percorrendo cada linha da matriz e alocando mem�ria
    para as colunas correspondentes
    */
    for (int i = 0; i < linhas; i++) {
        matrix.mtx[i] = (complex*)malloc(colunas * sizeof(complex));
        
        /*
        Esse if vai verificar se houve algum erro na aloca��o da mem�ria, assim como o anterios,
        no entando, essa estrutura vai liberar a mem�ria e depois encerrar o programa caso esse
        erro ocorra.
        */
        if (matrix.mtx[i] == NULL) {
            printf("Falha na aloca��o de mem�ria\n");

            for (int j = 0; j < i; j++) { //Percorre as linhas anteriores a 'i'
                free(matrix.mtx[j]);//Libera a mem�ria alocada para as colunas das linhas
            }
            free(matrix.mtx);//Libera a mem�ria alocada para as linhas

            exit(1);
        }
    }

    return matrix;
}

complexMatrix matrixTransposta(complexMatrix matrix) {
    
    complexMatrix transposta; //Declara��o da matriz
    
    transposta.linhas = matrix.colunas; //Atribuindo o n�merro de linhas a transposta
    transposta.colunas = matrix.linhas;//Agora o n�mero de colunas

    //Alocandoo mem�ria para as linhas da transposta
    transposta.mtx = (complex**)malloc(transposta.linhas * sizeof(complex*));
    if (transposta.mtx == NULL) {
        printf("Falha na aloca��o de mem�ria\n");
        exit(1);
    }

    //Alocando mem�ria para as colunas da transposta
    for (int i = 0; i < transposta.colunas; i++) {
        transposta.mtx[i] = (complex**)malloc(transposta.linhas * sizeof(complex*));
        if(transposta.mtx[i] == NULL) {
            printf("Falha na aloca��o de mem�ria\n");
            for (int j = 0; j<i; j++) {
                free(transposta.mtx[j]);
            }
                free(transposta.mtx);
                exit(1);
        }   
    }

    //Passandos os valores da matriz original para a transposta
    for (int i = 0; i < matrix.linhas; i++) {
        for (int j = 0; j < matrix.colunas; j++) {
            transposta.mtx[j][i].real =  matrix.mtx[i][j].real;
            transposta.mtx[j][i].imag = matrix.mtx[i][j].imag;
        }
    }

    return transposta;
}