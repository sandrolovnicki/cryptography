# Problem 2

In ciphertexts.txt are 2 ciphertext obtained with same key from open texts on Croatian language.
Decrypt the texts if encryption is of form yi = xi + ki (mod 26) and open texts both start with one of four letters: S, P, N, D.

## Example usage:

```
g++ -std=c++11 problem2.cpp -o p2
./p2

YGHJYOU
MDJUHYS

guess 1. letter in first open text: P
open text 1: P
open text 2: D
rewind? [y/n] n
done? [y/n] n

guess 2. letter in first open text: R
open text 1: PR
open text 2: DO
rewind? [y/n] n
done? [y/n] n

guess 3. letter in first open text: E
open text 1: PRE
open text 2: DOG
rewind? [y/n] n
done? [y/n] n

guess 4. letter in first open text: D
open text 1: PRED
open text 2: DOGO
rewind? [y/n] n
done? [y/n] n

guess 5. letter in first open text: M
open text 1: PREDM
open text 2: DOGOV
rewind? [y/n] n
done? [y/n] n

guess 6. letter in first open text: E
open text 1: PREDME
open text 2: DOGOVO
rewind? [y/n] n
done? [y/n] n

guess 7. letter in first open text: T
open text 1: PREDMET
open text 2: DOGOVOR
rewind? [y/n] n
done? [y/n] y

```
