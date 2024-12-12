# Relatório de Desenvolvimento do Compilador

## Informações Gerais

**Membros da equipe:**  
- Rafael Queiroz Santos  
- Brunna Gabriella  

**Divisão do trabalho:**  
A divisão do trabalho foi feita de forma equitativa (50% | 50%).

- **Rafael Queiroz Santos:** Adequou o analisador léxico ao padrão de projeto especificado pelo professor.
- **Brunna Gabriella:** Gerou o analisador sintático, adequou o AFD para suportar dois tokens novos (FIM_EXPR e CHAVES), iniciou a tabela de símbolos e adequou a especificação da linguagem *proc* conforme as novas diretrizes fornecidas.

**Decisões Tomadas:**  
O analisador léxico utilizado foi o desenvolvido pela aluna Brunna Gabriella, pois estava mais organizado e mais alinhado às novas especificações da linguagem *proc*. Essa decisão permitiu maior economia de tempo e otimização do processo de desenvolvimento.

## Progresso Realizado

### Componentes Concluídos
1. **Autômato Finito Determinístico (AFD):** O AFD foi finalizado e serve como base para o funcionamento do analisador léxico.
2. **Analisador Léxico:** O analisador léxico está completamente funcional e adequado ao padrão de projeto estabelecido.

### Componentes Iniciados
1. **Analisador Sintático:** A estrutura básica foi gerada, mas ainda está em fase de desenvolvimento.
2. **Tabela de Símbolos:** A tabela foi iniciada para integrar o analisador sintático e facilitar a gestão de variáveis e funções da linguagem.

## Instruções para Compilação e Execução
Para compilar o programa principal ( `main.c` ) e suas dependências, utilize o seguinte comando:

```bash
gcc main.c Analex.c Funcaux.c -o compilador
```

Para executar o compilador, use:

```bash
./compilador
```

## Considerações Finais
O progresso até o momento foi satisfatório, com foco na divisão equilibrada das tarefas e na manutenção da qualidade do código. Os próximos passos incluem:
- Finalização do analisador sintático.
- Integração completa da tabela de símbolos.
- Testes finais para garantir conformidade com as especificações da linguagem *proc*.

