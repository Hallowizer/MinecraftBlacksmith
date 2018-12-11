# Contributing
We currently do not have a developer's agreement. If you submit a pull request, we will create an agreement before merging.

## Copyright Warning
While MinecraftBlacksmith is licensed under BSD-2-Clause, Minecraft is under exclusive copyright. By law, you are not allowed to publish Minecraft's source code. However, you are allowed to submit patches, as they are not major chunks of Minecraft's code.

## Windows 10 Edition Source Code
If you would like to get a copy of the Windows 10 Edition source code, you will need it installed. If you do not have a PC, you can get Windows 10 Enterprise Edition [here](https://developer.microsoft.com/en-us/windows/downloads/virtual-machines), and run Windows 10 within a virtual machine. At one point, Minecraft Windows 10 edition came with Java Edition, so if you bought Minecraft before fall 2018, all you need to do to get the game is redeem the code found on your [Mojang account page](https://account.mojang.com/me). When you have the game, navigate to the path `C:\Program Files\WindowsApps`. Find the folder that starts with `Minecraft`, then has a ton of numbers. In there, you will find a `Minecraft.Windows.exe`. Once you obtain Minecraft's binary, you can disassemble it with `objdump`, then you can run MinecraftBlacksmith's `processasm` tool to remove extra binary numbers.