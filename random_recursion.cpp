#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Write a function that implements the rindex function. 
//This function has two parameters. 
//The first parameter is a normal C string. 
//The second parameter is a single character. 
//If the character appears one or more times anywhere in the string, 
//then rindex returns a pointer to the last occurrence of that character in the string. 
//If the character does not appear in the string, rindex returns 0 (i.e., a null pointer). 
//Do NOT change the string.
char* rindex(char str[], char val) {
    if (str[0] == 0) return 0;

    if (str[0] == val) {
        char* s = rindex(str+1, val);
        if (s == 0) return str;
        else return s;
    }

    else return rindex(str+1, val);
}

//Consider the following game (usually played by two people using n marbles). 
//The game starts by placing all the marbles in a bowl and choosing a small integer k, 
//where k > 1 (e.g., k could be two, three or four). The players then take turns removing marbles from the bowl. 
//Each turn, a player may either remove 1 marble, or he may remove k marbles. 
//Note that it is not permitted to skip a turn or to remove zero marbles 
//(each turn, a player must remove either exactly 1 marble or exactly k marbles). 
//The players alternate turns until there are no marbles left in the bowl. 
//The player who removes the last marble loses the game. 
//Write a program that determines if, for any number of marbles left in the bowl, n, 
//and for a specific value of k, whether or not I can with certainty win the game (by playing perfectly). 
//Obviously, if there’s only one marble left in the bowl, I will lose. However, note that if
//there’s two marbles left, I can trivially win the game by removing one of them. 
//We say that when there is one marble left, the bowl is in a “losing” state. When there are two marbles, it’s in a “winning state”. 
//Clearly if there are k+1 marbles, that is also a winning state 
//(since I could remove k marbles in my turn and force my opponent to remove the last marble). 
//Write your function to return true if the bowl is in a winning state, and to return false otherwise. 
//You must assume that both players play perfectly.
bool marb(int n, int k) {
    if (n <= 0) return true; //if n <= 0 then this would mean that my opponent attempted to grab an amount equal to or
                             //more than what's left after I try--either I'd win or he'd never attempt that, so this returns true
    if (n == 1) return false; 
    if (n == 2) return true; 
    if (n == k+1) return true; 

    if (n <= k) return marb(n-2, k); 

    else return (marb(n-2, k) && marb(n-1-k, k)) || (marb(n-k-k, k) && marb(n-k-1, k)); 
}

//Node struct for BST
struct Node {    
    int value;    
    Node* left;   
    Node* right;    
    Node* parent; 
}; 

//In binary search trees, we’re often worried about the height, 
//which is defined as the number of nodes on the longest path from the root to any leaf. 
//Write a function to find the “shortness” of a tree, 
//which we’ll define as the number of nodes along the shortest path from the root to any null child pointer in the tree. 
//Note that the shortest path may not necessarily end in a leaf. 
//For example, if the root of the tree had no left child (all of the nodes in the tree were in the right subtree of the root), 
//then the shortness would be equal to 1, since there is just one node along the path from the root to the first null pointer – 
//the root node is the only node along the path to the first null pointer since root->left is null in this example.
int shortness(Node* root) {
    if (root == 0) return 0;
    int leftShortness = 1 + shortness(root->left);
    int rightShortness = 1 + shortness(root->right);

    if (leftShortness > rightShortness) return rightShortness;
    else return leftShortness;
}

//A function that makes it so that left subtree is larger than root and right subtree is smaller than root, i.e. invert the BST
void invertTree(Node* root) {
    if (root == 0) return;
    if (root->left == 0 && root->right == 0) return;

    else {
        invertTree(root->left);
        invertTree(root->right);
        Node* n = root->right;
        root->right = root->left;
        root->left = n;
    }
}

//This checks if x is a linear combination of a and b
bool isLinear(int x, int a, int b) {
    if (x == 0) return true;
    if (x < 0) return false;
    else {
        bool usingA = isLinear(x-a, a, b);
        bool usingB = isLinear(x-b, a, b);
        bool usingAB = isLinear(x-a-b, a, b);
        return usingA||usingB||usingAB;
    }
}

