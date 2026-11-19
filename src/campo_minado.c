#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    int pos_c, pos_l, nivel, quantbombas, bombas, linha, coluna;
    int tabuleiro[15][15] = {0};
    int direcao_jogada;


    srand(time(NULL));

    //definir nível de dificuldade
    printf("Digite o nivel de dificuldade desejado (entre 1 e 3): ");
    scanf("%d", &nivel);
    switch (nivel)
    {
        case 1:
            quantbombas = 0.1*225;
            break;
        case 2:
            quantbombas = 0.2*225;
            break;
        case 3:
            quantbombas = 0.3*225;
            break;
        default:
            printf("Nivel invalido!");
            break;
    }

    //bombas em locais aleatórios
    for(bombas=1; bombas<=quantbombas; bombas++){
        
        //Gerando numeros alrtorio entre 0 e 14
        linha = rand() % 14;
        coluna = rand() % 14;
        tabuleiro[linha][coluna] = 1; //1 = bomba  
    }

    //inicializacao aleatoria na borda
    pos_l = rand() % 14;
    pos_c = 0;
    tabuleiro[pos_l][pos_c] = -1;

    //jogabilidade
    while(pos_c<14){
        if (tabuleiro[pos_l][pos_c] == 1){
            for (int m = 0; m < 15; ++m) { //linha
                for (int n = 0; n < 15; ++n) { //coluna
                    if (tabuleiro[m][n] == -1){
                        printf("[X]");
                    }
                    else if (tabuleiro[m][n] == 1){
                        printf("[*]");
                    }
                    else{
                        printf("[ ]");
                    }
                }
                printf("\n");
            }
            printf("BOMBA! Perdeu o jogo");
            break;
        }
        else{
            tabuleiro[pos_l][pos_c] = -1;
            for (int m = 0; m < 15; ++m) { //linha
                for (int n = 0; n < 15; ++n) { //coluna
                    if (tabuleiro[m][n] == -1){
                        printf("[X]");
                    }
                    else {
                        printf("[ ]");
                    }
                }
                printf("\n");
            }
            printf("Escolha a direcao da proxima jogada - digite 1 para andar para direita, 2 para andar em diagonal para cima e 3 para andar em diagonal para baixo: ");
            scanf("%d", &direcao_jogada);
            
            if(direcao_jogada == 1){
                pos_c = pos_c + 1;
                pos_l = pos_l + 0;
            }
            else if(direcao_jogada == 2){
                pos_c = pos_c + 1;
                pos_l = pos_l - 1;
            }
            else if(direcao_jogada == 3){
                pos_c = pos_c + 1;
                pos_l = pos_l + 1;
            }
        }
    }

    if(pos_c == 14){
        tabuleiro[pos_l][pos_c] = -1;
        for (int m = 0; m < 15; ++m) { //linha
            for (int n = 0; n < 15; ++n) { //coluna
                if (tabuleiro[m][n] == -1){
                    printf("[X]");
                }
                else {
                    printf("[ ]");
                }
                }
            printf("\n");
            }
        
        printf("Voce ganhou o jogo!");
    }
    return 0;
}
    