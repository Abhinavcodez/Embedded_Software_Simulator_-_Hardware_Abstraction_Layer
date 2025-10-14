# 🧩 Embedded Software Simulator – Hardware Abstraction Layer (HAL) & RTOS

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) [![Build](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Abhinavcodez/Embedded_Software_Simulator_-_Hardware_Abstraction_Layer)

---

## 📘 Overview

The **Embedded Software Simulator – Hardware Abstraction Layer (HAL)** is a **C++17-based embedded simulation framework** that provides a **virtual environment for firmware testing** — without physical boards or drivers.
It now supports **dual-mode execution**:

* **HAL-only mode:** Uses native C++ threads for simulation.
* **HAL + RTOS mode:** Uses an internal RTOS-like task scheduler (`rtos_sim`) for cooperative task simulation.

This project is ideal for:

* Embedded developers prototyping without target hardware
* Unit testing embedded logic
* Educational use in RTOS & HAL design

---

## 🚀 Key Features

* 🧱 **Virtualized Peripherals:** UART, GPIO, and easy extension for more
* ⚙️ **RTOS Simulation Layer:** Optional lightweight scheduler and task model
* 🧩 **ThreadSafe Queues:** Safe inter-task communication
* 🧪 **Built-in GTest Suite:** Unit and integration tests
* 🔄 **Toggle Between Modes:** Compile-time option `USE_RTOS` in CMake

---

## 📂 Project Structure

```
Embedded_Software_Simulator_-_Hardware_Abstraction_Layer/
├── include/
│   ├── app/               # Application-level headers (sensor_task, etc.)
│   ├── hal/               # HAL interfaces and manager (IUart, IGpio, HalManager, rtos_sim.h)
│   └── utils/             # Shared utilities (ThreadSafeQueue)
│
├── src/
│   ├── app/               # Application logic implementations
│   ├── hal/               # HAL stubs and virtual hardware (hal_manager_stubs.cpp)
│   └── main.cpp           # Entry point – dual-mode (HAL or HAL+RTOS)
│
├── tests/                 # Google Test unit/integration tests
├── CMakeLists.txt         # Build system (CMake ≥ 3.10)
└── README.md              # Project documentation
```

---

## ⚙️ Dependencies

* **C++17 compiler (GCC ≥ 9 or Clang ≥ 10)**
* **CMake ≥ 3.10**
* **Google Test (GTest)**

### 🧩 Install GTest (Ubuntu)

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
./embedded_sim
```

#### ⚙️ HAL + RTOS Simulation

```bash
cmake -DUSE_RTOS=ON ..
make -j$(nproc)
./embedded_sim
```

---

## 🧪 Running Tests

```bash
./run_tests
```

### Example Output

```
[==========] Running 8 tests from 6 test suites.
[ RUN      ] HAL_UART.SendReceive
[Mock HAL] UART_Init called
[Mock HAL] UART_Send called with length: 5
[       OK ] HAL_UART.SendReceive
[ RUN      ] HAL_GPIO.PinWriteRead
[Mock HAL] GPIO pin 4 written HIGH
[Mock HAL] GPIO pin 4 read HIGH
[       OK ] HAL_GPIO.PinWriteRead
...
[==========] 8 tests from 6 test suites ran. (3 ms total)
```

> ⚠️ If any test fails, ensure your virtual peripheral stubs are properly registered in `hal_manager_stubs.cpp`.

---

## 💡 Switching Between HAL and RTOS

The simulation mode is **compile-time controlled** through the CMake option `USE_RTOS`:

| Mode       | Description                                          | Command                   |
| ---------- | ---------------------------------------------------- | ------------------------- |
| HAL-only   | Uses standard C++ threads                            | `cmake -DUSE_RTOS=OFF ..` |
| HAL + RTOS | Uses simulated scheduler (`RTOS::create_task`, etc.) | `cmake -DUSE_RTOS=ON ..`  |

At runtime, both execute the same logic but through different threading/scheduling backends.

---

## 🧩 Adding New Virtual Peripherals

1. Create a new interface in `include/hal/`
   Example: `IADC.h`
2. Implement the stub in `src/hal/`
   Example: `virtual_adc.cpp`
3. Register it in `hal_manager_stubs.cpp`:

   ```cpp
   HalManager::instance().register_adc(std::make_unique<VirtualADC>());
   ```
4. Add a GTest unit in `tests/test_adc.cpp`

---

## 📘 Example Application Flow

```
main.cpp
│
├── sensor_task()      → Produces SensorSample data
├── processing_task()  → Formats & processes readings
├── logger_task()      → Logs to console
└── cli_task()         → Simple CLI interface
```

Each runs either as:

* **std::thread** (HAL-only mode), or
* **RTOS::task** (RTOS simulation mode)

---

## 🧰 Example Runtime Output

```
[CLI] CLI task started...
[LOG] Sensor ID: 1 Value: 23.45
[LOG] Sensor ID: 2 Value: 24.02
[LOG] Sensor ID: 3 Value: 24.10
[MAIN] Simulation finished.
```

---

## ⚠️ Notes

* RTOS simulation layer (`rtos_sim.h/.cpp`) is optional — toggle via CMake.
* All HAL stubs (UART, GPIO) are mockable and testable.
* ThreadSafeQueue ensures synchronization between all simulated threads.
* No real hardware interaction occurs — **pure software simulation**.
