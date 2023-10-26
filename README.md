# C++ Shape Manipulation Program 

## Program Description

This C++ program is designed to work with various shapes, including rectangles and composite shapes, in an object-oriented manner. It allows you to read shape descriptions from an input file, perform operations like moving and scaling, and then sort and display the shapes.

## Usage
The program reads shape descriptions from an input file, including rectangles and composite shapes.

You can perform operations like moving and scaling on the shapes as specified in the input file.

The program then sorts the shapes by their area and displays the sorted results.

Invalid or unsupported shape descriptions are ignored.

## Input Format
The input file format should be as follows:

```
RECTANGLE leftX leftY rightX rightY
COMPLEX N
RECTANGLE leftX leftY rightX rightY
RECTANGLE leftX leftY rightX rightY
...
COMPLEXEND
MOVE x y
SCALE posX posY k
...
```

RECTANGLE: Describes a rectangle with its left-bottom and right-top coordinates.

COMPLEX N: Starts a complex shape that includes N rectangles.

COMPLEXEND: Ends the complex shape description.

MOVE x y: Moves all shapes by x and y.

SCALE posX posY k: Scales all shapes around the point (posX, posY) by factor k.

