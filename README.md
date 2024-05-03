# Sistema de Monitoramento de Condições Adequadas para Vinharia Agnello

## Introdução
Este projeto consiste em um sistema baseado em Arduino que monitora as condições ambientais ideais para armazenamento de vinhos. Ele mede a luminosidade, temperatura e umidade e exibe essas informações em um display LCD. Além disso, o sistema utiliza LEDs e um buzzer para indicar se as condições estão dentro ou fora dos padrões ideais.

## Componentes Necessários
- 1 Arduino UNO
- 1 Sensor de luminosidade (LDR)
- 1 Sensor de temperatura e umidade (dht11)
- 1 Display LCD
- 1 Potenciômetro
- 1 Buzzer
- 3 LEDs (verde, amarelo e vermelho)
- Resistores (para os LEDs e os sensores, conforme necessário)
- Cabos de conexão
- Protoboard

## Dependências
Para replicar este projeto, você precisará do software Arduino IDE instalado em seu computador para carregar o código no Arduino.

## Como Reproduzir o Projeto
1. **Montagem do Circuito:**
    - Conecte os LEDs aos pinos 3 (verde), 4 (amarelo), 5 (vermelho). Use resistores adequados para limitar a corrente nos LEDs.
    - Ligue o sensor LDR ao pino A0. Um resistor deve ser usado para criar um divisor de tensão, essencial para a leitura correta dos valores de luminosidade.
    - Ligue o sensor dht22 no pino 2
    - Ligue o buzzer no pino 13
    - Ligue o display de LCD com as respectivas ligações: 7 ao RS, 6 ao E, D4 ao 12, D5 ao 10, D6 ao 9, D7 ao 8, DV0 ao potenciómetro
    - Faça as ligações negativas e positivas adequadamente, de acordo com o projeto, além do uso dos resistores corretos de forma correta

2. **Configuração do Ambiente de Desenvolvimento:**
    - Instale o Arduino IDE no seu computador.
    - Conecte o Arduino ao seu computador usando um cabo USB.

3. **Carregamento do Código:**
    - Abra o Arduino IDE.
    - Copie e cole o código fornecido acima no IDE.
    - Selecione o modelo correto de Arduino e a porta COM em que ele está conectado no IDE.
    - Carregue o código para o Arduino usando o botão de upload no IDE.
  
4. **Operação:**
    - Após o código ser carregado, o sistema carregará o display, apresentando a logo e as condições de luminosidade, temperatura e umidade.
    - Conforme as condições variam, os LEDs indicarão o estado do ambiente: verde para condições adequadas, amarelo para alerta e vermelho para condições inadequadas.

## Observações
- Este projeto é a continuação do primeiro projeto de monitoramento da saúde do vinho, adicionando o display de LCD, os sensores de temperatura e umidade, o potenciômetro e correções de código
- Ajuste os valores no código (especificamente na função `map()`) conforme necessário para calibrar o sensor LDR de acordo com as condições específicas do local de instalação.

Este projeto proporciona uma solução eficaz e de baixo custo para o monitoramento das condições de armazenamento do vinho, contribuindo para a manutenção da qualidade do produto na Vinheria Agnello.
