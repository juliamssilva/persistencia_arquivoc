#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int matricula;
    char nome[41];
    double nota1, nota2, nota3;
    double recuperacao;
} tDadosAlunos;

tDadosAlunos lerDadosAlunos() {
    tDadosAlunos dados;

    printf("Matricula: ");
    scanf("%d", &dados.matricula);
    printf("Nome: ");
    scanf("%s", dados.nome);

    return dados;
}

tDadosAlunos lerNotasAlunos(tDadosAlunos aluno) {
    printf("Nota 1: ");
    scanf("%lf", &aluno.nota1);
    printf("Nota 2: ");
    scanf("%lf", &aluno.nota2);
    printf("Nota 3: ");
    scanf("%lf", &aluno.nota3);
    
    return aluno;
}

double MediaFinal(tDadosAlunos aluno) {
    double media = (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3.0;
    if (media >= 7) {
        return media;
    } else if (media < 4) {
        return media;
    } else {
        double mediaf = ((media * 6) + (aluno.recuperacao * 4)) / 10;
        return mediaf;
    }
}

int Situacao(double nota) {
    if(nota >= 7) {
        return 1;
    } else {
        return 0;
    }
}

void salvarDadosAlunos(tDadosAlunos alunos[], int qntAlunos) {
    FILE *arquivo = fopen("dados_alunos.bin", "wb");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir.\n");
        return;
    }

    fwrite(alunos, sizeof(tDadosAlunos), qntAlunos, arquivo);
    
    fclose(arquivo);
}

void lerDadosAlunosArquivo(tDadosAlunos alunos[], int *qntAlunos) {
    FILE *arquivo = fopen("dados_alunos.bin", "rb");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir.\n");
        return;
    }

    fread(alunos, sizeof(tDadosAlunos), *qntAlunos, arquivo);
    
    fclose(arquivo);
}

int main() {
    char disciplina[51];
    int qntAlunos;

    puts("----------Seja Bem-Vindo!!----------");

    printf("Qual o nome da disciplina? ");
    fgets(disciplina, sizeof(disciplina), stdin);
    if (disciplina[strlen(disciplina) - 1] == '\n') {
        disciplina[strlen(disciplina) - 1] = '\0';
    }

    printf("Quantos alunos na turma? ");
    scanf("%d", &qntAlunos);

    if (qntAlunos > 30 || qntAlunos < 1) {
        puts("A quantidade máxima de alunos é 30");
        return 1;
    }

    tDadosAlunos alunos[qntAlunos];

    for (int i = 0; i < qntAlunos; i++) {
        alunos[i] = lerDadosAlunos();
    }
    
    for (int i = 0; i < qntAlunos; i++) {
        printf("Notas de %s:\n", alunos[i].nome);
        alunos[i] = lerNotasAlunos(alunos[i]);
    }

    for (int i = 0; i < qntAlunos; i++) {
        double media = (alunos[i].nota1 + alunos[i].nota2 + alunos[i].nota3) / 3.0;
        if (media >= 4.0 && media < 7.0) {
            printf("Nome: %s\n", alunos[i].nome);
            printf("Média Atual: %.2lf\n", media);
            printf("Nota da recuperação: ");
            scanf("%lf", &alunos[i].recuperacao);
        }
    }

    salvarDadosAlunos(alunos, qntAlunos);

    lerDadosAlunosArquivo(alunos, &qntAlunos);

    printf("\tDisciplina: %s\n", disciplina);
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("\tMatricula   Nome                 Nota1   Nota2   Nota3   Rec   Media   Situacao\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < qntAlunos; i++) {
        double resultado = MediaFinal(alunos[i]);
        printf("\t%05d       %-20s %.1lf    %.1lf    %.1lf    %.1lf    %.2lf    ", alunos[i].matricula, alunos[i].nome,
               alunos[i].nota1, alunos[i].nota2, alunos[i].nota3, alunos[i].recuperacao, resultado);
        if(Situacao(resultado) == 1) {
            printf("Aprovado\n");
        } else {
            printf("Reprovado\n");
        }
    }

    return 0;
}
