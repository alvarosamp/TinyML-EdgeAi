# 📟 Capítulo 1 — Fundamentos de Microcontroladores para TinyML

> **Objetivo**: Dominar os conceitos fundamentais de programação embarcada, GPIO, interrupções, comunicação serial e coleta de dados - competências essenciais para implementar Machine Learning em dispositivos de borda.

---

## 🎯 O que você vai aprender

Neste capítulo, você vai construir uma base sólida em programação de microcontroladores, preparando-se para implementar modelos TinyML nos capítulos seguintes:

- ✅ Controlar pinos GPIO (entrada e saída digital)
- ✅ Implementar interrupções de hardware para eventos assíncronos
- ✅ Estabelecer comunicação serial entre microcontrolador e computador
- ✅ Coletar dados de sensores e armazená-los automaticamente no Google Drive
- ✅ Utilizar PlatformIO para desenvolvimento multi-plataforma

---

## 📂 Estrutura do Diretório

```
Chapter1/
│
├── ArduinoCodes/              # Projetos PlatformIO
│   ├── platformio-gpio-out/           # Projeto 1: LED piscando (básico)
│   ├── platformio-gpio-in-out/        # Projeto 2: Entrada e saída digital
│   ├── platformio-gpio-interrupt/     # Projeto 3: Controle via interrupções
│   └── platformio-serial/             # Projeto 4: Comunicação serial
│
├── Python/                    # Scripts Python de apoio
│   └── SerialToDrive.py               # Captura serial → Google Drive
│
└── readme.md                  # Este arquivo
```

---

## 🚀 Projetos Práticos

### 📌 Projeto 1: GPIO Output - LED Piscando

**📁 Diretório**: `ArduinoCodes/platformio-gpio-out/`

#### 📖 Descrição:
Projeto introdutório que demonstra o controle básico de um pino GPIO como saída digital. O LED alterna entre ligado/desligado a cada 1 segundo.

#### 🔧 Conceitos aprendidos:
- Uso da biblioteca **mbed** para controle de hardware de baixo nível
- Classe `DigitalOut` para controle de pinos
- Compatibilidade multi-plataforma (Arduino Nano 33 BLE e Raspberry Pi Pico)

#### 🛠️ Hardware:
- **Arduino Nano 33 BLE**: LED conectado ao pino `P0_23` (ou LED interno)
- **Raspberry Pi Pico**: LED conectado ao pino `p22` (GPIO22)

#### ⚡ Como executar:
```bash
cd ArduinoCodes/platformio-gpio-out
pio run --target upload
```

#### 💡 Experimente modificar:
- Alterar o intervalo de `delay(1000)` para diferentes velocidades de piscar
- Adicionar mais LEDs em outros pinos

---

### 📌 Projeto 2: GPIO Input/Output - Controle Manual

**📁 Diretório**: `ArduinoCodes/platformio-gpio-in-out/`

#### 📖 Descrição:
Demonstra o uso simultâneo de entrada e saída digital. Um LED pisca automaticamente, enquanto um botão é monitorado (com resistor pull-up interno).

#### 🔧 Conceitos aprendidos:
- Configuração de pinos como **entrada** (`DigitalIn`)
- Uso de resistores pull-up internos
- Leitura de estados de botão

#### 🛠️ Hardware:
- **Entrada**: Botão conectado ao pino `P0_30` (Nano 33 BLE) ou `p10` (Pico)
- **Saída**: LED no pino `P0_23` (Nano 33 BLE) ou `p22` (Pico)

#### ⚡ Como executar:
```bash
cd ArduinoCodes/platformio-gpio-in-out
pio run --target upload
```

---

### 📌 Projeto 3: GPIO Interrupt - Controle Inteligente com Interrupções

**📁 Diretório**: `ArduinoCodes/platformio-gpio-interrupt/`

#### 📖 Descrição:
Implementa **interrupções de hardware** para responder instantaneamente a eventos externos (pressionar/soltar botão) sem polling constante. 

#### 🔧 Conceitos aprendidos:
- Classe `InterruptIn` da biblioteca mbed
- Funções de callback para interrupções (`rise()` e `fall()`)
- Eficiência energética (CPU livre durante espera)

