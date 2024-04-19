mod2gbt bgm_beautilfulGarage.mod beautiful_garbage 2

c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o bank_two_funcs.o bank_two_funcs.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o output.o output.c
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o gbt_player.o gbt_player.s
C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o gbt_player_bank1.o gbt_player_bank1.s

C:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yt3 -Wl-yo4 -Wl-ya4 -o main.gb bank_two_funcs.o main.o output.o gbt_player.o gbt_player_bank1.o

del *.ihx *.noi *.map *.o *.sym *.lst *.asm *.z80 *.adb