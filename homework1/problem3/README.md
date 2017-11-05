# Problem 2

## Example usage:

```
g++ problem3.cpp -o p3
./p3

--- ciphertext to decrypt ---
BNTQW PFXNA ENGWC DXAWI NCEFI PBCDX ADAPV UPUWD CEDBP NGDYW VWAWN GINCE FIPBC NQAPE VNINA WTPVD OPRXP QWEDO PCDXA PUWTN QDRPD OWINX APVSD CFQWP FXNAE FEGNA SFCBP RWBNU NOCWO UWADQ AMDVP GUWEA NGP

How many most frequent letters you want to see? 26
26 most frequent letters:  P(18), N(17), W(16), A(14), D(14), C(10), E(9), F(7), X(7), B(6), V(6), U(6), Q(6), I(6), G(6), O(5), R(3), T(3), S(2), M(1), Y(1), L(0), K(0), J(0), H(0), Z(0)

How many most frequent bigrams you want to see? 40
40 most frequent bigrams:  AP(4), XA(4), IN(4), NG(4), NA(4), UW(4), CE(3), AW(3), DX(3), CD(3), DO(3), EF(3), PV(3), QW(3), ED(2), DC(2), PU(2), WE(2), BC(2), PR(2), BP(2), OP(2), WT(2), WA(2), BN(2), NQ(2), QA(2), FX(2), PB(2), IP(2), WP(2), FI(2), NC(2), XN(2), WI(2), AE(2), PF(2), AD(2), CB(1), SF(1)

How many most frequent threegrams you want to see? 25
25 most frequent threegrams:  DXA(3), CDX(3), DOP(2), PUW(2), APV(2), PBC(2), IPB(2), FIP(2), EFI(2), CEF(2), NCE(2), INC(2), WIN(2), XAP(2), NAE(2), XNA(2), FXN(2), PFX(2), WPF(2), QWP(2), NOC(1), FEG(1), PVS(1), VSD(1), SDC(1)

How many most frequent quadgrams you want to see? 15
15 most frequent threegrams:  CDXA(3), INCE(2), QWPF(2), WPFX(2), PFXN(2), FXNA(2), XNAE(2), NCEF(2), IPBC(2), FIPB(2), EFIP(2), CEFI(2), NXAP(1), XAPV(1), OWIN(1)

type your guesses in the form open_text_letter->ciphertext_letter
example: P->S (meaning P gets encrypted into S)
type '-' if you are done with guessing

guess 1: W->H
guess 2: X->J
guess 3: Y->K
guess 4: Z->M
guess 5: A->N
guess 6: B->O
guess 7: C->Q
guess 8: E->W
guess 9: F->X
guess 10: G->Y
guess 11: H->Z
guess 12: I->P
guess 13: -


--- open text obtained with this substitution ---
_A_CE I_FA_ _A_E_ _F_E_ A____ I___F ___I_ _I_E_ ____I A__GE _E_EA __A__ __I__ AC_I_ _A_A_ E_I__ BI_FI CE__B I__F_ I_E_A C__I_ BE_AF _I___ __CEI _FA__ ___A_ ____I _E_A_ AB_EB _E__C _Z__I __E__ A_I

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 
N O Q _ W X Y Z P _ _ _ _ _ _ _ _ _ _ _ _ _ H J K M 


What do you want to do? [add/remove/quit, default - guess again] remove

type open text letter which you want to remove from guesses
remove: C

--- open text obtained with this removal ---
_A__E I_FA_ _A_E_ _F_E_ A____ I___F ___I_ _I_E_ ____I A__GE _E_EA __A__ __I__ A__I_ _A_A_ E_I__ BI_FI _E__B I__F_ I_E_A ___I_ BE_AF _I___ ___EI _FA__ ___A_ ____I _E_A_ AB_EB _E___ _Z__I __E__ A_I

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 
N O _ _ W X Y Z P _ _ _ _ _ _ _ _ _ _ _ _ _ H J K M 


What do you want to do? [add/remove/quit, default - guess again] add

type your add in the form open_text_letter->ciphertext_letter
example: P->S (meaning P gets encrypted into S)
add: C->T

--- open text obtained with this change ---
_AC_E I_FA_ _A_E_ _F_E_ A____ I___F ___I_ _I_E_ ____I A__GE _E_EA __A__ __I__ A__I_ _A_A_ ECI__ BI_FI _E__B I__F_ I_ECA ___I_ BE_AF _I___ ___EI _FA__ ___A_ ____I _E_A_ AB_EB _E___ _Z__I __E__ A_I

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 
N O T _ W X Y Z P _ _ _ _ _ _ _ _ _ _ _ _ _ H J K M 


What do you want to do? [add/remove/quit, default - guess again]
```
