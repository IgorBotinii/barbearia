# 💈 FEIto na Navalha

**FEIto na Navalha** é um sistema de agendamento para barbearias, desenvolvido em C, que facilita a organização de horários para cortes de cabelo e barba, oferecendo uma solução prática para pequenos estabelecimentos.

## 📇 Índice

- [Funcionalidades](#funcionalidades)
  - [Para Clientes](#para-clientes)
  - [Para Barbeiros](#para-barbeiros)
- [Como Usar](#acao)
  - [Area de Clientes](#cliente)
  - [Area de Barbeiros](#barbeiro)
- [Desenvolvedores](#desenvolvedores)

### ✍️ Funcionalidades

### Para Clientes
- **Cadastro**: Clientes podem criar uma conta utilizando CPF e senha.
- **Login**: Autenticação de clientes já cadastrados.
- **Agendamento de Cortes**: Agende um horário com um barbeiro disponível.
- **Cancelamento de Agendamentos**: Permite que os clientes cancelem agendamentos já realizados.
- **Consulta de Agendamentos**: Visualização dos agendamentos ativos.

### Para Barbeiros
- **Cadastro**: Barbeiros podem criar uma conta utilizando um nome de usuário (login) e senha.
- **Login**: Autenticação de barbeiros já cadastrados.
- **Consulta de Agendamentos**: Visualização dos agendamentos marcados para o barbeiro.
- **Atualização de Informações**: Barbeiros podem atualizar suas informações cadastrais.


## 💻​ Ação
### Cliente:
Ao iniciar como cliente, o sistema lhe mostrara as seguintes opções:

```
Menu Principal do cliente:
1. Realizar agendamento
2. Cancelar agendamento
3. Consultar historico de agendamentos
4. Sair
```
- **Opção 1:** Esta função permite agendar um corte com o barbeiro que preferir, Digitando o nome do barbeiro que deseja agendar e o horario, lembrando que o horario tem q estar disponivel, mas fique tranquilo, o sistema avisa caso o seu horario ja esteja preenchido:

```
Barbeiros disponiveis:
- Joao
- Marcelo 

Horarios disponiveis:
1. 15:00
2. 16:00
3. 17:00
4. 18:00
5. 19:00
6. 20:00
Digite o nome do barbeiro que deseja agendar (ou 0 para cancelar): 
```
- **Opção 2:** Esta opção permite o usuario cancelar o corte caso não consiga ir:

```
Agendamentos encontrados:
1. CPF: 503 BARBEIRO: jotao HORARIO: 15:00
2. CPF: 503 BARBEIRO: jotao HORARIO: 16:00
3. CPF: 503 BARBEIRO: Mathes    HORARIO: 18:00
Digite o número do agendamento que deseja cancelar (ou 0 para cancelar): 2
Agendamento cancelado com sucesso!

```

- **Opção 3:** Esta opção server para poder verificar seu historico de agendamentos e cancelamentos

```
Historico de agendamentos para o CPF: 503
CPF: 503        BARBEIRO: Ricardo      HORARIO: 15:00
CPF: 503        AGENDAMENTO CANCELADO: CPF: 503 BARBEIRO: Ricardo      HORARIO: 15:00
```



- **Opção 4:** Nessa opção o usuario cancela e fecha o sistema:

```
4
Sistema Finalizado
```
-------
### Barbeiro:

- **Opção 1:** Esta opção você verifica quais agendamentos você possui:

```
Escolha uma opcao: 1
Digite o nome do barbeiro: Ricardo
CPF: 503 | HORARIO: 15:00
```
- **Opção 2** Esta opção você cancela um agendamento caso não consiga comparecer 

```
Escolha uma opcao: 2
Agendamentos encontrados para Ricardo:
1. CPF: 503     BARBEIRO: Ricardo       HORARIO: 15:00
Digite o Numero do agendamento que deseja cancelar (ou 0 para cancelar): 1
Agendamento cancelado com sucesso!
```
- **Opção 4** O usuario finaliza e sai do sistema 
```
4
Sistema Finalizado
```


## 👨🏻‍💻 Responsaveis
  ### Desenvolvedores
- **Nome:** Igor Botini **RA:** 22.124.023-7
- **Nome:** Henrique Gaiardoni Sant’Anna **RA:** 22.124.009-6