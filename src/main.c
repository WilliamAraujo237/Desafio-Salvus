#include <stdio.h>
#include <string.h>

#define MAX_funcionarioRegistro 100

//Struct, construtor para funcionarioRegistro
typedef struct {
    char nome[50];
    char contrato[12];
    float salario;
    int horas;
    int contratosAssinadosQTD;
    int valorBonos;
    float salarioComBonos;
} Funcionario;

void RegistraFuncionario(Funcionario funcionarioRegistro[], int *contador) {
    //Variaveis locais utilizadas no código
    char continuar = 's';
    float valorFixoCLT = 3000.00;
    int valorFixoPorHora = 50;

    while (continuar == 's' || continuar == 'S') {
        if (*contador >= MAX_funcionarioRegistro) {
            printf("Limite de funcionarioRegistro atingido.\n");
            break;
        }

        // Adiciona o nome e o tipo de contrato do funcionario 
        printf("Digite o nome do funcionario: ");
        fgets(funcionarioRegistro[*contador].nome, sizeof(funcionarioRegistro[*contador].nome), stdin);
        funcionarioRegistro[*contador].nome[strcspn(funcionarioRegistro[*contador].nome, "\n")] = 0;

        printf("Digite o contrato do funcionario (CLT ou PJ): ");
        fgets(funcionarioRegistro[*contador].contrato, sizeof(funcionarioRegistro[*contador].contrato), stdin);
        funcionarioRegistro[*contador].contrato[strcspn(funcionarioRegistro[*contador].contrato, "\n")] = 0;

        // Adiciona o valor do salario baseado no contrato (CLT ou PJ)
        if (strcasecmp(funcionarioRegistro[*contador].contrato, "CLT") == 0) {
            QuantidadeDeHorasTrabalhadas(funcionarioRegistro,*contador);
            funcionarioRegistro[*contador].salario = valorFixoCLT;
            BonosPorContratoAssinado(funcionarioRegistro, *contador);

        } else if (strcasecmp(funcionarioRegistro[*contador].contrato, "PJ") == 0) {
            QuantidadeDeHorasTrabalhadas(funcionarioRegistro,*contador);
            funcionarioRegistro[*contador].salario = funcionarioRegistro[*contador].horas * valorFixoPorHora;
            BonosPorContratoAssinado(funcionarioRegistro,*contador);
        } else {
            printf("Tipo de contrato invalido.\n");
            continue; // Pula o incremento do contador e volta ao início do loop
        }

        // Incrementa o contador para refletir o novo funcionário registrado
        (*contador)++;

        printf("Deseja continuar registrando? (s/n): ");
        scanf(" %c", &continuar);
        getchar();  // Limpa o buffer de entrada
    }
}

// Adiciona um bônus para cada contrato assinado
void BonosPorContratoAssinado(Funcionario funcionarioRegistro[], int contador){
    int valorCalculoBonus = 200;

    printf("Quantos contratos o funcionario assinou? : ");
    scanf("%d", &funcionarioRegistro[contador].contratosAssinadosQTD);
    getchar(); 
    funcionarioRegistro[contador].valorBonos = funcionarioRegistro[contador].contratosAssinadosQTD * valorCalculoBonus;
    funcionarioRegistro[contador].salarioComBonos = funcionarioRegistro[contador].valorBonos + funcionarioRegistro[contador].salario;
}

// Adiciona a quantidade de horas trabalhadas
void QuantidadeDeHorasTrabalhadas (Funcionario funcionarioRegistro[], int construtor){

    printf("Digite a quantidade de horas trabalhadas: ");
    scanf("%d", &funcionarioRegistro[construtor].horas);
    getchar();

}

int main() {
    Funcionario funcionarioRegistro[MAX_funcionarioRegistro];
    int contador = 0;  // Contador para manter o número de funcionários registrados
    float folhaDePagamento = 0;

    // Passamos o endereço de 'contador' para que a função possa modificá-lo diretamente
    RegistraFuncionario(funcionarioRegistro, &contador);

    printf("\nfuncionarioRegistro registrados:\n");
    for (int i = 0; i < contador; i++) {
        printf("||==========================================||\n");
        printf("|| Funcionario %d:\n", i + 1);
        printf("|| Nome: %s\n", funcionarioRegistro[i].nome);
        printf("|| Contrato: %s\n", funcionarioRegistro[i].contrato);
        printf("|| Salario: %.2f\n", funcionarioRegistro[i].salario);
        printf("|| Horas trabalhadas: %d\n", funcionarioRegistro[i].horas);
        printf("|| Quantidade de contratos assinados: %d\n", funcionarioRegistro[i].contratosAssinadosQTD);
        printf("|| Salario com bonus: %.2f\n", funcionarioRegistro[i].salarioComBonos);

        folhaDePagamento += funcionarioRegistro[i].salarioComBonos;
    }
    printf("||==========================================||\n");
    printf("|| Folha de pagamento: %.2f\n", folhaDePagamento);
    printf("||==========================================||\n");
    return 0;
}