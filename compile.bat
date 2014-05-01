@echo off
gcc -o test.exe -lm -std=c99 test.c rpn.c stack.c opmap.c
echo compiled to text.exe
