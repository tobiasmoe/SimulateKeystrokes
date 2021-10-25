# SimulateKeystrokes

## Description
Simple C++ program to simulate keystrokes based on a specific given dataset called [Keystroke Dynamics - Benchmark Data Set](https://www.cs.cmu.edu/~keystroke/). This program was created for my own msthesis where I needed a program to simulate keystroke dynamics. The cpp program is very simple, and uses the Windows function [SendInput](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendinput) to simulate keystrokes.
This program also uses your cursor when running.

## Requirements
* Webpage that can collect keystrokes.
* A way to run the cpp program, (Visual Studio 2019, Visual Studio Code, etc).
* Windows.

## Program behaviour
* Navigate to the browser (this is done by clicking on the taskbar)
* Navigate to the input field (this is done by clicking on the input field)
* Simulate the keystrokes

## Instructions
* Copy this repository
* Add the cpp file in your IDE program, e.g. Visual Studio Code
* Change code in file
  * Function focusWebPage() has two SetCursorPos() that you have to (most likely) change the x and y coordinate on
  * Line 48 function myFile.open(), change this to the file you want to read from (e.g., the files included in this repo


For any questions email me at: tobben166@hotmail.com
