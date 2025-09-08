# 🕹️ Word Search Game (C Language)

## 👤 Author
- Mohamed Khalil Nafati  
- Class: 1LNIG5  

---

## 📝 Project Overview
This project is a **word search game implemented in C**, which allows users to practice their word-finding skills in a fun and interactive way. The game offers several modes:  

1. **Single-player mode** – choose word length and display options.  
2. **Single-player with time constraints** – each attempt and the total game have a time limit.  
3. **Two-player mode** – players take turns, and after 3 rounds, a final score table is displayed.  

The game selects words based on user-defined criteria such as word length and allowed letters.  

---

<img width="576" height="300" alt="image" src="https://github.com/user-attachments/assets/e9f1e7a4-8cb8-44d3-9db1-85a08ab4f317" />


## 🎮 Gameplay Rules

### 1. Single-player
- User inputs must be **positive numbers**: 0, 1, 2, or 3  
- Word length must be **7, 8, or 9** (no symbols allowed)  
- Option to display **all words** or only the **longest words**

- <img width="593" height="347" alt="image" src="https://github.com/user-attachments/assets/5b18d49b-6145-4e66-aa82-d1b2b877c2df" />


### 2. Single-player with time constraints
- Each attempt has a time limit `t = word length`  
- Total allowed time = `t * t`

- <img width="1039" height="396" alt="image" src="https://github.com/user-attachments/assets/361ed403-a60b-4341-ab49-97fa5fafbfa4" />


### 3. Two-player mode
- User chooses a **positive even number < 26** as word length  
- Players alternate attempts  
- After 3 rounds, the **score table** is displayed; ties are possible

- <img width="1078" height="693" alt="image" src="https://github.com/user-attachments/assets/48c30736-d1ee-42f3-a30a-326e2adb27c5" />

- <img width="1078" height="468" alt="image" src="https://github.com/user-attachments/assets/5955978e-14a5-4f73-9f1f-8efb912b43d8" />



---

## 🔹 Key Functions

### Alea_caractere
Generates random characters:  
- `'v'` → random vowel  
- `'c'` → random consonant  
Uses `rand()` for randomization.  

### Supp_Accents
Removes accents from a given word, e.g., `'à', 'â', 'ä'` → `'a'`; `'é', 'è', 'ê'` → `'e'`.  

### Mots_Possible
Finds all possible words from a given set of letters:  
- Checks each word in the dictionary  
- Marks letters used with `'*'`  
- Stores valid words in the `Possible[]` array  

### Word Validation Loop
- Tracks attempts and time for each input  
- Checks if a word is valid using `test()`  
- Adds valid words to `Mots_Saisie[]`  
- Alerts user if attempt or total time is exceeded  

### Recherche
- Checks if a word already exists in **J1** or **J2** arrays (used to store player words)  
- Prevents duplicate entries  

---

## ⚙️ C Standard Functions Used
- `fflush(stdin)` – clear input buffer  
- `strcpy()` – copy strings  
- `toupper()` – convert letters to uppercase  
- `atoi()` – convert string to integer  
- `strcmp()` – compare strings  
- `rand()` / `srand()` – generate pseudo-random numbers  

---

## 💡 Conclusion
This code provides a solid base for a word search game.  
To improve:  
- Enhance input validation and security  
- Add more interactive features for better user experience  

---

## 📚 Resources
- [YouTube Tutorial 1](https://www.youtube.com/watch?v=2ybLD6_2gKM)  
- [YouTube Tutorial 2](https://www.youtube.com/watch?v=FvWvI0i8vkE)  
- [Stack Overflow](https://stackoverflow.com)  
- [ChatGPT](https://chat.openai.com) (for syntax corrections)  

---

## ⚡ How to Run
1. Compile the program using GCC:  
```bash
gcc word_search_game.c -o word_search
