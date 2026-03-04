# 🤖 TinyML & Edge AI - Material Didático

> Repositório de apoio para aulas práticas de **TinyML (Tiny Machine Learning)** e **Edge AI**, baseado no livro **TinyML Cookbook v2**. Este material foi desenvolvido para capacitar estudantes e desenvolvedores na criação de aplicações de inteligência artificial embarcada em microcontroladores com recursos limitados.

---

## 📚 Sobre o Projeto

Este repositório contém uma série progressiva de projetos práticos que ensinam como implementar **Machine Learning em dispositivos embarcados** (microcontroladores) com restrições severas de memória, processamento e energia.

### 🎯 Objetivos de Aprendizado

Ao final deste curso, você será capaz de:

- ✅ Compreender os fundamentos de **TinyML** e suas aplicações práticas
- ✅ Configurar e programar microcontroladores (Arduino Nano 33 BLE, Raspberry Pi Pico, etc.)
- ✅ Coletar e processar dados de sensores para treinar modelos
- ✅ Treinar modelos de Machine Learning e convertê-los para **TensorFlow Lite**
- ✅ Implementar **classificação binária** em dispositivos embarcados
- ✅ Desenvolver aplicações de **reconhecimento de voz** (Keyword Spotting)
- ✅ Otimizar modelos para execução em ambientes com recursos limitados

---

## 🌟 O que é TinyML?

**TinyML** (Tiny Machine Learning) é o campo da inteligência artificial que trata da execução de modelos de ML em dispositivos embarcados com recursos extremamente limitados (KB de memória RAM e Flash). 

### Por que TinyML é importante?

- 🔋 **Eficiência energética**: Dispositivos podem operar por meses/anos com bateria
- 🔒 **Privacidade**: Processamento local, sem envio de dados para a nuvem
- ⚡ **Baixa latência**: Inferência em tempo real sem depender de conectividade
- 💰 **Custo reduzido**: Uso de hardware de baixo custo (centavos a poucos dólares)
- 🌍 **Edge Computing**: Inteligência distribuída nos dispositivos finais

---

## 📂 Estrutura do Repositório

```
TinyML-EdgeAi/
│
├── 📁 Chapter1/          # Fundamentos: GPIO, Serial e Coleta de Dados
│   ├── ArduinoCodes/     # Códigos PlatformIO (GPIO, interrupts, serial)
│   └── Python/           # Scripts para comunicação serial e coleta de dados
│
├── 📁 Chapter2/          # Estação Meteorológica e Classificação Binária
│   ├── ArduinoSketches/  # Firmware para leitura de sensores (temp/umidade)
│   ├── Artifacts/        # Modelos treinados (model.h)
│   └── collab/           # Notebook Jupyter para treino e conversão do modelo
│
├── 📁 Chapter3/          # Keyword Spotting (KWS) com Edge Impulse
│   └── ArduinoCodes/     # Aplicações de reconhecimento de voz para controle de LEDs
│
├── 📁 ArduinoLibs/       # Bibliotecas Arduino personalizadas (se necessário)
│
├── requirements.txt      # Dependências Python
├── LICENSE               # Licença do projeto
└── readme.md             # Este arquivo
```

---

## 🚀 Capítulos e Projetos

### 📌 Capítulo 1: Fundamentos de TinyML e Microcontroladores

**Objetivo**: Introduzir programação de microcontroladores e comunicação serial para coleta de dados.

#### 🔧 Conteúdo:
- **GPIO básico**: Controle de pinos digitais (entrada/saída)
- **Interrupções**: Tratamento de eventos assíncronos em hardware
- **Comunicação Serial**: Envio e recebimento de dados via USB
- **Integração Python**: Scripts para captura de dados seriais e armazenamento em CSV

#### 🛠️ Tecnologias:
- PlatformIO (ambiente de desenvolvimento)
- Arduino Framework (C/C++)
- Python 3.8+ (pySerial, NumPy, Matplotlib)

