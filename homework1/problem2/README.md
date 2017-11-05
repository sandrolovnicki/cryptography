# Problem 2

## Example usage:

```
g++ problem2.cpp -o p2
./p2

--- ciphertext to decrypt ---
GEOBW KAWZB RGJTW AFHIE GQLOD DOBQI TWRUE WILOA IFGKR GQWDB WBGTL OJWQO IZQFI SIZWT GTGAI TIFAB WKGLO DDOBQ ITIJQ FBILQ OXIKO IAIBW QFWFW UGEOB WKAIL JILQK W

How many most frequent letters you want to see? 10
10 most frequent letters:  I(17), W(15), O(11), B(10), G(10), Q(10), A(7), F(7), L(7), G(7)

How many most frequent bigrams you want to see? 8
8 most frequent bigrams:  BW(5), OB(4), AI(4), IL(4), LO(4), IT(3), QF(3), LO(3)

type your 2 guesses in the form open_text_letter->ciphertext_letter
example: P->S (meaning P gets encrypted into S)
guess 1: A->I
guess 2: E->W

BASED ON YOUR 2 CHOICES, THESE ARE CONGRUENCES FOR COMPUTING A KEY (a,b)

a*0 + b = 8 (mod 26)  &&  a*4 + b = 22 (mod 26)

solutions:
KEY0 = (10,8)    check: 10*0 + 8 = 8 (mod 26)  &&  10*4 + 8 = 22 (mod 26)
KEY1 = (23,8)    check: 23*0 + 8 = 8 (mod 26)  &&  23*4 + 8 = 22 (mod 26)

KEY0 -> a has no inverse
KEY1 -> a^-1 = 17
--- open text obtained with this key ---
SKYLE IUEDL XSRFE UBJAK SGZYT TYLGA FEXWK EAZYU ABSIX SGETL ELSFZ YREGY ADGBA OADEF SFSUA FABUL EISZY TTYLG AFARG BLAZG YVAIY AUALE GBEBE WSKYL EIUAZ RAZGI E


Does this look OK to you? [y/n] n

type your 2 guesses in the form open_text_letter->ciphertext_letter
example: P->S (meaning P gets encrypted into S)
guess 1: O->I
guess 2: I->W

BASED ON YOUR 2 CHOICES, THESE ARE CONGRUENCES FOR COMPUTING A KEY (a,b)

a*14 + b = 8 (mod 26)  &&  a*8 + b = 22 (mod 26)

solutions:
KEY0 = (2,6)    check: 2*14 + 6 = 8 (mod 26)  &&  2*8 + 6 = 22 (mod 26)
KEY1 = (15,6)    check: 15*14 + 6 = 8 (mod 26)  &&  15*8 + 6 = 22 (mod 26)

KEY0 -> a has no inverse
KEY1 -> a^-1 = 7
--- open text obtained with this key ---
AMERI CKIDR ZAVNI KTHOM ASJEF FERSO NIZUM IOJEK OTACZ ASIFR IRANJ EVISE ODSTO GODIN ANAKO NOTKR ICAJE FFERS ONOVS TROJS EPOCE OKORI STITI UAMER ICKOJ VOJSC I


Does this look OK to you? [y/n] y
```
