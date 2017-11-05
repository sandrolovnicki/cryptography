# Problem 3

Find the key K in Hill's cipher if m=2 and pair (open text, ciphertext) is known.

## Example usage:

```
g++ problem1.cpp -o p1
./p1

open text ? VERNAM
ciphertext? BJKDIW	

matrix equation AK=b for pairs of letters starting at index 0 and 2:
|21  4| |k1 k2|  =  |1   9|
|17 13| |k3 k4|     |10  3|

detA      = 23
(detA)^-1 = 17

A^-1 = |13 10|
       |23 19|

K = |9  17|
    |5   4|

testing all pairs:
|V E| |9  17| = |B J|
      |5   4|
|R N| |9  17| = |K D|
      |5   4|
|A M| |9  17| = |I W|
      |5   4|
is this OK? [y/n] y

```
