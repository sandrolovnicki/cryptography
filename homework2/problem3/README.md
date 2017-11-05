# Problem 3

## Example usage:

```
g++ problem1.cpp -o p1
./p1

open text ? VERNAM
ciphertext? BJKDIW	

matrix equation AK=b for 0. and 2. pair of letters:
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
