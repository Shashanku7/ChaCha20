# ChaCha20

 **ChaCha20** is a **256-bit stream cipher** designed by           
  **Daniel J. Bernstein**, based on a **512-bit internal state.**  
 It operates using **20 rounds** of **quarter-round transformations** on a **4×4 matrix of 32-bit words.**  
 The output keystream is **XORed** with plaintext for encryption, ensuring high performance and resistance to timing attacks.




## Compilation and Execution

__For Windows Users:__
  > Make sure git and g++ is installed in your system for cloning and compiliation purpose, if not installed follow these steps:
 (If installed directly move on to step 6)
 1) Ensure MSYS2 is installed: If you haven't installed MSYS2 yet, run the following command in PowerShell to install it:
 ```powershell
     winget install MSYS2.MSYS2
 ```
  
  After installation, open the MSYS2 terminal from the Start Menu (search for "MSYS2").

 2) Once inside the MSYS2 terminal, update the package database and core system packages by running:
 ```powershell
      pacman -Syu
  ```

3) Now, install g++ with:
```powershell
     pacman -S mingw-w64-ucrt-x86_64-gcc
```

 4) Add C:\msys64\ucrt64\bin (or similar path depending on architecture) to your system PATH so that g++ can be used in PowerShell or CMD.

5) Install git for windows using the link: [Git](https://git-scm.com/downloads/win)

6) Clone the repository using the command:
```powershell
  git clone https://github.com/Shashanku7/ChaCha20
  cd ChaCha20
```

7) Run these commands and execute the code:
```powershell
 g++ -I include src/*.cpp -o chacha20
./chacha20   <file name\> e|d
```
8) Verify the results by opening the .enc or .dec file generated

-----
__For Unix Based Systems:__

1) Install the necessary packages for cloning and compilation:
For Debian Based Distributions:
```shell
   sudo apt install git g++ make cmake 
```
For Arch Linux based Distributions:
```shell
      > sudo pacman -S git gcc make cmake
```
2)  Clone the repository using the command:
```shell
    > git clone https://github.com/Shashanku7/ChaCha20
    > cd ChaCha20
```

3) Generate and run the build files using:
 ```shell
      cmake -B bin
      cmake --build bin
      cd build
      .\chacha20 <filename> e|d
  ```
  4) open the .enc or .dec files generated to verify the results

----
