# Full-Chain SUID Privilege Escalation (x86-64)

A Proof-of-Concept project demonstrating an advanced, full-chain exploit on modern 64-bit Linux. This project successfully chains a Format String vulnerability with a Buffer Overflow to dynamically bypass state-of-the-art memory mitigations and achieve root privilege escalation.

## 🎯 Goal
To pop a stable `uid=0(root)` shell from an SUID binary by dynamically leaking memory addresses, surgically restoring the Stack Canary, aligning the stack to avoid `movaps` faults, and executing a Return-Oriented Programming (ROP) chain.

## ⚙️ Environment & Mitigations
* **OS:** Linux (Tested on Ubuntu/Kali)
* **Arch:** amd64 (x86_64)
* **Protections Defeated:** ASLR, PIE (Position Independent Executable), NX (Non-Executable Stack), Stack Canaries, and Full RELRO.
* **Protections Disabled:** `_FORTIFY_SOURCE`

## 🧩 Vulnerabilities Chained
1. **Format String Leak:** Exploited to dynamically leak the randomized Stack Canary and the Libc base address, defeating ASLR and PIE.
2. **Buffer Overflow:** Exploited to smash the stack, replace the Canary, and overwrite the Instruction Pointer (RIP).
3. **ROP Chain:** Hijacked execution flow to call `setuid(0)` followed by `system("/bin/sh")`.

## 🚀 Usage

**1. Compile the vulnerable target:**
*(Requires compiling with modern protections enabled, but disabling Fortify)*
```bash
gcc src/vuln.c -o src/vuln -fstack-protector-all -pie -fPIE -Wl,-z,relro,-z,now -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -O0 -g
```

**2. Set up the SUID permissions:**
*(To simulate a vulnerable system binary, it must be owned by root)*
```bash
sudo chown root:root src/vuln
sudo chmod 4755 src/vuln
```

**3. Run the exploit:**
```bash
python3 exploit/exploit.py
```

## 📝 Detailed Analysis & Walkthrough
For a comprehensive, step-by-step breakdown of the memory geography, GDB analysis, and offset calculations used to build this exploit, check out my technical blog post:

[![View Live Demo](https://img.shields.io/badge/Full_Writeup-View_Post-0077b5?style=for-the-badge&logo=bookstack&logoColor=white)](https://vedantk6403.github.io/my-portfolio/blog/privilege-escalation.html)


## 🔗 Connect with me:
[<img align="left" alt="LinkedIn" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/linkedin.svg" />](https://www.linkedin.com/in/vedant-karande-936787247/)
[<img align="left" alt="GitHub" width="22px" src="https://cdn.jsdelivr.net/npm/simple-icons@v3/icons/github.svg" />](https://github.com/Vedantk6403)
<br />