#### 🎬 Comportamento:
- **Botão pressionado** (falling edge): LED **liga** (`led = 1`)
- **Botão solto** (rising edge): LED **desliga** (`led = 0`)

#### 🛠️ Hardware:
- Botão no pino `P0_30` (Nano 33 BLE) ou `p10` (Pico) com pull-up
- LED no pino `P0_23` (Nano 33 BLE) ou `p22` (Pico)

#### ⚡ Como executar:
```bash
cd ArduinoCodes/platformio-gpio-interrupt
pio run --target upload
```

#### 💡 Por que interrupções são importantes para TinyML?
Em aplicações reais de TinyML, interrupções permitem que o microcontrolador **durma** (economizando energia) e acorde apenas quando há dados de sensores para processar ou inferência para executar.

---

### 📌 Projeto 4: Comunicação Serial - Base para Coleta de Dados

**📁 Diretório**: `ArduinoCodes/platformio-serial/`

#### 📖 Descrição:
Estabelece comunicação serial USB com o computador. Envia mensagens periódicas que podem ser capturadas para análise ou treinamento de modelos.

#### 🔧 Conceitos aprendidos:
- Inicialização de `Serial` com baud rate 9600
- Envio de strings via `Serial.println()`
- Sincronização com `while(!Serial)` 

#### 📤 Saída Serial (a cada 2 segundos):
```
Inicializando
Executado
Executado
Executado
...
```

#### ⚡ Como executar:
```bash
cd ArduinoCodes/platformio-serial
pio run --target upload
pio device monitor  # Abre o monitor serial
```

#### 💡 Aplicação prática:
Este padrão é a **base para transmitir dados de sensores** (temperatura, aceleração, áudio) que serão usados para treinar modelos nos capítulos seguintes.

---

## 🐍 Script Python: Coleta Automática de Dados

### 📌 SerialToDrive.py - Captura Serial + Upload para Google Drive

**📁 Arquivo**: `Python/SerialToDrive.py`

#### 📖 Descrição:
Script automatizado para capturar dados da porta serial por um período definido e fazer upload automático para o Google Drive - ideal para coletar grandes volumes de dados de sensores.

#### 🔧 Funcionalidades:
- ✅ Leitura contínua da porta serial
- ✅ Gravação em arquivo `.log` local
- ✅ Upload automático para Google Drive via API
- ✅ Configuração flexível via argumentos de linha de comando

#### 📦 Dependências:
```bash
pip install pyserial pydrive
```

#### ⚡ Como usar:

