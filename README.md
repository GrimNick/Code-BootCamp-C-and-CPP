# Code-BootCamp-C-and-CPP

# 🔤 Spell Checker & Auto Suggestion System in C++

This project implements solutions for two core NLP tasks using **basic vector algebra and set theory**, developed during a C/C++ bootcamp. The problems addressed are:

1. ✅ **Misspelled Word Detection from Text**
2. ✨ **Auto Suggestion System for Incomplete Words**

> 🛠️ Built using modern C++11 in a multi-file, modular architecture. Ideal for beginner-level students learning NLP, data modeling, and vector operations in C++.

---

## ⚙️ Programming Environment

- **Language**: C/C++
- **Compiler**: GCC/G++ with C++11 support
- **IDE Recommended**: [CLion](https://www.jetbrains.com/clion/) (free for academic use), CodeBlocks, or VSCode
- **Structure**: Multi-file project using `.h` and `.cpp` separation

---

## 📁 Data Sources

The required dictionary and input files are available via Google Drive:

### 📌 Problem 1: Misspelled Words Detection
- 📘 [Dictionary File](https://drive.google.com/file/d/1uQ8HRCYOUmtF5zCNOhxMy7gbsL2QBwXM/view?usp=sharing)
- 📝 [Input Text File](https://drive.google.com/file/d/1rai8WShc8QrT1gVjc0SwK1MKDXrwLJH3/view?usp=sharing)

### 📌 Problem 2: Auto Suggestion System
- 📗 [Word List (Sample from Google 10,000 English)](https://drive.google.com/file/d/1r3xWVOavkgsn4pKy6kzPU9pAj3tmeuom/view?usp=sharing)

---

## 🚀 Day 1: Misspelled Word Detection

### 🧠 Problem Description
Detect all **misspelled words** in a given text by comparing it to a dictionary of correct English words.

### 🧮 Mathematical Model
Let:
- `Sd` = Set of words in the dictionary  
- `St` = Set of words in the input text  
- `Sw` = Set of misspelled words

Then:
```math
Sw = St - Sd