#### 📖 [Documentação completa do Capítulo 1](Chapter1/readme.md)

---

### 📌 Capítulo 2: Estação Meteorológica e Predição de Neve

**Objetivo**: Criar um pipeline completo de ML - da coleta de dados à inferência embarcada.

#### 🌦️ Descrição do Projeto:
Construção de uma **estação meteorológica inteligente** que coleta dados de temperatura e umidade para prever a ocorrência de neve em tempo real, diretamente no microcontrolador.

#### 🔧 Pipeline Completo:

1. **Aquisição de Dados**:
   - API WorldWeatherOnline (histórico meteorológico)
   - Coleta via sensores (HTS221 ou HS300x no Arduino Nano 33 BLE)

2. **Preparação do Dataset**:
   - Criação de janelas temporais (sequências de temperatura/umidade)
   - Balanceamento de classes (Yes/No para presença de neve)
   - Normalização Z-score

3. **Treinamento**:
   - Modelo Keras: Dense(12, relu) → Dropout(0.4) → Dense(1, sigmoid)
   - Binary Cross-Entropy como função de perda
   - Avaliação com matriz de confusão e métricas de classificação

4. **Quantização e Conversão**:
   - Conversão para TensorFlow Lite com quantização int8
   - Geração de `model.h` (C array) para Arduino

5. **Deploy em Microcontrolador**:
   - Upload do modelo para Arduino Nano / Raspberry Pi Pico
   - Inferência em tempo real com dados de sensores

#### 🛠️ Tecnologias:
- TensorFlow / Keras
- TensorFlow Lite for Microcontrollers
- Pandas, Scikit-learn
- Arduino (sensor HTS221/HS300x)

#### 📖 [Documentação completa do Capítulo 2](Chapter2/readme.md)

---

### 📌 Capítulo 3: Keyword Spotting (KWS) - Controle por Voz

**Objetivo**: Implementar reconhecimento de comandos de voz para controle de LEDs.

#### 🎤 Descrição do Projeto:
Desenvolvimento de uma aplicação de **Keyword Spotting** usando **Edge Impulse** para reconhecer comandos de voz e controlar LEDs no Arduino Nano 33 BLE Sense.

#### 🔧 Conteúdo:

1. **Coleta de Áudio**:
   - Microfone embutido no Arduino Nano 33 BLE Sense
   - Aplicativo mobile para gravação de amostras

2. **Feature Engineering**:
   - Extração de características **MFE (Mel-Filterbank Energy)**
   - Pré-processamento de áudio para speech recognition

3. **Treinamento no Edge Impulse**:
   - Design de modelo de classificação de áudio
   - Treinamento e validação na plataforma Edge Impulse

4. **Deploy e Controle**:
   - Export da biblioteca Arduino gerada pelo Edge Impulse
   - Implementação de controle de LEDs via comandos de voz

#### 🛠️ Tecnologias:
- Edge Impulse (plataforma de AutoML)
- Arduino Nano 33 BLE Sense (microfone PDM)
- MFE (Mel-Filterbank Energy) features
- TensorFlow Lite Micro

#### 📖 [Documentação completa do Capítulo 3](Chapter3/readme.md)

---

## 🧰 Pré-requisitos

### Hardware Necessário:

- **Arduino Nano 33 BLE Sense** (recomendado) ou **Raspberry Pi Pico**
- Cabo USB para programação
- LEDs e resistores (projetos de GPIO)
- *(Opcional)* Sensores adicionais (temperatura, umidade, acelerômetro)

### Software:

