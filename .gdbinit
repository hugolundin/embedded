target extended-remote localhost:3333
set remote exec-file main.elf

monitor arm semihosting enable
monitor reset halt
monitor debug_level -2
