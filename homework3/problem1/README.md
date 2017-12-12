# Problem 1

In ciphertext.txt is a ciphertext obtained with column transposition cipher from open text on Croatian language.
Decrypt the text if number of columns is greater than 4 and less than 16.

## Example usage:

```
g++ problem1.cpp -o p1
./p1

SEOZIKKILACUWHOZTSAJRDAATJWTISAROOOFRILTJIJREETATIDAENURINIIVBZIIAEMOFJJSAELHN
length: 78
78 = 2*3*13
type matrix dimensions (row column): 13 6

S H W T E A  2:4
E O T J N E  3:3
O Z I I U M  4:2
Z T S J R O  1:5
I S A R I F  3:3
K A R E N J  2:4
K J O E I J  3:3
I R O T I S  3:3
L D O A V A  3:3
A A F T B E  3:3
C A R I Z L  2:4
U T I D I H  3:3
W J L A I N  2:4

satisfied with matrix? [y/n] y

bigram occurrences table:
   | 1  2  3  4  5  6 
---|------------------
 1 |    2  1  3  1  1 
 2 | 2     1  5  3  1 
 3 | 0  6     2  2  2 
 4 | 5  1  1     4  3 
 5 | 1  6  0  2     5 
 6 | 1  1  1  7  3    

type key (permutation of {1,...,6}): 3 2 5 6 4 1
SOLUTION: 
WHEATSTONEJEIZUMIOSTROJZASIFRIRANJEKOJIJEKORISTIODVAALFABETARAZLICITIHDULJINAW

```
