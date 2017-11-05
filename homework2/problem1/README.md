# Problem 1

In problem1_ciphertext.txt is a ciphertext obtained with Vigenere's cipher from open text on Croatian language. Find length of the keyword, keyword itself and decrypt the text.

## Example usage:

```
g++ problem1.cpp -o p1
./p1

Kasiski test:
CXT-15 CXT-57  -> difference = 42
XTU-16 XTU-64  -> difference = 48
SQP-40 SQP-111  -> difference = 71
GIP-69 GIP-147  -> difference = 78
guess key length: 6

KNHUGBGPZROUGPOIZZKKGKOXUP  Ic = 0.0738462
RISBQSJCXXBHDSCIGBUWCZQCRS  Ic = 0.0584615
OYJSBFWBWWUGJALVLSGFBWFBA  Ic = 0.0615385
PWCATPJYACXGPOXTDTSPJZXOG  Ic = 0.0523077
ZPXIXXSMWXXIDCADXAQHRBAII  Ic = 0.0769231
FGTBTTQWXTTPWOWGGVPXGTVMP  Ic = 0.0892308

Satisfied? [y/n] y

for j=0, M_h=0.0703846 and h=20
for j=1, M_h=0.0587308 and h=12
for j=2, M_h=0.0626538 and h=8
for j=3, M_h=0.0646538 and h=11
for j=4, M_h=0.0575769 and h=18
for j=5, M_h=0.0577308 and h=7

key: GOSPIT
Satisfied? [y/n] n
Modify key? [y/n] y
Enter fully correct key: GOSPIC

open text:
EDWARDHUGHHEBERNPRONALAZACJEPRVENAPRAVEUKOJOJJEUTJELOVLJENPRINCIPROTORANAPRAVUJEIZUMIOTISUCUDEVETSTOPETNAESTEGODINEINAZVAOJUJEELEKTRICNISTROJZAKODIRANJE

```