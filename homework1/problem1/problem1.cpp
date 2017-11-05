/***********************************************************************************************************************
 *
 * Author: Sandro Lovnički
 *
 * College: University of Zagreb, Faculty of Science, Department of Mathematics
 * Graduate Programme: Computer Science and Mathematics
 *
 *
 * Project: Cryptography and Network Security, Homework1, Problem1
 * Task: Decrypt the ciphertext "ITLTATW" obtained with the Caesar cipher
 *
 * Build: g++ problem1.cpp -o problem1_exe
 * Run: ./problem1_exe
 *
 ***********************************************************************************************************************
 * USAGE:
 *   You will be prompt to enter ciphertext after which 2 possible program "modes" follow.
 *     1. If you just pressed newline, default ciphertext from original Task will be used and automatically correct
 *        decrypted solution will be shown (which I know by now). This mode is just for fast checking the correctness
 *        of assignment
 *     2. You can enter any string of CAPITAL LETTERS and see all 26 possibilities of Caesar cipher encryption. You can
 *        then choose key value K to test inverse e_K(d_k(ciphertext)).
 *
***********************************************************************************************************************/

#include <iostream>

std::string Caesar_e(std::string open_text, int key)
{
    std::string ret = "";
    key %= 26;
    for(int i=0; i<open_text.length(); i++)
        ret += open_text[i]-key < 65 ? open_text[i]+26-key : open_text[i]-key;
    return ret;
}

std::string Caesar_d(std::string ciphertext, int key)
{
    std::string ret = "";
    key %= 26;
    for(int i=0; i<ciphertext.length(); i++)
        ret += ciphertext[i]+key > 90 ? ciphertext[i]-26+key : ciphertext[i]+key;
    return ret;
}

int main()
{
    std::string ciphertext;
    std::string open_text;
    std::cout << "Enter ciphertext (default: ITLTATW): "; getline(std::cin, ciphertext);
    if(ciphertext.empty()) ciphertext = "ITLTATW";

    std::cout << "-------------------------------------------------------------" << std::endl;
    for(int key=0; key<26; key++)
        std::cout << "K=" << key << (key < 10 ? " " : "") << " => d_K(" << ciphertext << ") = " << Caesar_d(ciphertext, key) << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;;

    int key;
    if(ciphertext == "ITLTATW") { key=21; std::cout << "Solution: K=21, d_21(ITLTATW) = DOGOVOR" << std::endl; }
    else { std::cout << "Test key K="; std::cin >> key; }
    std::cout << "Check inverse: e_" << key << "(" << Caesar_d(ciphertext, key) << ") = " << Caesar_e(Caesar_d(ciphertext,key),key) << std::endl;

    return 0;
}