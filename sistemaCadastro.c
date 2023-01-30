#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

typedef struct Aniversario{
    int dia;
    int mes;
    int ano;
}aniversario;

typedef struct Funcionario{
    aniversario niver;
    int n_registro;
    char nome[100];
    float salario;
}funcionario;

typedef struct Noh{
    funcionario dados;
    struct Noh *proximo;
}Noh;

typedef struct Lista{
    Noh* inicio;
    Noh* final;
}lista;

lista li;

void insereLista(int n_registro, char nome[100], int dia, int mes, int ano, float salario)
{
    Noh *p = (Noh*)malloc(sizeof(Noh));
    strcpy(p->dados.nome, nome);
    p->dados.n_registro = n_registro;
    p->dados.niver.dia = dia;
    p->dados.niver.mes = mes;
    p->dados.niver.ano = ano;
    p->dados.salario = salario;

    p->proximo = NULL;

    if(li.inicio == NULL){
        li.inicio = p;
    }else{
        li.final->proximo = p;
    }

    li.final = p;

}

void imprimir(void)
{
    Noh *p = li.inicio;

    if(p != NULL){
        while(p != NULL){
            printf("----------------------------------------------\n");
            printf("Número de registro: #%d\n", p->dados.n_registro);
            printf("Funcionário: %s\n", p->dados.nome);
            printf("Data de nascimento: %d/%d/%d\n", p->dados.niver.dia, p->dados.niver.mes, p->dados.niver.ano);
            printf("Salário atual: R$%.2f\n", p->dados.salario);
            printf("----------------------------------------------\n");
            
            p = p->proximo;
        }
    }else{
        printf("Sem registro de funcionários!");
    }

}

int deletar()
{
    int numero;
    Noh *p = li.inicio;

    if(p == NULL){
        printf("Sem registro de funcionários!");
        return 0;
    }else{
        printf("Registro a ser removido: ");
        scanf("%d", &numero);

        Noh *anterior = NULL;
        Noh *atual = p;

        while(atual != NULL && atual->dados.n_registro != numero){
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual == NULL){
            printf("Registro não encontrado!");
            return 0;
        }

        if(atual == p){
            p = atual->proximo;
    
        }else{
            anterior->proximo = atual->proximo;
        }

        free(atual);

        printf("\n\n");
        printf("Registro %d removido com sucesso!", numero);
        
        return 0;
        
    }
}

int editar()
{
    char nome[100];
    int dia, mes, ano, n_registro, numero;
    float salario;

    Noh *p = li.inicio;
    if(p == NULL){
        printf("Sem registros de funcionários!");
        return 0;
    }else{
        printf("Registro a ser editado: ");
        scanf("%d", &numero);

        Noh *anterior = NULL;
        Noh *atual = p;

        while(atual != NULL && atual->dados.n_registro != numero){
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual == NULL){
            printf("Registro não encontrado!");
            return 0;
        }

        printf("-----------------------------------------------------------\n");
        printf("Nome do funcionário: ");
        fflush(stdin);
        scanf("%s", &atual->dados.nome);
        printf("\n");
        printf("Data de nascimento (dd/mm/aaaa)\n");
        printf("Dia: ");
        scanf("%d", &atual->dados.niver.dia);
        printf("Mês: ");
        scanf("%d", &atual->dados.niver.mes);
        printf("Ano: ");
        scanf("%d", &atual->dados.niver.ano);
        printf("\n");
        printf("Informe o salário atual (use virgula se precisar): ");
        scanf("%f", &atual->dados.salario);
        printf("-----------------------------------------------------------\n\n");
        
        printf("Cadastro editado com sucesso!");

        return 0;
    }
}

void liberaLista()
{
    if(li.inicio != NULL){
        Noh* noh;
        while(li.inicio != NULL){
            noh = li.inicio;
            li.inicio = li.inicio->proximo;
            free(noh);
        }
        free(li.inicio);
    }
}

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    int decisao, dia, mes, ano, numero, n_registro = 0;
    float salario;
    char nome[100];

    do{
        system("cls");
        printf("----------Sistema de Cadastro de Funcionários----------");
        printf("\n\n");
        printf("\tMenu principal\n\n");
        printf("[0] - Sair\n[1] - Registrar funcionário\n[2] - Registros\n[3] - Deletar registro\n[4] - Editar registro\n\n");
        printf("Opção: ");
        scanf("%d", &decisao);
        system("cls");

        switch(decisao){
            case 0:
                liberaLista();
                printf("Encerrando Sistema de Cadastro...");
                Sleep(1500);
                break;

            case 1:
                n_registro++;
                printf("-----------------------------------------------------------\n");
                printf("Número de regristro do funcionário: #%d\n", n_registro);
                printf("Nome do funcionário: ");
                fflush(stdin);
                gets(nome);
                printf("\n");
                printf("Data de nascimento (dd/mm/aaaa)\n");
                printf("Dia: ");
                scanf("%d", &dia);
                printf("Mês: ");
                scanf("%d", &mes);
                printf("Ano: ");
                scanf("%d", &ano);
                printf("\n");
                printf("Informe o salário atual (use virgula se precisar): ");
                scanf("%f", &salario);
                printf("-----------------------------------------------------------\n\n");

                insereLista(n_registro, nome, dia, mes, ano, salario);

                printf("Cadastro realizado com sucesso!");
                printf("\n\n");

                system("pause");
                break;

            case 2:
                imprimir();
                printf("\n\n");
                system("pause");
                break;
            
            case 3:
                deletar();
                printf("\n\n");
                system("pause");
                break;
            
            case 4:
                editar();
                printf("\n\n");
                system("pause");
                break;

            default:
                printf("Opção Inválida!\n\n");
                system("pause");
                break;
        }
    }while(decisao != 0);

    return 0;

}
