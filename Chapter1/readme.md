## Chapter 1 — TinyML on the Edge (Códigos)

Este diretório contém os códigos de apoio do Capítulo 1 do projeto TinyML-EdgeAi.

O objetivo deste capítulo é apresentar exemplos iniciais para captura de dados e execução de pequenos exemplos em microcontroladores e no ambiente Python, preparando o terreno para modelos TinyML nos capítulos seguintes.

### Estrutura do diretório

- `ArduinoCodes/` — Sketches para Arduino / placas compatíveis. Abra os arquivos `.ino` na Arduino IDE.
- `Python/` — Scripts Python de apoio (pré-processamento, visualização, captura via serial, etc.).
- `readme.md` — Este arquivo.

> Observação: os nomes exatos das pastas podem variar conforme a distribuição local. Ajuste os caminhos quando necessário.

### Conteúdo típico

- Exemplos simples de leitura de sensores e envio de dados por serial.
- Scripts Python para ler dados enviados pela porta serial (ex.: gravação em CSV, plotagem básica).

### Pré-requisitos

- Arduino IDE (versão recomendada: 1.8.x ou 2.x). Instale o suporte à placa que você pretende usar (ex.: Arduino Uno, Nano 33 BLE Sense, ESP32, Raspberry Pi Pico etc.).
- Bibliotecas Arduino necessárias (quando aplicável):
  - `Arduino.h` (inclusa na IDE)
  - bibliotecas específicas de sensor (consulte o cabeçalho de cada sketch)
- Python 3.8+ com pacotes comuns para ciência de dados e comunicação serial. Exemplo de instalação rápida:

```bash
python3 -m pip install --user numpy scipy matplotlib pyserial
```

### Como usar

1. Executando sketches Arduino

   - Abra o sketch desejado em `ArduinoCodes/` com a Arduino IDE.
   - Selecione a placa correta em Ferramentas → Placa e a porta serial correta.
   - Clique em Upload para gravar o programa na placa.
   - Abra o Monitor Serial (ou uma aplicação externa) para verificar a saída.

2. Lendo dados com Python

   - Conecte a placa via USB e identifique a porta serial (ex.: `/dev/tty.usbmodemXXXX` no macOS).
   - Execute o script Python de leitura serial (exemplo):

```bash
python3 Python/your_script.py --port /dev/tty.usbmodemXXXX --baud 115200
```

   - Substitua `your_script.py` pelo arquivo Python correspondente no diretório `Python/`.

### Boas práticas e dicas

- Verifique a taxa de transmissão (baud rate) no sketch e no script Python — ambos devem coincidir.
- Se houver múltiplos dispositivos seriais conectados, confirme a porta correta antes de executar os scripts.
- Para datasets, prefira gravar em CSV com cabeçalho claro (timestamp, sensor1, sensor2, ...).

### Erros comuns e resolução

- Erro: porta serial não encontrada — verifique cabos, drivers (macOS normalmente não precisa), e permissões.
- Erro: dados desconformes — valide o formato enviado pelo sketch (delimitadores, newline) e ajuste o parser Python.

### Contribuindo

- Adicione novos sketches em `ArduinoCodes/` e scripts de apoio em `Python/`.
- Inclua um pequeno comentário no topo do arquivo explicando o propósito, entradas esperadas e saída.

### Referências úteis

- Documentação Arduino: https://www.arduino.cc/
- pySerial: https://pyserial.readthedocs.io/
- TensorFlow Lite for Microcontrollers (quando avançar para modelos): https://www.tensorflow.org/lite/microcontrollers

### Licença

Consulte o arquivo `LICENSE` na raiz do repositório para os termos de uso.

---

Se quiser, posso adaptar este README para incluir exemplos concretos de execução (com nomes de arquivos dos sketches e scripts existentes), basta me dizer quais arquivos você quer documentar em detalhe.
