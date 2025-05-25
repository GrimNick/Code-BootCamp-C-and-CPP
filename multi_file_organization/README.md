# 🔍 Misspelled Word Detection in C/C++

This project implements a simple **spell-checking system** that reads an English dictionary and a block of text, then identifies all the **misspelled words** — i.e., words in the text that are not present in the dictionary.

It is a part of a bootcamp module on **vector algebra and set operations using C/C++**, with a focus on **modular multi-file project structure**.

---

## 📄 Problem Description

You are given:
1. A **dictionary file** containing valid English words (one per line).
2. A **text file** containing a block of text.

The goal is to output all the words from the text that are **not present in the dictionary**, assuming whitespace-delimited word boundaries.

---

## 🧠 Mathematical Model

Let:
- `Sd` = Set of words from the dictionary file  
- `St` = Set of words from the input text  
- `Sw` = Set of misspelled words

Then:
```math
Sw = St - Sd
