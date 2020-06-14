Here's a link to the [original README.md](README-upstream.md)

# Portable Grbl
This project has the goal to improve the portability of the well-known [Grbl project](https://github.com/gnea/grbl).

Grbl is a well known project, but it's highly tied to the AVR ATMega microcontroller architecture. The project now seems struggled by the limits of the chosen architecture. No resources for more more axes, no  resources for higher motion speeds, no resources for more functionality.

This project makes an attempt to improve portability by separating hardware-dependent stuff from general code, and by allowing to add new supported platforms with a minimal touch of the general code.

For beginning, focus will be on the STM32 platform. Being widespread and cheap, and at the same time by providing much more power and resources, this has a chance to become a popular replacement for the ATMega chips. More than that, there are a lot of cheap STM32 boards that are completely ready to replace the "Arduino + CNC Shield" combo. Those boards are originally developed for the Mach3 software, but by simply replacing firmware we can get a cheap complete Grbl/STM32 solution.
