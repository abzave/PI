# Pi Calculation Benchmark in C++ (Windows API)

This project is a simple benchmark that calculates PI developed in C++ using WinAPI.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Requirements](#requirements)
4. [How to Compile and Run](#how-to-compile-and-run)
5. [Usage](#usage)

## Project Overview

This benchmark calculates up to 10 digits of Pi by using the [Leibniz Series](https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80) method. The benchmark can be run in the command line and using a simple GUI for Windows.

## Features

- **CPU Benchmark**: Times how long it takes the CPU to calculate different amounts of digits of Pi.
- **Pi Calculation**: Calculates up to 10 digits of Pi.
- **Command Line Interface**: Available to run using the command line.
- **Graphic User Interface**: GUI available for Windows.

## Requirements

- **C++ Compiler**: A C++ compiler supporting the C++11 standard or higher (e.g., MSVC or MinGW).
- **Windows OS for GUI**: The GUI version of the project is intended to run on a Windows platform due to its reliance on Windows-specific APIs.

## How to Compile and Run

### Step 1: Clone the repository

``` bash
git clone https://github.com/abzave/PI.git
cd PI
```

### Step 2: Compile the project

If you are using **Visual Studio**, you can open a new `.sln` file in Visual Studio and build the project.
Alternatively, for **MinGW**, you can compile the source file using:

``` bash
g++ "PI cmd/src/*.cpp" "PI cmd/include/*.h" -Wall
```

### Step 3: Run the program

Once compiled, run the executable. It will open the menu where the user can select the benchmark to run.

## Usage

1. Select the version of the benchmark to run. The available versions are: PI cmd (command line) and PI GR (GUI).
2. For command line execution:
    1. Enter the option number of the amount of digits to calculate.
3. For GUI execution:
    1. Select the amount of digits to calculate from the dropdown.
    2. Click the button `Calculate PI`.
