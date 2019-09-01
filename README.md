
# LinuxCNC Pendant

This is a pendant for linuxCNC using an SparkFun SAMD21 Dev Breakout but with little or no changes to the program you can run this on other arduino UNO style board.

## Getting Started

**warning** this project may require some changes to make it work properly with your hardware

The project is divided in 4 directories:
* model - a FreeCAD project of the enclosure and a G-code for cutting it
* PCB - a kicad project of the PCB
* Arduino
* Python

### Prerequisites

I suggest you check the PCB before starting beacause there will be maybe some issues: (eg: spacings, SMD parts filipped, ecc..)

for running python program you need the following packages:
* linuxCNC
* TkInter
* tk-tools
* pyserial

### Installing

Upload arduino 'remoteCNC' project on the board and run the python 'remoteCNC' program on a PC with linuxCNC running

## Running the tests

To check pushbuttons and analog input use the 'remoteCNC_test' program on both arduino and PC side.

## Contributing

This project expecially the software in not completed so you are free to contribuite in any way you want.

## Authors

* **Francesco Osti** - *Initial work* - [fran-retfie](https://github.com/fran-retfie)

See also the list of [contributors](https://github.com/fran-retfie/LinuxCNCpendant/contributors)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