#### Para Projetos Arduino:
- [PlatformIO](https://platformio.org/) (recomendado) ou [Arduino IDE 2.x](https://www.arduino.cc/en/software)
- Drivers USB (geralmente automáticos no Windows/macOS)

#### Para Machine Learning:
- **Python 3.8+**
- Jupyter Notebook / Google Colab
- Bibliotecas Python (instalar via requirements.txt):
  ```bash
  pip install -r requirements.txt
  ```

#### Bibliotecas Incluídas:
- `tensorflow` - Treinamento e conversão de modelos
- `numpy`, `pandas` - Manipulação de dados
- `matplotlib`, `seaborn` - Visualização
- `scikit-learn` - Pré-processamento e métricas
- `pyserial` - Comunicação serial
- `wwo-hist`, `requests` - Coleta de dados meteorológicos

---

## 🎓 Como Usar Este Material

### Para Estudantes:

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/alvarosamp/TinyML-EdgeAi.git
   cd TinyML-EdgeAi
   ```

2. **Siga os capítulos em ordem sequencial** (1 → 2 → 3)

3. **Leia o README de cada capítulo** antes de executar os códigos

4. **Execute os projetos práticos** e experimente modificações

### Para Instrutores:

- Cada capítulo pode ser apresentado como **módulo independente** de 2-4 aulas
- Os notebooks Jupyter servem como **demonstrações ao vivo**
- Os códigos Arduino podem ser usados para **laboratórios práticos**
- Incentive os alunos a **modificar parâmetros** e observar os resultados

---

## 🎯 Resultados Esperados

Ao completar este curso, os participantes terão construído:

1. ✅ **Projetos funcionais de GPIO e comunicação serial**
2. ✅ **Um sistema de predição meteorológica embarcado** (classificação binária)
3. ✅ **Uma aplicação de reconhecimento de voz** para controle de dispositivos
4. ✅ **Portfolio completo de projetos TinyML** para apresentar em entrevistas/portfólios

---

## 📖 Recursos Adicionais

### Livros:
- **TinyML Cookbook** (Gian Marco Iodice) - Livro base deste material
- **TinyML** (Pete Warden, Daniel Situnayake) - Fundamentos teóricos

### Plataformas:
- [Edge Impulse](https://www.edgeimpulse.com/) - Plataforma de ML para dispositivos embarcados
- [TensorFlow Lite Micro](https://www.tensorflow.org/lite/microcontrollers) - Documentação oficial

### Comunidades:
- [TinyML Foundation](https://www.tinyml.org/)
- [Arduino Forum](https://forum.arduino.cc/)
- [PlatformIO Community](https://community.platformio.org/)

---

## 🤝 Contribuindo

Contribuições são bem-vindas! Sinta-se à vontade para:

- 🐛 Reportar bugs ou problemas
- 💡 Sugerir novos projetos ou melhorias
- 📝 Melhorar a documentação
- 🔧 Adicionar suporte para novas placas

Para contribuir, abra uma **issue** ou envie um **pull request**.

---

## 📄 Licença

Este projeto está licenciado sob os termos especificados no arquivo [LICENSE](LICENSE).

---

## 👨‍🏫 Autor e Contato

**Repositório mantido por**: [alvarosamp](https://github.com/alvarosamp)

Para dúvidas sobre o material didático ou sugestões de melhorias, abra uma issue no GitHub.

---

## 🌟 Agradecimentos

Este material foi desenvolvido com base no excelente livro **TinyML Cookbook v2** e na crescente comunidade de TinyML. Agradecimentos especiais a todos os contribuidores e estudantes que ajudam a melhorar este conteúdo.

---

<div align="center">

**🚀 Vamos democratizar a Inteligência Artificial embarcada! 🚀**

[![Made with ❤️](https://img.shields.io/badge/Made%20with-❤️-red.svg)](https://github.com/alvarosamp/TinyML-EdgeAi)
[![TinyML](https://img.shields.io/badge/TinyML-Edge%20AI-blue.svg)](https://www.tinyml.org/)
[![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D.svg?logo=arduino)](https://www.arduino.cc/)
[![TensorFlow](https://img.shields.io/badge/TensorFlow-Lite-FF6F00.svg?logo=tensorflow)](https://www.tensorflow.org/lite)

</div>
