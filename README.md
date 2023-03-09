# pic-template

This repo is just a place to store documentation and library functions from [ECE 376 - Embedded Systems](http://www.bisonacademy.com/ECE376/Index.htm) (taught by Dr. Jacob Glower) so that I don't forget it.
Specifically, this project uses the HI-TECH C Compiler for the PIC18F4620.

I also aimed to make the functions more readable by formatting the C files and adding better variable names and comments.

Right now the `template.c` file builds, and I know from ECE 376 that most of the functions work.
I haven't tested all the functions yet, though, so they may need some work to get right.

## Dependencies

In order to build this project you need a few tools.

- [MPLABX](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [HI-TECH C](http://www.bisonacademy.com/Software/HCPIC18-pro-9.63PL3.zip)
- [PIC Flash Tool](http://www.bisonacademy.com/Software/PIC_Flash_Tool_1.2.exe)

These tools can all be found on [BisonAcademy](http://www.bisonacademy.com/ECE376/Resources.htm)

One thing to note is that the `nbproject/configurations.xml` file contains some build details by default such as:

- Microcontroller to build for (PIC18F4620)
- Compiler to use (HI-TECH C)
- Code Offset (0x800)

These should be good for everyone with the default installations of the above links, but you may need to verify that the settings are correct for you project and tools. I used [MPLABX.pdf](docs/MPLABX.pdf) as a guide.

## Getting Started

1. Clone this repo or more properly create a new repo using this repo as a template
2. Open MPLABX IDE
3. Select File->Open Project (Ctrl + Shift + O)
4. Select the folder where the repo is cloned
5. Clean/Build the project

## Documentation

Doxygen style comments are used to create documentation for the helper functions in `lib/`. To generate html docs, [install Doxygen](https://www.doxygen.nl/download.html) (and add the Doxygen bin directory to the PATH) and run `doxygen` in the terminal to generate docs in `docs/`.

**TODO** - Add comments to LCD functions
