#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "avl.h"
#include <time.h>


/* Exemplo de uso dos argumentos para main
O programa l� um arquivo texto como entrada e gera um arquivo como sa�da com o conte�do do arquivo de entrada convertido para letras mai�sculas
Para chamar, digite "exemplo entrada.txt saida.txt" */




int main(int argc, char *argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
    clock_t start, end, elapsed; //para contar o tempo
//    int lineno=0;


    FILE * entrada;
    FILE * saida;
    FILE * procura;
    pNodoA *arv = NULL;
    int ok, verifica = 0;
    int achou = 0;
    int loop_flag = 0;
    TipoInfo chave;
    char palavra2[20];

//    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
//    char separador[]= {" 0123456789,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    if (argc!=4)  ///o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf ("N�mero incorreto de par�metros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {
        entrada = fopen(argv[1], "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
        if (entrada==0) //se n�o conseguiu abrir o arquivo
        {
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }
        else // arquivo de entrada OK
        {
            saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] � o segundo par�metro ap�s o nome do arquivo.
            start=clock(); //inicia a contagem do tempo;

            //percorre todo o arquivo lendo linha por linha
            while (!feof(entrada))
            {
                if(fscanf(entrada,"%lld %s", &chave, palavra2) == 2)
                {
                    arv = InsereAVL(arv, chave, palavra2 ,&ok);
                }
            }
            procura = fopen(argv[2],"r");
            if(procura==NULL)
            {
                printf("Lista de palavras para consulta não encontrada");
            }
            else
            {
                while(!feof(procura))
                {
                    if(fscanf(procura,"%s", palavra2) == 1)
                    {
                        fprintf(saida, "%s\n", palavra2);
                        achou = busca(arv, palavra2, saida);
                        printf("Valor de achou: %d\n",achou);
                        if(achou == 1)
                        {
                            loop_flag+=1;
                        }
                        if(achou == 0 && loop_flag == 0)
                        {
                            fprintf(saida,"%s","Nenhum Resultado Encontrado\n");
                        }
                    }
                    fprintf(saida,"%s","\n\n");

                }
                //    printf("digite a palavra a ser procurada");
                //    fflush(stdin);
                //    gets(palavra2);
            }
            /**
            while (fscanf(entrada,"%d %s", &arv->info, gets(palavra)))
            {
                arv = InsereAVL(arv, 42,&ok);
                palavra = strtok (linha, separador); ///considera qquer caractere n�o alfab�tico como separador
                while (palavra != NULL)
                {
                    fprintf(saida," %s", strlwr(palavra)); ///strlwr � a fun��o que converte palavras para min�sculo
                    palavra = strtok (NULL, separador);
                }
            }*/
            end=clock(); //l� o tempo final
            elapsed = 1000 * (end - start) / (CLOCKS_PER_SEC); //calcula o tempo decorrido em milissegundos
            printf("\nO tempo gasto no processamento do arquivo %s foi de %ld ms\n",argv[1],elapsed);
            printf("\nArquivo %s gerado com sucesso.\n",argv[2]);
        }
        fclose (entrada); //fecha os arquivos
        fclose (saida);
        return 0;
    }
}

