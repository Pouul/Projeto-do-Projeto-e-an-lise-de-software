#include <stdio.h>
#include <string.h>

#define MAX 1000

int cache[MAX][MAX];

void Lcs(char S1[], char S2[], char LCS[])  {
    int n = strlen(S1);
    //linha n
    int m = strlen(S2);
    //coluna m
    // loop para percorrer o matriz
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // se qualquer um dos indices for 0 será 0 no índice
            if (i == 0 || j == 0){
                cache[i][j] = 0;
            }
            // se forem iguais pegamos o lcs anterior e somamos 1 para o novo comprimento de lcs
            else if (S1[i-1] == S2[j-1]){
                cache[i][j] = 1 + cache[i-1][j-1];
            }
            // verificamos qual o lcs anterior devemos pegar , o maior.
            else {
                cache[i][j] = (cache[i-1][j] > cache[i][j-1]) ? cache[i-1][j] : cache[i][j-1];
            }
        }
    }
    //reconstruindo o lcs
    // n e m são indice do último elemento que está armazenado o tamanho do LCS
    int index = cache[n][m];
    // \0 para marcar o final do string
    LCS[index] = '\0';
    int i = n, j = m;
    // enquando forem positivo
    while (i > 0 && j > 0) {
        // se achar coloca no último casa do LCS index-1
        if (S1[i-1] == S2[j-1]) {
            LCS[index-1] = S1[i-1];
            //subtrai os indice porque já achamos os iguais, 
            //menos caractere considerado e restante no LCS
            i--; 
            j--; 
            index--;
        } 

        //Tento considerado menos caractere cosiderado 
        //qual o caminho que possui maior LCS
        //se LCS ao considerar menos caractere do S1 for maior que o LCS
        //considerando menos caractere do S2
        //considere que tenha menos caractere no S1
        //caso contrário considere menos carctere no S2
        else if (cache[i-1][j] > cache[i][j-1]) 
            i--;
        else
            j--;
    }
    
     
    

    
}


int main() {
    //declaração do variaveis
    FILE *arquivo;         
    char S1[MAX]; 
    char S2[MAX];
    S1[0] = '\0';
    S2[0] = '\0';
    char LCS[MAX];
    char buffers1[MAX];   
    char buffers2[MAX];

    //arquivo recebe o endereço do txt e tem direito de ler
    arquivo = fopen("string1.txt", "r");
    
    //verificar se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    //enquando não for última linha pega conteudo da 
    //linha acha as quebra linhas e tira,
    //depois concatena o conteúdo do buffer no s1
    while (fgets(buffers1, sizeof(buffers1), arquivo) != NULL) {
        buffers1[strcspn(buffers1, "\n")] = '\0';
        strcat(S1, buffers1);
    }
    
    // fechar o arquivo
    fclose(arquivo);

    
    //arquivo recebe o endereço do txt e tem direito de ler
    arquivo = fopen("string2.txt", "r");

    //verificar se arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    //enquando não for última linha pega conteudo da 
    //linha acha as quebra linhas e tira,
    //depois concatena o conteúdo do buffer no s2
    while (fgets(buffers2, sizeof(buffers2), arquivo) != NULL) {
        buffers2[strcspn(buffers2, "\n")] = '\0';
        strcat(S2, buffers2);
    }
    // fechar o arquivo
    fclose(arquivo);

    Lcs( S1,  S2, LCS);

    printf("LCS dos Strings: %s\n", LCS);

    return 0;
}
