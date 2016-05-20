# Galileo MRAA

A demonstrastion of MRAA pin-mux functionality on THe Galileo Gen2
board.

A potentiometer controls the blink rate of a the user LED on the
Galileo Gen2 board.  When a button connected to D3 is pressed, the
program exits.

## Sample Output

```
Process started (ID: 0x1019010)
libmraa version 0.1 initialized.
libmraa initialized for platform 'Intel Galileo Gen 2' of type 1
MRAA C Demonstration
LIBMRAA Version: 0.1
Board: Intel Galileo Gen 2
gpio: Set owner to 260115976
gpio: Set owner to 260115976
gpio: Set owner to 260115976
gpio: Set owner to 260115976
Vary the rate of blink by turning the poteniometer on A0
Exit the program by pressing the button on D3

Process exited with exit code 0


Process exited with code: 0
```
