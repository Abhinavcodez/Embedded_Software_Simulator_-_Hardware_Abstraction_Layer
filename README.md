# 🧩 Embedded Software Simulator – Hardware Abstraction Layer (HAL) & RTOS

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) [![Build](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Abhinavcodez/Embedded_Software_Simulator_-_Hardware_Abstraction_Layer)

---

## 📘 Overview

The **Embedded Software Simulator – Hardware Abstraction Layer (HAL)** is a software-only simulation framework designed for embedded systems development. It provides a virtualized environment to test and develop embedded applications without the need for physical hardware. This approach is particularly useful for early-stage development, unit testing, and educational purposes.

**Key Features:**

* **Virtual Peripherals:** Simulate hardware components like UART, GPIO, and timers.
* **Modular HAL:** Easily extendable to add new virtual peripherals.
* **RTOS Simulation:** Optionally simulate real-time operating system tasks and scheduling.
* **Unit & Integration Testing:** Built-in support for testing application logic and HAL interactions.

---

## 📂 Project Structure

```
Embedded_Software_Simulator_-_Hardware_Abstraction_Layer/
├── include/
│   ├── hal/             # HAL interfaces (IUart.h, IGpio.h, HAL Manager)
│   ├── app/             # Application headers (sensor tasks, queues)
│   └── utils/           # Utilities
├── src/
│   ├── hal/             # HAL stubs & virtual drivers
│   ├── app/             # Application logic
│   └── rtos/            # Optional RTOS stubs (can be removed)
├── tests/               # Google Test unit tests
├── CMakeLists.txt       # Build configuration
└── README.md            # Project documentation
```

---

## ⚙️ Dependencies

* **C++17 compiler (GCC ≥ 9 or Clang ≥ 10)**
* **CMake ≥ 3.10**
* **Google Test (GTest)**

To install GTest on Ubuntu:

```bash
sudo apt update
sudo apt install libgtest-dev cmake
cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp *.a /usr/lib
```

---

## 🏗️ Build Instructions

Clone and build:

```bash
git clone https://github.com/Abhinavcodez/Embedded_Software_Simulator_-_Hardware_Abstraction_Layer.git
cd Embedded_Software_Simulator_-_Hardware_Abstraction_Layer
mkdir build && cd build
```

### 🔧 Build Modes

#### 🧠 HAL-only (Default)

```bash
cmake -DUSE_RTOS=OFF ..
make -j$(nproc)
```

**Executables:**

* `embedded_sim` → Runs the main application simulation
* `run_tests` → Runs all unit and integration tests

---

## 🧪 Running Tests

```bash
./run_tests
```

### Example Output

```
[==========] Running 8 tests from 6 test suites.
[ RUN      ] HAL_UART.SendReceive
[Mock HAL] UART_Init called for port: test_uart.txt
[Mock HAL] UART_Send called with length: 2
[       OK ] HAL_UART.SendReceive
[ RUN      ] HAL_GPIO.PinWriteRead
[Mock HAL] GPIO pin 3 written HIGH
[Mock HAL] GPIO pin 3 read HIGH
[       OK ] HAL_GPIO.PinWriteRead
...
[==========] 8 tests from 6 test suites ran. (0 ms total)
```

> ⚠ Segmentation faults usually indicate missing virtual peripheral mocks or test misconfigurations.

---

## 🧩 Adding New Virtual Peripherals

1. Create an interface in `include/hal/` (e.g., `IADC.h`)
2. Implement stub in `src/hal/` (e.g., `virtual_adc.h/.cpp`)
3. Register in `hal_manager_stubs.cpp`
4. Add unit tests in `tests/` with GTest

---

## ⚠️ Notes

* RTOS integration is **optional** and can be removed
* Fully modular: easy to add new drivers/tasks
* No hardware needed; pure software simulation

---

## 🔧 License

MIT License – see [LICENSE](LICENSE)