//This checks if s1 is a substring of s2 (common letters must be consecutive in s2)
//Uses a helpful boolean flag parameter that is "triggered" when it seems a substring is found
bool substr (char* s1, char* s2, bool flag) {
    if (s1[0] == '\0') 
    	return true;
    if (s1[0] == s2[0]) { 
        flag = true;
        return substr(s1+1, s2+1, flag);
    }
    else {
        if (flag == false) 
        	return substr(s1, s2+1, flag);
        else 
        	return false;
    }
}

//Using recursion with no loops and no global variables, 
//write a function that returns 1 if x is divisible by an integer greater than or equal to 2 and less than or equal to k. 
//Return zero otherwise. Recall that “is divisible by” means the remainder is zero. 
//Note that, assuming you’ve written your program correctly, for any x > 1, isDivis(x, x-1) will return 0 if and only if x is prime.

// return 1 if x is divisible by some integer ≥ 2 and ≤ k, return 0 otherwise
int isDivis(int x, int k) {
    if (k < 2) return false;
    else if(x % k == 0) return true;
    else return isDivis(x, k-1);
}

//This checks if seq is a subsequence of str (common letters in seq must be in order in str, but not necessarily consecutive)
bool subseq (char* seq, char* str) {
    if (seq[0] == '\0') return true;
    else if (str[0] == '\0') return false; 

    else if (seq[0] == str[0]) return subseq(seq+1, str+1); 
    else return subseq(seq, str+1); 
}

int exponent(int base, uint32_t n) {
    if (n == 0) return 1;
    else return (int) (base * exponent(base, n-1));
}

int numOfDigits(int n) {
    if (n == 0) return 0;
    else return 1 + numOfDigits(n/10);
}

int main(void){
	printf("testing isLinear\n");
    bool if8 = isLinear(8, 3, 5);
    bool if9 = isLinear(9, 3, 5);
    bool if10 = isLinear(10, 3, 5);
    bool if7 = isLinear(7, 3, 5);
    bool if57 = isLinear(57, 15, 4);
    bool if58 = isLinear(58, 15, 4);
    printf("1: %d, 1: %d, 1: %d, 0: %d, 1: %d, 0: 0\n", if8, if9, if10, if7, if57, if58);

	printf("testing substr\n");
    char* s1 = "abc";
    char* s2 = "xabcx";
    printf("1: %d\n", substr(s1, s2, false));
    s2 = "axbxc";
    printf("0: %d\n", substr(s1, s2, false));

    s1 = "batman";
    s2 = "the dark knight, batman, is here";
    printf("1: %d\n", substr(s1, s2, false));
    s2 = "the dark knight, bat man, is here";
    printf("0: %d\n", substr(s1, s2, false));
    s1 = "b";
    printf("1: %d\n", substr(s1, s2, false));

	printf("testing isDivis\n");
    printf("1: %d\n0: %d\n1: %d\n0: %d\n0: %d\n0: %d\n1: %d\n1: %d\n0: %d\n", 
    	isDivis(9,8), isDivis(17,16), isDivis(57,56), isDivis(59,58), isDivis(101,100), 
    	isDivis(97,96), isDivis(98, 96), isDivis(25,5), isDivis(25,4));

	printf("testing subseq()\n");
    char* seq = "abc";
    char* str1 = "I know my abc's";
    printf("1: %d\n", subseq(seq, str1));
    str1 = "Strawberry cream pie";
    printf("1: %d\n", subseq(seq, str1));
    str1 = "apple crumb pie";
    printf("0: %d\n", subseq(seq, str1));

	printf("testing the rindex function\n");
    char x[] = {'A', 'y', 'y', 'o', '\0'};
    char* str2 = rindex(x, 'y');
    //returned pointer should point to the second y
    printf("%c %c %c\n", *str2, *(str2-1), *(str2+1));
    char* y = "abcdeghijklmnopqrstuwxyz";
    str2 = rindex(y, 'f');
    if (str2 == nullptr) 
    	printf("yesh\n");
    else 
    	printf("smh\n");
}
