## Chapter 2 — Preparando dados e gerando um modelo TinyML (Estação Meteorológica)

Este diretório contém materiais usados para construir um pipeline de dados meteorológicos, treinar um modelo binário para prever presença de neve e converter o modelo para uso em dispositivos embarcados (TensorFlow Lite for Microcontrollers).

O conteúdo central está no notebook `collab/prepare_model.ipynb`, que implementa as etapas de aquisição de dados, preparação do dataset, treino, avaliação, quantização e geração de um cabeçalho C (`model.h`) com o modelo TFLite.

Resumo das etapas e instruções rápidas

- Aquisição de dados
	- Método 1: usar o pacote `wwo-hist` (WorldWeatherOnline) para baixar históricos meteorológicos.
	- Método 2: consultar diretamente a API histórica da WorldWeatherOnline via `requests` (necessita `api_key`).
	- Dados extraídos: temperatura (`tempC`), umidade (`humidity`) e precipitação de neve (`totalSnow_cm`).

- Preparação do dataset
	- Criação de janelas temporais (ex.: `Temp0`,`Temp1`,`Temp2` e `Humi0`,`Humi1`,`Humi2`).
	- Geração de rótulos binários (Yes/No) usando `MIN_SNOW_CM` como limiar.
	- Balanceamento (undersampling) para aproximar 50/50 entre classes.
	- Escalonamento com Z-score (calcular média/desvio e aplicar).
	- Visualizações: scatter plot temperatura × umidade e histogramas (raw vs scaled).
	- Exportar dataset final para CSV (`OUTPUT_DATASET_FILE`, ex.: `snow_dataset.csv`).

- Treino do modelo (TensorFlow / Keras)
	- Arquitetura de exemplo no notebook: Dense(12,relu) → Dropout(0.4) → Dense(1,sigmoid).
	- Compilação: `binary_crossentropy`, `adam`, métrica `accuracy`.
	- Parâmetros configuráveis: `BATCH_SIZE`, `NUM_EPOCHS`.
	- Split: treino/val/test (ex.: 80/20 e subdivisão do holdout).

- Avaliação
	- Predição sobre conjunto de teste, matriz de confusão, precision/recall/f-score.

- Quantização e conversão
	- Salvar SavedModel, criar `TFLITEConverter` com `representative_dataset` para quantização inteira (int8).
	- Converter para `.tflite` e medir tamanho (bytes).
	- Gerar `model.h` (C array) com `xxd` (no Colab o notebook instala xxd; em macOS o utilitário costuma estar presente).

Como rodar (passo a passo rápido)

1) Crie e ative um virtualenv (recomendado):

```bash
python3 -m venv .venv
source .venv/bin/activate
python3 -m pip install --upgrade pip
```

2) Instale dependências do capítulo (veja `requirements.txt` neste diretório):

```bash
pip install -r Chapter2/requirements.txt
```

3) Abra o notebook `Chapter2/collab/prepare_model.ipynb` no Jupyter/VS Code e configure as variáveis no topo:
	 - `api_key` (WorldWeatherOnline) se for baixar dados automaticamente;
	 - `MIN_SNOW_CM`, `BATCH_SIZE`, `NUM_EPOCHS`, e nomes de arquivos (`OUTPUT_DATASET_FILE`, `TFL_MODEL_FILE`, `TF_MODEL`).

4) Execute as células na ordem: aquisição → preparação → treino → avaliação → quantização → geração de `model.h`.

Notas e dicas

- Se preferir não usar a API pública, você pode criar um CSV local e pular as células de download.
- No macOS, `xxd` geralmente já está disponível; se não, instale via Homebrew: `brew install xxd` (ou `vim`/`xxd` está frequentemente presente).
- A conversão/quantização pode exigir bastante memória dependendo da versão do TensorFlow; se tiver problemas, considere executar a etapa de treino/quantização em Colab.

Dependências (resumido)

- numpy, pandas, matplotlib, seaborn, scikit-learn, tensorflow, wwo-hist, requests

Veja também

- `Chapter2/collab/prepare_model.ipynb` — notebook com o fluxo completo.
- `Artifacts/` — possivelmente contém modelos ou artefatos gerados pelo capítulo.

Se quiser, eu atualizo este README com exemplos concretos (nomes de arquivos das sketches/artifacts) ou gero um `requirements.txt` com versões sugeridas. Já criei o `requirements.txt` básico ao lado.
