#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10
#define TAMANHO_SEGUNDO_NIVEL 11/10

typedef struct Objeto {
    int chave;  
    struct Objeto* proximo;
} Objeto;


typedef struct TabelaHash {
    Objeto* primeiro_nivel[TAMANHO_TABELA];
    Objeto* segundo_nivel[TAMANHO_TABELA][TAMANHO_SEGUNDO_NIVEL];
    
} TabelaHash;


int hash_primeiro_nivel(int chave) {
    return chave % TAMANHO_TABELA;
}

int hash_segundo_nivel(int chave) {
    return (chave / TAMANHO_TABELA) % TAMANHO_SEGUNDO_NIVEL;
}

void inserir(TabelaHash* tabela, Objeto* objeto) {
    int indice_primeiro_nivel = hash_primeiro_nivel(objeto->chave);
    int indice_segundo_nivel = hash_segundo_nivel(objeto->chave);
    
    if (tabela->segundo_nivel[indice_primeiro_nivel][indice_segundo_nivel] == NULL) {
        tabela->segundo_nivel[indice_primeiro_nivel][indice_segundo_nivel] = objeto;
    } else {
        Objeto* atual = tabela->segundo_nivel[indice_primeiro_nivel][indice_segundo_nivel];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = objeto;
    }
}

Objeto* obter(TabelaHash* tabela, int chave) {
    int indice_primeiro_nivel = hash_primeiro_nivel(chave);
    int indice_segundo_nivel = hash_segundo_nivel(chave);
    
    Objeto* lista = tabela->segundo_nivel[indice_primeiro_nivel][indice_segundo_nivel];
    while (lista != NULL) {
        if (lista->chave == chave) {
            return lista;
        }
        lista = lista->proximo;
    }
    return NULL;
}

int calcular_chave(const char* nome) {
    int chave = 0;
    while (*nome != '\0') {
        chave += *nome;
        nome++;
    }
    return chave;
}

int main() {
    TabelaHash tabela;
    
    const char* nomes[] = {"João", "Marco", "Marina", "Julia", "Antonio", "Jose"};

    for (int i = 0; i < 6; i++) {
        Objeto* objeto = (Objeto*)malloc(sizeof(Objeto));
        objeto->chave = calcular_chave(nomes[i]);
        objeto->proximo = NULL;
        inserir(&tabela, objeto);
    }
    
    
    char nome[50];

    while (1) {
        printf("Insira um nome considerando a figura da especificação da atividade (ou digite 'sair' para encerrar): ");
        scanf("%s", nome);

        if (strcmp(nome, "sair") == 0) {
            break;
        }

        Objeto* objeto = (Objeto*)malloc(sizeof(Objeto));
        objeto->chave = calcular_chave(nome);
        objeto->proximo = NULL;
        inserir(&tabela, objeto);

        int indice_primeiro_nivel = hash_primeiro_nivel(objeto->chave);
        int indice_segundo_nivel = hash_segundo_nivel(objeto->chave);

        printf("%s está na posição %d do primeiro nível e posição %d do segundo nível.\n", nome, indice_primeiro_nivel, indice_segundo_nivel);
    }

    return 0;
}

