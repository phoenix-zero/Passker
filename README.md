# Passker

## A GUI password asker

Passker is a lightweight Qt based GUI password asker.

- Forgot to start Vim/NVim with sudo permissions? We have got you covered
```
:w !sudo tee > /dev/null %
```
- On a GUI IDE and need to provide ssh passphrase? Use Passker

## Export Passker as your default ASKPASS
```
export SUDO_ASKPASS=Passker
export SSH_ASKPASS=Passker
```

## AUTHORS
[Anubhab Mukherjee](https://www.github.com/phoenix-zero)
[Soham Kar](https://www.github.com/2bit-hack)
