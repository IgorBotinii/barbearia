#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int sair = 0;
char cpf_logado[20];
char login_logado[50];

void listarBarbeiros() {
    FILE *arquivo = fopen("barbeiros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de barbeiros!\n");
        return;
    }

    char linha[100];
    printf("Barbeiros Disponiveis:\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char loginArquivo[50], nomeBarbeiro[50];
        sscanf(linha, "LOGIN: %s\tSENHA: %*s\tNOME BARBEIRO: %s", loginArquivo, nomeBarbeiro);
        printf("- %s \n", nomeBarbeiro);
         printf("\n");
    }

    fclose(arquivo);
}

int verificarBarbeiro(const char *nomeBarbeiro) {
    FILE *arquivo = fopen("barbeiros.txt", "r");
    if (arquivo == NULL) {
        return 0;
    }

    char linha[100], nomeArquivo[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "LOGIN: %*s\tSENHA: %*s\tNOME BARBEIRO: %s", nomeArquivo);
        if (strcmp(nomeBarbeiro, nomeArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

void horariosdisponiveis(char horarios[][10], int *numHorarios) {
    strcpy(horarios[0], "15:00");
    strcpy(horarios[1], "16:00");
    strcpy(horarios[2], "17:00");
    strcpy(horarios[3], "18:00");
    strcpy(horarios[4], "19:00");
    strcpy(horarios[5], "20:00");
    *numHorarios = 6; // Define o numeros de Horarios disponiveis
}
    void agendarCorte(const char *cpf) {
        listarBarbeiros();

        // Criar uma matriz para armazenar os horarios
        char horarios[6][10];
        int numHorarios = 0;
        horariosdisponiveis(horarios, &numHorarios);

        printf("horarios disponiveis:\n");
        for (int i = 0; i < numHorarios; i++) {
            printf("%d. %s\n", i + 1, horarios[i]);
        }

        char nomeBarbeiro[50];
        printf("Digite o nome do barbeiro que deseja agendar (ou 0 para cancelar): ");
        fgets(nomeBarbeiro, sizeof(nomeBarbeiro), stdin);
        nomeBarbeiro[strcspn(nomeBarbeiro, "\n")] = '\0';

        if (strcmp(nomeBarbeiro, "0") == 0) {
            printf("Agendamento cancelado.\n");
            return;
        }

        // Verificar se o barbeiro existe
        if (!verificarBarbeiro(nomeBarbeiro)) {
            printf("O barbeiro %s nao existe.\n", nomeBarbeiro);
            return;
        }

        // Adicionar a seleção de horario
        int indiceHorario;
        printf("Selecione o horario (1 a 6): ");
        scanf("%d", &indiceHorario);
        getchar(); // Limpar o buffer do stdin

        if (indiceHorario < 1 || indiceHorario > numHorarios) {
            printf("horario invalido.\n");
            return;
        }
    FILE *agendamentoArquivo = fopen("agendamentos.txt", "a+");
    if (agendamentoArquivo == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos! Criando o arquivo...\n");
        agendamentoArquivo = fopen("agendamentos.txt", "w");
        if (agendamentoArquivo == NULL) {
            printf("Erro ao criar o arquivo de agendamentos!\n");
            return;
        }
    }

    char linha[100];
    int horarioOcupado = 0;
    char horarioSelecionado[10];
    strcpy(horarioSelecionado, horarios[indiceHorario - 1]);

    while (fgets(linha, sizeof(linha), agendamentoArquivo) != NULL) {
        if (strstr(linha, horarioSelecionado) != NULL && strstr(linha, nomeBarbeiro) != NULL) {
            horarioOcupado = 1;
            break;
        }
    }

    // Se o horario estiver ocupado, feche o arquivo e retorne
    if (horarioOcupado) {
        fclose(agendamentoArquivo);
        printf("O horario das %s com o barbeiro %s ja foi preenchido\n", horarioSelecionado, nomeBarbeiro);
        return;
    }

    // Aqui você pode escrever no arquivo porque ele está aberto
    fprintf(agendamentoArquivo, "CPF: %s\tBARBEIRO: %s\thorario: %s\n", cpf, nomeBarbeiro, horarioSelecionado);
    fclose(agendamentoArquivo);

    printf("O seu agendamento com o barbeiro %s para o horario %s foi realizado com sucesso!\n", nomeBarbeiro, horarioSelecionado);
}

// Função para consultar agendamentos
void consultarAgendamentos() {
    char nome_barbeiro[50];
    char linha[256];
    int agendamentos_encontrados = 0;
    int i;

    // Solicita o login do barbeiro
    printf("Digite o nome do barbeiro: ");
    scanf("%s", nome_barbeiro);

    // Verifica se o nome contém apenas letras
    for (i = 0; nome_barbeiro[i] != '\0'; i++) {
        if (!isalpha(nome_barbeiro[i])) {
            printf("Nome do barbeiro invalido. Digite apenas letras.\n");
            return; 
        }
    }

    // Abre o arquivo agendamentos.txt em modo leitura
    FILE *arquivo = fopen("agendamentos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos.\n");
        return;
    }

    // Lê linha por linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Verifica se o login do barbeiro está na linha
        if (strstr(linha, nome_barbeiro) != NULL) {
            // Se encontrar o primeiro agendamento, exibe a mensagem "Seus agendamentos:" uma vez
            if (agendamentos_encontrados == 0) {
                printf("Seus agendamentos:\n");
            }
            printf("%s", linha);  // Exibe a linha que contém o login
            agendamentos_encontrados = 1;
        }
    }

    // Verifica se nenhum agendamento foi encontrado
    if (!agendamentos_encontrados) {
        printf("Nenhum agendamento encontrado para o barbeiro '%s'.\n", nome_barbeiro);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

// Função para verificar se o CPF contém apenas numeross (desconsiderando pontuação)
int VarVerificarCPFnumero(const char *cpf) {
    for (int i = 0; i < strlen(cpf); i++) {
        if (!isdigit(cpf[i]) && cpf[i] != '.' && cpf[i] != '-') {
            return 0;
        }
    }
    return 1;
}

// Função para verificar se o login contém apenas letras
int VarVerificarLoginLetra(const char *login) {
    for (int i = 0; i < strlen(login); i++) {
        if (!isalpha(login[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para verificar se o CPF ja está cadastrado
int verificarCPF(const char *cpf) {
    FILE *arquivo = fopen("clientes.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    char linha[100], cpfArquivo[20];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "CPF: %s", cpfArquivo);
        if (strcmp(cpf, cpfArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Função para verificar se o login ja está cadastrado
int verificarLogin(const char *login) {
    FILE *arquivo = fopen("barbeiros.txt", "r");
    if (arquivo == NULL) {
        return 0;
    }

    char linha[100], loginArquivo[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "LOGIN: %s", loginArquivo);
        if (strcmp(login, loginArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Função para verificar se o CPF e a senha estão corretos
int verificarLoginCliente(const char *cpf, const char *senha) {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return 0;
    }

    char linha[100], cpfArquivo[20], senhaArquivo[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "CPF: %s SENHA: %s", cpfArquivo, senhaArquivo);
        if (strcmp(cpf, cpfArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Função para verificar se o login e a senha estão corretos
int verificarLoginBarbeiro(const char *login, const char *senha) {
    FILE *arquivo = fopen("barbeiros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de barbeiros!\n");
        return 0;
    }

    char linha[100], loginArquivo[50], senhaArquivo[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "LOGIN: %s SENHA: %s", loginArquivo, senhaArquivo);
        if (strcmp(login, loginArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Função para cadastrar um novo cliente
void CadastrarCliente(const char *cpf, const char *senha, const char *nomeCliente) {
    FILE *arquivo = fopen("clientes.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes!\n");
        return;
    }

    fprintf(arquivo, "CPF: %s\tSENHA: %s\tNOME CLIENTE: %s\n", cpf, senha, nomeCliente);
    fclose(arquivo);
}

// Função para cadastrar um novo barbeiro
void CadastrarBarbeiro(const char *login, const char *senha, const char *nomeBarbeiro) {
    FILE *arquivo = fopen("barbeiros.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de barbeiros!\n");
        return;
    }

    fprintf(arquivo, "LOGIN: %s\tSENHA: %s\tNOME BARBEIRO: %s\tSALDO ATUAL: 0.00\n", login, senha, nomeBarbeiro);
    fclose(arquivo);
}

// Função para consultar saldo
void consultarSaldo() {
    char login_logado[50];
    char senha_logada[50];
    char login_arquivo[50], senha_arquivo[50];
    char nome_barbeiro[50];
    float saldo;
    int i, login_encontrado = 0;

    FILE *arquivo = fopen("barbeiros.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de barbeiros!\n");
        return;
    }

    // Entrada do login
    printf("Digite o seu login de barbeiro: ");
    scanf("%s", login_logado);

    // Verifica se o login contém apenas letras
    for (i = 0; login_logado[i] != '\0'; i++) {
        if (!isalpha(login_logado[i])) {
            printf("Login de barbeiro inválido. Digite apenas letras.\n");
            fclose(arquivo);
            return; 
        }
    }

    // Entrada da senha
    printf("Digite a sua senha: ");
    scanf("%s", senha_logada);

    // Leitura do arquivo e busca pelo login e senha
    while (fscanf(arquivo, "LOGIN: %s SENHA: %s NOME BARBEIRO: %s SALDO ATUAL: %f\n", 
                  login_arquivo, senha_arquivo, nome_barbeiro, &saldo) != EOF) {
        if (strcmp(login_logado, login_arquivo) == 0 && strcmp(senha_logada, senha_arquivo) == 0) {
            printf("Login e senha corretos!\n");
            printf("Nome do barbeiro: %s\n", nome_barbeiro);
            printf("Seu saldo atual é: R$%.2f\n", saldo);
            login_encontrado = 1;
            break;
        }
    }

    if (!login_encontrado) {
        printf("Login ou senha incorretos!\n");
    }

    fclose(arquivo);
}

// Função pra usar no menu
int validarNumero(char *entrada) {
    for (int i = 0; i < strlen(entrada); i++) {
        if (!isdigit(entrada[i])) {
            return 0; // Se encontrar qualquer caractere não numérico, retorna 0
        }
    }
    return 1; // Se todos os caracteres forem números, retorna 1
}

// Menu do barbeiro
void menuBarbeiro() {
    int opcao;
    int sair = 0;
    char entrada[10]; // Armazena a entrada do usuário como string

    do {
        printf("\nMenu Principal do barbeiro:\n");
        printf("1. Consultar agendamentos\n");
        printf("2. Cancelar agendamentos\n");
        printf("3. Consultar saldo\n");
        printf("4. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%s", entrada); // Lê a entrada como string

        // Verifica se a entrada contém apenas números
        if (validarNumero(entrada)) {
            opcao = atoi(entrada); // Converte a string para número inteiro
        } else {
            printf("Opcao invalida, insira uma opcao valida!\n");
            continue;  // Retorna ao início do loop se a entrada não for válida
        }

        switch (opcao) {
            case 1:
                consultarAgendamentos(); // Função para consultar agendamentos
                break;

            case 2:
                // Função
                break;

            case 3:
                consultarSaldo(); // Função para consultar saldo
                break;

            case 4:
                printf("Sistema Finalizado\n");
                exit(0); // Encerra o programa
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (!sair);
}

// Menu do cliente
void menuCliente() {
    int opcao;
    do {
        printf("\nMenu Principal do cliente:\n");
        printf("1. Realizar agendamento\n");
        printf("2. Cancelar agendamento\n");
        printf("3. Consultar historico de agendamentos\n");
        printf("4. Sair\n");

        char input[10];
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &opcao);

        switch (opcao) {
            case 1:
                agendarCorte(cpf_logado);
                break;

            case 2:
                // Lógica para cancelar agendamento
                break;

            case 3:
                // Lógica para consultar historico de agendamentos
                break;

            case 4:
                printf("Sistema Finalizado\n");
                sair = 1; // Define sair como 1 para encerrar o sistema
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 4);
}

// Função principal
int main() {
    char cpf[20], login[20], senha[50];
    char nomeBarbeiro[50];
    char nomeCliente[50];
    int opcao;

    while (!sair) {
        printf("Seja bem-vindo a barbearia FEIto na Navalha!\n");
        printf("Selecione uma opcao:\n ");
        printf("0- SAIR\t1- LOGAR\t2- CADASTRAR\n ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &opcao);

        if (opcao == 0) {
            printf("Saindo do sistema.\n");
            sair = 1;
            break;
        } else if (opcao == 1) {
            // Login
            printf("Selecione uma opcao:\n");
            printf("1- LOGAR COMO BARBEIRO\t2- LOGAR COMO CLIENTE\n");

            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &opcao);

            if (opcao == 1) {
                while (1) {
                    printf("Digite o login do barbeiro (somente letras) (ou 0 para cancelar): ");
                    fgets(login, sizeof(login), stdin);
                    login[strcspn(login, "\n")] = '\0';

                    if (strcmp(login, "0") == 0) {
                        printf("Login como barbeiro cancelado.\n");
                        break;
                    }

                    if (!VarVerificarLoginLetra(login)) {
                        printf("Login invalido! Digite apenas letras.\n");
                        continue;
                    }

                    printf("Digite a senha: ");
                    fgets(senha, sizeof(senha), stdin);
                    senha[strcspn(senha, "\n")] = '\0';

                    if (verificarLoginBarbeiro(login, senha)) {
                        printf("Login bem-sucedido! Bem-vindo barbeiro!\n");
                        strcpy(login_logado, login); // Armazena o login logado
                        menuBarbeiro();
                        if (sair) {
                            break;
                        }
                    } else {
                        printf("Login ou senha inexistente ou incorreto.\n");
                        continue;
                    }
                }
            } else if (opcao == 2) {
                while (1) {
                    printf("Digite o CPF do cliente (somente numeros) (ou 0 para cancelar): ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = '\0';

                    if (strcmp(cpf, "0") == 0) {
                        printf("Login como cliente cancelado.\n");
                        break;
                    }

                    if (!VarVerificarCPFnumero(cpf)) {
                        printf("CPF invalido! Digite apenas numeros.\n");
                        continue;
                    }

                    printf("Digite a senha: ");
                    fgets(senha, sizeof(senha), stdin);
                    senha[strcspn(senha, "\n")] = '\0';

                    if (verificarLoginCliente(cpf, senha)) {
                        printf("Login bem-sucedido! Bem-vindo cliente!\n");
                        strcpy(cpf_logado, cpf); // Armazena o CPF logado
                        menuCliente();
                        if (sair) {
                            break;
                        }
                    } else {
                        printf("CPF ou senha inexistente ou incorreto.\n");
                        continue;
                    }
                }
            }
        } else if (opcao == 2) {
            // Cadastrar
            printf("Selecione uma opcao:\n");
            printf("1- CADASTRAR BARBEIRO\t2- CADASTRAR CLIENTE\n");

            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &opcao);

            if (opcao == 1) {
                while (1) {
                    printf("Digite o login do barbeiro (somente letras) (ou 0 para cancelar): ");
                    fgets(login, sizeof(login), stdin);
                    login[strcspn(login, "\n")] = '\0';

                    if (strcmp(login, "0") == 0) {
                        printf("Cadastro de barbeiro cancelado.\n");
                        break;
                    }

                    if (!VarVerificarLoginLetra(login)) {
                        printf("Login invalido! Digite apenas letras.\n");
                        continue;
                    }

                    if (verificarLogin(login)) {
                        printf("Login ja cadastrado! Por favor, escolha outro login.\n");
                        continue;
                    }

                    printf("Digite a senha: ");
                    fgets(senha, sizeof(senha), stdin);
                    senha[strcspn(senha, "\n")] = '\0';

                    printf("Digite o nome do barbeiro: ");
                    fgets(nomeBarbeiro, sizeof(nomeBarbeiro), stdin);
                    nomeBarbeiro[strcspn(nomeBarbeiro, "\n")] = '\0';

                    CadastrarBarbeiro(login, senha, nomeBarbeiro);
                    printf("Barbeiro cadastrado com sucesso!\n");
                    break;
                }
            } else if (opcao == 2) {
                while (1) {
                    printf("Digite o CPF do cliente (somente numeros) (ou 0 para cancelar): ");
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = '\0';

                    if (strcmp(cpf, "0") == 0) {
                        printf("Cadastro de cliente cancelado.\n");
                        break;
                    }

                    if (!VarVerificarCPFnumero(cpf)) {
                        printf("CPF invalido! Digite apenas numeros.\n");
                        continue;
                    }

                    if (verificarCPF(cpf)) {
                        printf("CPF ja cadastrado! Por favor, use outro CPF.\n");
                        continue;
                    }

                    printf("Digite a senha: ");
                    fgets(senha, sizeof(senha), stdin);
                    senha[strcspn(senha, "\n")] = '\0';

                    printf("Digite o nome do cliente: ");
                    fgets(nomeCliente, sizeof(nomeCliente), stdin);
                    nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

                    CadastrarCliente(cpf, senha, nomeCliente);
                    printf("Cliente cadastrado com sucesso!\n");
                    break;
                }
            }
        }
    }

    return 0;
}