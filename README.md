## Neural Network Visualizer

An interactive, object-oriented C++ application to **build**, **train**, **test**, and **visualize** a fully connected feedforward neural network on the **MNIST** dataset.

---

### Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Live Demo](#live-demo)
- [Installation](#installation)
- [Usage](#usage)
- [Object-Oriented Design](#object-oriented-design)
- [Future Work](#future-work)

---

### Overview

This project visualizes a feedforward neural network implemented **from scratch** in C++, trained on the **MNIST** dataset. The application includes a graphical interface built using **SFML**, allowing users to build custom networks interactively and observe their learning process in CLI.

---

### Features

- Visual creation of layers and neurons via GUI
- Manual training on MNIST dataset
- Training and testing display in the CLI
- Forward and backward propagation written from scratch
- Modular, reusable class structure (OOP principles)

---

### Example Usage

<center>

![Example Usage](./exampleUsage.png)

</center>

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/efemuratucarli/NeuralNetworkVisualizer.git
   cd NeuralNetworkVisualizer
   ```

2. Open the `Project.sln` file with **Visual Studio 2022** or newer.

3. Ensure **SFML** is properly installed and linked.

4. Build and run the project.

---

### Usage

- Click "Add Layer" to add hidden layers.
- Use "Train" to start training on MNIST.
- Watch real-time feedback in the console.
- "Test" the model after training is completed.

---

### Object-Oriented Design

- **Network**: Manages layers and training logic.
- **Layer**: Manages a collection of neurons and their layout within a network layer.
- **Neuron**:  Represents a single computational unit in the network, contains key variables related to training and test phases.
- **Button**: Triggers actions via GUI.
- **Input**:  Renders the 28×28 grayscale image as a grid of 10×10 blocks per pixel, providing real-time visual feedback for the network’s input.
- **Utility Modules**: `Activation`, `DatasetLoader`.

Each class follows OOP principles **encapsulation**, **aggregation**, and **abstraction** for maintainability and extensibility.

---

### Future Work

- Add support for other kinds of networks
- Export results as `.txt` or `.csv`
- Improve graphical output of performance metrics
- Extend dataset loading to non-MNIST formats