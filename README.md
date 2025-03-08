# MLP Digit Recognizer


## 📝 Overview
This project implements a **Multilayer Perceptron (MLP)** neural network to recognize handwritten digits from the **MNIST dataset**. It includes functionalities for:
- Loading **pre-trained parameters**
- Processing **grayscale images**
- Predicting the digit along with its probability

## 📦 Installation & Building

### 1️⃣ Clone the Repository
```bash
git clone <repository-url>
cd <repository-name>
```

### 2️⃣ Compile using the Makefile
```bash
make
```

### 3️⃣ Run the Executable
```bash
./main
```

## 🚀 Usage
The `main.cpp` file serves as the application's entry point and demonstrates how to:
✅ Load pre-trained weights and biases from the `parameters/` folder
✅ Read a **28x28 grayscale image** from `images/` or another source
✅ Process the image through the **MLP network**
✅ Output the **predicted digit** and its **probability**

### ▶️ Running the Program
Ensure the `parameters/` and `images/` folders contain the necessary sample data, then execute:
```bash
./main
```

### 📌 Example Output
```
Predicted digit: 7
Probability: 0.95
```

## 📂 Preparing Input Data
If the `parameters/` and `images/` folders are missing, follow these steps:

### 🔢 Parameters
The network requires weight matrices and bias vectors:
- **Weight Matrices:**
  - `128x784`, `64x128`, `20x64`, `10x20`
- **Bias Vectors:**
  - `128x1`, `64x1`, `20x1`, `10x1`

**Options:**
- Obtain **pre-trained** weights/biases from a compatible source
- Save them as raw float data in files (e.g., `w1.bin`, `b1.bin`, etc.) and update `main.cpp`

### 🖼️ Images
Input images should be **28x28 grayscale images** flattened into a **784x1 array** (row-major order).

#### Steps:
1. Download MNIST data from [Yann LeCun's MNIST database](http://yann.lecun.com/exdb/mnist/).
2. Convert sample images into a **784x1 float array** (normalized between `0.0` and `1.0`).
3. Save the processed image in a readable format for `main.cpp`.
4. Modify `main.cpp` to load custom parameter and image files.

## 🔍 Network Architecture
```
(Input)  -> [ 784 neurons ]
          -> [ 128 neurons (ReLU) ]
          -> [  64 neurons (ReLU) ]
          -> [  20 neurons (ReLU) ]
(Output) -> [  10 neurons (Softmax) ]
```

- **Input Layer:** 784 neurons (flattened 28x28 image)
- **Hidden Layer 1:** 128 neurons (ReLU activation)
- **Hidden Layer 2:** 64 neurons (ReLU activation)
- **Hidden Layer 3:** 20 neurons (ReLU activation)
- **Output Layer:** 10 neurons (Softmax activation; representing digits 0-9)

The network outputs a **probability distribution** over digits and selects the one with the **highest probability**.

## 🛠 Contributing
Contributions are welcome! 🎉 Feel free to:
- Fork the repository
- Submit issues
- Create pull requests to improve the project

## 📜 License
This project is licensed under the **MIT License**.

---
✉️ For any queries, feel free to contact the project maintainer!

---
