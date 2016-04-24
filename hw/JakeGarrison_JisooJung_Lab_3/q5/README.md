# Bit Reduce

#### Source
It is all in the `reduce.c` source code
`cd ~/q5/` for source

#### To execute

* `gcc -std=c99 reduce.c -ljpeg -o reduce.o`
* `./reduce.o NUM_OF_BITS` where NUM_BITS is the bit reduce value. Leave blank for defult of 5 aka 32 levels of RGB


#### Alias
* type `source alias`
* then you can use `build` to compile
* then `./reduce.o NUM_OF_BITS`
* athen `disp` to show the images (need desktop screen)
