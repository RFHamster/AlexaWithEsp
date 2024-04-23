# Controlando um ESP/Wemos D1 (Arudino com ESP) via chamadas HTTP e Alexa

## Considerações Iniciais

Ese projeto foi feito visando minha realidade, ele não está totalmente pronto para produção e utiliza muito de IPs estáticos, caso deseje utilizar dessa forma é basicamente fazer o passo a passo. Também irei dar uma ideia de como generalizar esse código para "funcionar" em produção, é claro que ainda vai faltar algumas coisas, mas ele já estará pronto para suportar mais de um ESP.

## Configurações Iniciais (Por etapa)

### WebServer Java (Databse)

Começando pelo o que é mais simples nesse sistema o WebServer. Ele funciona como um banco de dados e nessa forma que eu fiz, ele está sendo "sub-utilizado", apenas guarda as portas já cadastradas de um ESP, criando novas ou recuperando. Como podemos ver mais a frente aqui no ReadMe o sistema é controlado por requisições HTTP e para isso precisamos dos endpoints de controle (IPs), dessa forma o sistema presente está tudo estático no código, hardcoded.

Fiz assim porque comporta a minha realidade, tenho um ESP e só queria que ele controlasse e somente com uma alexa. Caso queira aumentar o projeto, seria uma boa ideia ter uma tabela fazendo um novo cadastro onde um Id_Alexa está numa tupla com o IP_ESP relacionado, onde toda vez que o IP do ESP fosse alterado (cada Wifi é um IP e a cada ligação o IP pode mudar também) ele alertasse o servidor e alterava seu IP e a relação com a Alexa.

Dito isso, falta uma entidade para mapear uma Alexa (ID_Alexa, Quais ESPs ela pode controlar, localização...) e uma entidade para mapear um ESP (Chassi do ESP, seu IP, quais alexas o controlam...), assim poderiamos escalar o Projeto. É bom falar também que utilizei o ngrok para redirecionar as requisições para meu servidor e apenas utilizo o banco de dados H2 nesse repositório, o correto seria dar deploy no Back-end.

### ESP (No meu caso Wemos D1)

Essa é a parte central do nosso projeto, é valido ressaltar que para os dispositivos (alexa local) é utilizado seu IP local na rede, mas quando vamos utilizar chamadas HTTP e testar ele no servidor externo da Amazon, precisamos de um IP WAN, nesse caso configurei meu roteador para fazer um "port fowarding" na porta 8082 para meu IP e porta do ESP.

#### Exemplo de Port Fowarding (não é o meu)

![image](https://github.com/RFHamster/AlexaWithEsp/assets/71076681/1b18b64c-32d5-4179-bf8b-cbb83a913b84)

Dessa forma, como podemos ver no código ele tem handlers para cada um dos endpoints feitos e pode criar um novo dispositivo com o auxílio do EspAlexa (esse sim funciona localmente). Além disso o código também consegue manipular requisições HTTP e deserializar/serializar Jsons com as bibliotecas de Wifi do ESP e JsonArduino.

### Alexa

Para o cadastro dos componentes no ESP e no Banco de Dados foi criada uma skill, como no teste ela rodava no servidor da amazon precisei criar redirecionamentos para o Back-End e para o ESP como eu expliquei anteriormente, então basicamente ele consome os mesmos com os dados da requisição da skill. Quando a skill fosse implementada em uma alexa normal ela iria passar para o IP local, não precisando mais do redirecionamento do ESP e NECESSITANDO da nova implementação do database que eu mencionei, para que uma tabela mapeie qual IP a alexa deve consumir para comunicar com o ESP de chassi X.

#### Cadastrando um equipamento pela skill (simulando uma Alexa)

![image2](https://github.com/RFHamster/AlexaWithEsp/assets/71076681/94f15aac-8991-4fb5-82b8-e352ebbfcf1c)

Agora no caso da minha Alexa de controle os dispositivos são cadastrados pelo aplicativo, e já podem ser controlados depois disso!

#### Configurando um dispositivo

#### Adicionar Dispositivo

![image3](https://github.com/RFHamster/AlexaWithEsp/assets/71076681/23f5192c-6016-47a1-8ba9-91340fdea388)

#### Escolher Dispositivo (Outros e no Wifi)

![image](https://github.com/RFHamster/AlexaWithEsp/assets/71076681/f108d0cc-76eb-4547-aef9-475ab58c30d7)

![image](https://github.com/RFHamster/AlexaWithEsp/assets/71076681/af588a0e-e3e6-4750-9d18-747c216a0fa7)

Com o dispositivo configurado é so controlar pelo APP ou pela voz com o nome dele!!!