**1. Configure o Google Drive API:**
- Acesse [Google Cloud Console](https://console.cloud.google.com/)
- Crie um projeto e ative a API do Google Drive
- Baixe `client_secrets.json` e coloque na mesma pasta do script

**2. Execute o script:**
```bash
python Python/SerialToDrive.py \
    --port COM3 \                    # Windows
    --baudrate 9600 \
    --logging_time_s 60              # Captura por 60 segundos
```

**No Linux/macOS:**
```bash
python3 Python/SerialToDrive.py \
    --port /dev/ttyACM0 \            # Linux
    --baudrate 9600 \
    --logging_time_s 60
```

**3. Configure o ID da pasta do Google Drive:**
- Edite a linha `gdrive_id = ""` no script com o ID da sua pasta
- O ID pode ser obtido da URL da pasta: `https://drive.google.com/drive/folders/SEU_ID_AQUI`

#### 📊 Exemplo de uso prático:
```bash
# Capturar 5 minutos de dados de acelerômetro
python SerialToDrive.py --port COM3 --baudrate 115200 --logging_time_s 300
```

#### 💡 Dica profissional:
Para datasets de TinyML, configure seu microcontrolador para enviar dados formatados em CSV:
```cpp
// No Arduino
Serial.print(timestamp);
Serial.print(",");
Serial.print(sensor1);
Serial.print(",");
Serial.println(sensor2);
```

---

## 🧰 Pré-requisitos e Instalação

### Hardware necessário:
- ✅ **Arduino Nano 33 BLE** ou **Raspberry Pi Pico**
- ✅ Cabo USB para programação
- ✅ LEDs (5mm) e resistores 220Ω
- ✅ Botão (push-button) e breadboard
- ✅ *(Opcional)* Jumpers para conexões

### Software:

#### 1️⃣ Instalar PlatformIO:

**Via VS Code (recomendado):**
- Instale a extensão **PlatformIO IDE** no VS Code
- Reinicie o VS Code

**Via linha de comando:**
```bash
pip install platformio
```

#### 2️⃣ Instalar dependências Python:
```bash
pip install pyserial pydrive numpy matplotlib
```

#### 3️⃣ Verificar instalação:
```bash
pio --version
python -c "import serial; print('pySerial instalado!')"
```

---

## 📋 Guia Rápido de Execução

### Para projetos PlatformIO:

```bash
# 1. Navegue até o projeto desejado
cd ArduinoCodes/platformio-gpio-out

# 2. Compile o código
pio run

# 3. Faça upload para a placa
pio run --target upload

# 4. (Opcional) Abra o monitor serial
pio device monitor
```

### Identificar porta serial:

**Windows:**
```powershell
# PowerShell
[System.IO.Ports.SerialPort]::getportnames()
```

**Linux/macOS:**
```bash
ls /dev/tty.*  # macOS
ls /dev/ttyACM* /dev/ttyUSB*  # Linux
```

---

## 🎓 Desafios Propostos

Após completar os projetos básicos, tente estes desafios:

### 🏆 Desafio 1: LED RGB
Controle um LED RGB usando 3 pinos PWM para criar diferentes cores.

### 🏆 Desafio 2: Debouncing
Implemente debouncing de software no projeto de interrupções para evitar leituras falsas.

### 🏆 Desafio 3: Sensor de Temperatura
Use um sensor DHT11/DHT22 para enviar temperatura via serial e armazenar no Google Drive.

### 🏆 Desafio 4: Logger Multi-Sensores
Modifique `SerialToDrive.py` para processar dados de múltiplos sensores e salvar em CSV formatado.

---

## ⚠️ Troubleshooting

### Problema: "Porta serial não encontrada"
**Solução:**
- Verifique se a placa está conectada via USB
- No Windows, instale drivers CH340/CP2102 se necessário
- Verifique permissões: `sudo usermod -a -G dialout $USER` (Linux)

### Problema: "Upload failed"
**Solução:**
- Feche o monitor serial antes de fazer upload
- Pressione o botão RESET na placa
- Tente outra porta USB

### Problema: "Dados corrompidos no serial"
**Solução:**
- Confirme que o baud rate é idêntico no código e no script Python
- Adicione `ser.flushInput()` após abrir a porta
- Use `Serial.flush()` no Arduino antes de enviar dados

### Problema: "Erro no Google Drive API"
**Solução:**
- Certifique-se que `client_secrets.json` está configurado
- Execute a autenticação manualmente primeiro
- Verifique permissões da pasta no Drive

---

## 🎯 Checkpoint de Aprendizado

Antes de avançar para o Capítulo 2, certifique-se de que você:

- [ ] Consegue compilar e fazer upload de código para o microcontrolador
- [ ] Entende a diferença entre polling e interrupções
- [ ] Sabe configurar e ler dados da porta serial
- [ ] Consegue capturar dados automaticamente com Python
- [ ] Está confortável com a estrutura de projetos PlatformIO

---

## 📚 Próximos Passos

Após dominar os fundamentos, você está pronto para:

➡️ **Capítulo 2**: Coletar dados de sensores reais (temperatura/umidade) e treinar seu primeiro modelo TinyML para classificação binária

➡️ **Capítulo 3**: Implementar reconhecimento de voz (Keyword Spotting) usando Edge Impulse

---

## 🔗 Referências Úteis

- [PlatformIO Documentation](https://docs.platformio.org)
- [Arduino Mbed OS Nano Boards](https://docs.arduino.cc/learn/programming/mbed-nano)
- [pySerial Documentation](https://pyserial.readthedocs.io/)
- [PyDrive Documentation](https://pythonhosted.org/PyDrive/)
- [Google Drive API Guide](https://developers.google.com/drive/api/guides/about-sdk)

---

## 📄 Licença

Este material está licenciado conforme especificado no arquivo [LICENSE](../LICENSE) na raiz do repositório.

---

<div align="center">

**🎓 Continue praticando - a jornada TinyML está apenas começando! 🚀**

[⬅️ Voltar ao Índice Principal](../readme.md) | [Próximo: Capítulo 2 ➡️](../Chapter2/readme.md)

</div>
