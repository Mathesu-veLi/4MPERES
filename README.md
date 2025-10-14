
# 🤖 4MPERES — Robô Seguidor de Linha (Arduino)

Repositório do código utilizado pela equipe **4MPERES** na **OBR Bahia 2024**, implementado em **Arduino C++**.  
O projeto controla um robô seguidor de linha com sensores QTR e motores duplos, usando **controle PID** para navegação precisa.

---

## ⚙️ Descrição Geral

Este código foi desenvolvido para um robô autônomo seguidor de linha, utilizando a plataforma **Arduino**.  
O controle dos motores é feito com base na leitura de **sensores infravermelhos QTR**, aplicando um **algoritmo PID** (Proporcional, Integral, Derivativo) para corrigir a trajetória do robô conforme a linha detectada.

---

## 📁 Estrutura do Projeto

```

4MPERES/
├── libraries/              # Bibliotecas utilizadas (submódulos Git)
│   ├── DualMotor/          # Controle dos motores
│   ├── HC_SR04/            # Sensor ultrassônico
│   └── Motor/              # Implementação base de motor
├── main_code/
│   └── main_code.ino       # Código principal do robô
├── teories/                # Documentação e anotações teóricas
├── tests/                  # Códigos de teste de componentes individuais
│   ├── has_line/           # Teste de sensores de linha
│   └── has_obstacle/       # Teste de detecção de obstáculos
└── .gitmodules             # Definição dos submódulos de bibliotecas

````

---

## 🧩 Dependências

O projeto utiliza bibliotecas externas, adicionadas como **submódulos Git**:

| Biblioteca | Caminho | Descrição |
|-------------|----------|-----------|
| [Motor](https://github.com/Mathesu-veLi/Motor) | `libraries/Motor` | Classe base para controle de motores DC |
| [DualMotor](https://github.com/Mathesu-veLi/DualMotor) | `libraries/DualMotor` | Controle simultâneo de dois motores |
| [HC_SR04](https://github.com/Mathesu-veLi/HC_SR04) | `libraries/HC_SR04` | Leitura de distância com sensor ultrassônico HC-SR04 |

---

## 🔧 Instalação e Configuração

### 1️⃣ Clonar o repositório com submódulos
```bash
git clone --recursive https://github.com/Mathesu-veLi/4MPERES.git
````

*(Se já clonou sem `--recursive`)*

```bash
git submodule update --init --recursive
```

### 2️⃣ Abrir o projeto no Arduino IDE

* Abra o arquivo `main_code/main_code.ino`
* Verifique se as bibliotecas estão localizadas corretamente em `libraries/`
* Conecte sua placa Arduino (UNO, Nano, ou compatível)
* Selecione a porta e placa corretas na IDE

### 3️⃣ Fazer o upload

Clique em **"Upload"** (ícone de seta) na IDE do Arduino para gravar o código na placa.

---

## ⚙️ Funcionamento do Código

### 🔹 Controle PID

O robô usa os sensores QTR para detectar a posição da linha e ajustar a velocidade dos motores conforme o erro calculado.

**Equação PID usada:**

```
Saída = (Kp * P) + (Ki * I) + (Kd * D)
```

Parâmetros no código:

```cpp
float Kp = 55;
float Kd = 30;
float Ki = 0.00;
```

### 🔹 Pinos Utilizados

| Função       | Pinos Arduino      |
| ------------ | ------------------ |
| Motor A      | 8, 9               |
| Motor B      | 10, 11             |
| Sensores QTR | A1, A2, A3, A4, A5 |

### 🔹 Ciclo de execução

1. **Calibração dos sensores** (`calibrateSensors()`)
   O robô calibra os sensores QTR durante 7 segundos após o início.

2. **Leitura e cálculo do erro**
   O valor lido dos sensores é comparado com o valor central (2500) para determinar o desvio.

3. **Correção de velocidade**
   O PID gera um valor de correção que aumenta ou reduz a velocidade dos motores.

4. **Movimento contínuo**
   O robô mantém o movimento ajustando dinamicamente as velocidades.

---

## 🚀 Exemplo Simplificado

```cpp
int correctionSpeed = calculateCorrection();

int speedA = DEFAULT_SPEED + correctionSpeed;
int speedB = DEFAULT_SPEED - correctionSpeed;
speedConstraints(speedA, speedB);

frontalMotors->custom(speedA, speedB);
```

---

## 🧠 Ajuste Fino

Os ganhos **Kp**, **Ki** e **Kd** devem ser ajustados experimentalmente para otimizar o comportamento do robô.

Sugestão:

* Aumente **Kp** se o robô demorar para corrigir.
* Aumente **Kd** se ele oscilar demais.
* Use **Ki** apenas se houver erro sistemático acumulado.

---

## 🧪 Testes

A pasta `tests/` contém dois programas independentes em Arduino, usados para **verificar o funcionamento dos sensores antes da integração final** com o código principal.

### 🔸 `tests/has_obstacle/has_obstacle.ino`

Testa o sensor **ultrassônico HC-SR04**, responsável por detectar obstáculos à frente do robô.

* **Pinos usados:**

  * `TRIGGER = 13`
  * `ECHO = 14`
* **Funcionamento:**
  Mede a distância em centímetros e imprime no monitor serial:

  ```
  Has obstacle?: true (6.4cm)
  Has obstacle?: false (12.3cm)
  ```
* **Lógica:**
  Considera que há um obstáculo quando a distância é **menor que 8 cm**.

---

### 🔸 `tests/has_line/has_line.ino`

Verifica se os **sensores de linha** (infravermelhos) estão detectando corretamente o preto e o branco.

* **Pinos usados:**

  * `Left Line Sensor = 3`
  * `Right Line Sensor = 2`
* **Funcionamento:**
  Exibe no monitor serial o estado de cada sensor:

  ```
  Line Sensor 1 | 0
  Line Sensor 0 | 1
  ```

  Onde `1` significa **linha detectada** e `0` significa **sem linha**.
* **Função principal:**

  ```cpp
  bool hasLine(int liner) {
    return digitalRead(liner) == 0 ? true : false;
  }
  ```

Esses testes são essenciais para calibrar sensores antes de rodar o código principal (`main_code.ino`).

---

## 📜 Licença

Este projeto é distribuído sob a licença **MIT**.
Sinta-se livre para usar, modificar e distribuir o código, mantendo os devidos créditos.

---

## 🏁 Créditos

Projeto desenvolvido como parte da **Olimpíada Brasileira de Robótica (OBR)** – Etapa Bahia 2024.
Inspirado em robôs seguidores de linha clássicos e aprimorado com controle PID.
