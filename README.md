# Embedded Software Simulator – Hardware Abstraction Layer (HAL)

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) [![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/Abhinavcodez/Embedded_Software_Simulator_-_Hardware_Abstraction_Layer/actions)

---

## 📌 Project Overview

The **Embedded Software Simulator – HAL** is a software-only simulation framework for embedded systems development. It enables virtual testing of applications and hardware abstraction layers without the need for real hardware. Ideal for early-stage development, testing, and educational purposes.

**Key Features:**

* **Virtual Peripherals:** UART, GPIO, timers, and more.
* **Modular HAL:** Easily extendable to add new peripherals.
* **RTOS Simulation:** Software-only task scheduling, delays, and concurrency.
* **Unit & Integration Testing:** Full support using Google Test.
* **System Simulation:** Run main application with virtual sensors and logging.

---

## 📂 Project Structure

```
Embedded_Software_Simulator_-_HAL/
├── include/
│   ├── hal/             # HAL interfaces & virtual peripherals (IUart.h, IGpio.h, rtos_sim.h)
│   ├── app/             # Application headers (sensor tasks, queues)
│   └── utils/           # Utility headers
├── src/
│   ├── hal/             # HAL stubs & virtual drivers (hal_manager_stubs.cpp, virtual devices)
│   ├── app/             # Application logic (sensor_task.cpp, CLI)
├── tests/               # Google Test unit & integration tests (HAL + RTOS)
├── CMakeLists.txt       # Build configuration
└── README.md            # Project documentation
```

---

## 🛠 Dependencies

* **C++17**
* **CMake >= 3.10**
* **Google Test (GTest)**

**Install GTest on Ubuntu:**

```bash
sudo apt update
sudo apt install libgtest-dev cmake
cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp *.a /usr/lib
```

---

## ⚙️ Build Instructions

```bash
git clone https://github.com/Abhinavcodez/Embedded_Software_Simulator_-_Hardware_Abstraction_Layer.git
cd Embedded_Software_Simulator_-_HAL
mkdir build && cd build
cmake ..
make -j$(nproc)
```

**Executables:**

* `embedded_sim` → Run the main application simulation with virtual sensors and CLI.
* `run_tests` → Run all unit and integration tests including RTOS simulation.

---

## ✅ Running Tests

```bash
./run_tests
```

**Example Output:**

```
[==========] Running 6 tests from 4 test suites.
[ RUN      ] HAL_UART_SendReceive_Test.BasicEcho
[VirtualUART] TX: Hello
[VirtualUART] RX: Echo:Hello
[       OK ] HAL_UART_SendReceive_Test.BasicEcho
[ RUN      ] HAL_GPIO_PinWriteRead_Test.WriteRead
[VirtualGPIO] Pin 1 = HIGH
[       OK ] HAL_GPIO_PinWriteRead_Test.WriteRead
[ RUN      ] RTOS_Sim.BasicTaskExecution
[       OK ] RTOS_Sim.BasicTaskExecution
[ RUN      ] RTOS_Sim.DelayFunction
[       OK ] RTOS_Sim.DelayFunction
[==========] 6 tests from 4 test suites ran. (378 ms total)
[  PASSED  ] 6 tests.
```

> ⚠ Segmentation faults usually indicate missing virtual peripheral mocks or incorrect test configuration.

---

## 📝 Adding New Virtual Peripherals

1. Create an interface in `include/hal/` (e.g., `IADC.h`).
2. Implement the stub in `src/hal/` (e.g., `virtual_adc.h/.cpp`).
3. Register it in `hal_manager_stubs.cpp`.
4. Add unit tests in `tests/` using Google Test.

---

## 🛠 RTOS Simulation

* Implemented in `include/hal/rtos_sim.h`.
* Supports:

  * `RTOS::create_task(function<void()>)`
  * `RTOS::start_scheduler()`
  * `RTOS::delay_ms(int ms)`
* Fully software-based and optional—can be removed if hardware-only HAL is desired.
* Tested via `tests/test_rtos.cpp`.

---

## ⚠ Notes

* Fully modular: easy to add new drivers/tasks.
* No physical hardware required; pure software simulation.
* RTOS simulation is deterministic in tests for repeatable unit testing.