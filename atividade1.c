#include <stdio.h>

void iniciar_menu() {
    printf("Escolha uma opção \n");
    printf("(1) - Resultados \n");
    printf("(2) - Aprovados \n");
    printf("(3) - Reprovados \n");
    printf("(4) - Porcentagens \n");
    printf("(5) - Sair \n");
}

int resultado(FILE *arqEntrada) {
    float nota, maior_nota, menor_nota;
    FILE *arqResultado;

    rewind(arqEntrada);

    if (fscanf(arqEntrada, "%f", &nota) != 1) {
        printf("Erro na leitura do arquivo.\n");
        return 1;
    }

    maior_nota = nota;
    menor_nota = nota;

    while (fscanf(arqEntrada, "%f", &nota) == 1) {
        if (nota > maior_nota) {
            maior_nota = nota;
        }
        if (nota < menor_nota) {
            menor_nota = nota;
        }
    }

    arqResultado = fopen("Resultado.txt", "w");
    if (arqResultado == NULL) {
        printf("Erro na abertura do arquivo de resultado.\n");
        return 1;
    }

    fprintf(arqResultado, "\n Maior Nota: %.2f\n\n", maior_nota);
    fprintf(arqResultado, "\n Menor Nota: %.2f\n\n", menor_nota);

    fclose(arqResultado);
    return 0;
}

int aprovados(FILE *arqEntrada) {
    int aprovados = 0;
    float nota;
    FILE *arqAprovado;

    rewind(arqEntrada);

    fscanf(arqEntrada, "%f", &nota);
    while(!feof(arqEntrada)){
        if (nota >= 7) {
            aprovados++;
        }
        fscanf(arqEntrada, "%f", &nota);
    }

    arqAprovado = fopen("Aprovados.txt", "w");
    if (arqAprovado == NULL) {
        printf("Erro na abertura do arquivo de aprovados.\n");
        return 1;
    }

    fprintf(arqAprovado, "\n Numero de alunos aprovados: %d", aprovados);

    fclose(arqAprovado);
    return 0;
}

int reprovados(FILE *arqEntrada) {
    int reprovados = 0;
    float nota, soma = 0.0, media_reprovados = 0.0;
    FILE *arqReprovados;

    rewind(arqEntrada);

    if (fscanf(arqEntrada, "%f", &nota) != 1) {
        printf("Erro na leitura do arquivo.\n");
        return 1;
    }

    while (fscanf(arqEntrada, "%f", &nota) == 1) {
        if (nota < 7) {
            reprovados++;
            soma = soma + nota;
        }
    }

    if (reprovados > 0) {
        media_reprovados = soma / reprovados;
    }

    arqReprovados = fopen("Reprovados.txt", "w");
    if (arqReprovados == NULL) {
        printf("Erro na abertura do arquivo de reprovados.\n");
        return 1;
    }

    fprintf(arqReprovados, "\n Numero de alunos reprovados: %d \n\n", reprovados);
    if (reprovados > 0) {
        fprintf(arqReprovados, "\n Media dos alunos reprovados: %.2f \n\n", media_reprovados);
    }

    fclose(arqReprovados);
    return 0;
}

int porcentagem(FILE *arqEntrada) {
    int total_alunos = 0, aprovados = 0, reprovados = 0;
    float nota, porcentagem_reprovado, porcentagem_aprovado, total_float;
    FILE *arqPorcentagem;
    rewind(arqEntrada);

    fscanf(arqEntrada, "%f", &nota);
    while(!feof(arqEntrada)){
        if (nota < 7) {
            reprovados++;
        }else{
            aprovados++;
        }
        total_alunos++;
        fscanf(arqEntrada, "%f", &nota);
    }

    total_float = total_alunos;
    porcentagem_reprovado = (reprovados / total_float) * 100;
    porcentagem_aprovado = (aprovados / total_float) * 100;

    arqPorcentagem = fopen("Porcentagens.txt", "w");
    fprintf(arqPorcentagem, "\n Porcentagem Reprovados: %.2f \n\n", porcentagem_reprovado);
    fprintf(arqPorcentagem, "\n Porcentagem Aprovados: %.2f \n\n", porcentagem_aprovado);
    fclose(arqPorcentagem);
    return 0;
}

int main() {
    int escolhaMenu, parada = 0;
    FILE *arqEntrada;
    arqEntrada = fopen("Notas.txt", "r");

    if (arqEntrada == NULL) {
        printf("\n Erro na abertura do arquivo! \n\n");
        return 1;
    }

    while (parada == 0) {
        iniciar_menu();
        scanf("%d", &escolhaMenu);

        switch (escolhaMenu) {
        case 1:
            printf("Resultado.txt criado com sucesso!\n");
            resultado(arqEntrada);
            break;

        case 2:
            printf("Aprovados.txt criado com sucesso!\n");
            aprovados(arqEntrada);
            break;

        case 3:
            printf("Reprovados.txt criado com sucesso!\n");
            reprovados(arqEntrada);
            break;

        case 4:
            printf("Porcentagens.txt criado com sucesso!\n");
            porcentagem(arqEntrada);
            break;

        case 5:
            printf("Fim!\n");
            parada = 1;
            break;

        default:
            printf("Essa escolha não existe...\n");
        }

        printf("\n\n");
    }

    if (arqEntrada != NULL) {
        fclose(arqEntrada);
    }

    return 0;
}
