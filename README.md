# 🐚 BasicShell

> A robust, low-level Linux shell implementation in C++17.

![Linux](https://img.shields.io/badge/OS-Linux-orange?logo=linux)
![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue?logo=c%2B%2B)
![Status](https://img.shields.io/badge/Status-Functional-success)

`BasicShell` is a lightweight command-line interpreter that bridges the gap between high-level C++ logic and the raw power of the Linux Kernel. It manages the full process lifecycle—from parsing strings to handling signals and process execution.

---

## 🏗️ The Architecture

At its core, this shell implements the **"Holy Trinity"** of Systems Programming:

1.  **Forking**: Cloning the parent process to create an isolated execution environment.
2.  **Execution**: Using `execvp` to perform a "brain transplant," replacing the child's memory with a new binary (like `vim` or `discord`).
3.  **Synchronization**: The parent process waits for the child to finish, capturing exit codes and signals to ensure system stability.

---

## ✨ Key Features

### 🛠️ External Program Support

Launches any program found in the system `PATH`.

- **Tested with**: `vim`, `python3`, `git`, and even GUI apps like `discord`.

### 📂 Smart Navigation (`cd`)

Custom implementation of directory traversal.

- **Home Support**: Resolves `cd` (no arguments) to `std::getenv("HOME")`.
- **Path Shortening**: Automatically replaces the long absolute path with `~` in the prompt for a cleaner UI.

### 🛡️ Signal & Error Handling

- **Exit Code Recovery**: Uses `WIFEXITED` and `WEXITSTATUS` macros to report failed commands.
- **Suicide Protection**: Masks `SIGINT` (Ctrl+C) so the shell stays alive even if the child process is interrupted.

---

## 💻 Technical Deep Dive

### Signal Shielding Logic

One of the biggest challenges was preventing the shell from dying when a user interrupts a child process.

```cpp
// Parent (Shell) ignores the signal
signal(SIGINT, SIG_IGN);

if (fork() == 0) {
    // Child restores default behavior to remain mortal
    signal(SIGINT, SIG_DFL);
    execvp(...);
}
```

🚀 Getting Started
Build
```Bash

g++ *.cpp -o BasicShell -std=c++17
```
Run
```Bash

./BasicShell
```
🎯 Roadmap

    [x] Basic command execution

    [x] cd with ~ path formatting

    [x] Signal handling (Ctrl+C)

    [ ] I/O Redirection (>)

    [ ] Piping (|)

    [ ] Background execution (&)

Developed by dequsa.
