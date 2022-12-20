#include <iostream>

using namespace std;

/*
 * Print array
 */
void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }

    cout << endl;
}

/*
 * Permutate array based on permutation
 */
void permutate(int *arr, int perm[], int size){
    int temp[size];
    for(int i = 0; i < size; i++){
        temp[i] = arr[perm[i]-1];
    }

    for(int i = 0; i < size; i++){
        arr[i] = temp[i];
    }
}

/*
 * Expand array based on permutation
 */
void expandPerm(int input[], int *output, int perm[], int size){
    for(int i = 0; i < size; i++){
        output[i] = input[perm[i]-1];
    }
}

/*
 * Split array into left and right
 */
void split(int arr[], int size, int *left, int *right){
    int j = 0;
    for(int i = 0; i < size; i++){
        if(i < size / 2){
            left[i] = arr[i];
        }else{
            right[j] = arr[i];
            j++;
        }
    }
}

/*
 * Combine left and right into single array
 */
void combine(int left[], int right[], int *arr, int size){
    int j = 0;
    for(int i = 0; i < size; i++){
        if(i < size / 2) {
            arr[i] = left[i];
        }else {
            arr[i] = right[j];
            j++;
        }
    }
}

/*
 * Shift array to the left based on shift amount
 */
void leftShift(int *arr, int shift, int size){
    int temp[size];

    int j = 0;
    for(int i = shift; i < size; i++){
        temp[j] = arr[i];
        j++;
    }

    for(int i = 0; i < shift; i++){
        temp[j] = arr[i];
        j++;
    }

    for(int i = 0; i < size; i++){
        arr[i] = temp[i];
    }
}

/*
 * XOR 2 arrays
 */
void XOR(int input[],int *output,int size) {
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[i] = input[i] ^ output[i];
    }

    for (int i = 0; i < size; i++) {
        output[i] = temp[i];
    }
}

/*
 * SBox function
 */
void sBox(int l[], int r[], int *s0s1){
    int s0Sub [4][4]={
            {1,0,3,2},
            {3,2,1,0},
            {0,2,1,3},
            {3,1,3,2}
    };

    int s1Sub [4][4]={
            {0,1,2,3},
            {2,0,1,3},
            {3,0,1,0},
            {2,1,0,3}
    };

    int s0row = (l[0] * 2) + l[3];
    int s0col = (l[1] * 2) + l[2];

    int s0num = s0Sub[s0row][s0col];

    s0s1[1] = s0num % 2;
    s0num = s0num / 2;
    s0s1[0] = s0num % 2;

    int s1row = (r[0] * 2) + r[3];
    int s1col = (r[1] * 2) + r[2];

    int s1num = s1Sub[s1row][s1col];

    s0s1[3] = s1num % 2;
    s1num = s1num / 2;
    s0s1[2] = s1num % 2;
}

/*
 * Fk function
 */
void functionF(int *key, int *l, int *r){
    int expand[8] = {4,1,2,3,2,3,4,1};
    int P4[4] = {2,4,3,1};
    int expanded_r[8] = {};
    int left[4] = {};
    int right[4] = {};
    int s0s1[4] = {};

    cout << "   Expand right: ";
    expandPerm(r, expanded_r, expand, 8);
    printArray(expanded_r, 8);
    cout << endl;

    cout << "   XOR on right with key: ";
    XOR(key, expanded_r, 8);
    printArray(expanded_r, 8);
    cout << endl;

    cout << "   Split: " << endl;
    split(expanded_r, 8, left, right);
    cout << "       Left: ";
    printArray(left, 4);
    cout << "       Right: ";
    printArray(right, 4);
    cout << endl;

    cout << "   S-Box: ";
    sBox(left, right, s0s1);
    printArray(s0s1, 4);
    cout << endl;

    cout << "   P4 permutation: ";
    permutate(s0s1, P4, 4);
    printArray(s0s1, 4);
    cout << endl;

    cout << "   XOR on left with P4 permutation: ";
    XOR(s0s1, l, 4);
    printArray(l, 4);
    cout << endl;
}

/*
 * Swap 2 arrays
 */
void swap(int *l, int *r, int size){
    int temp[size];
    for(int i = 0; i < size; i++){
        temp[i] = l[i];
    }

    for(int i = 0; i < size; i++){
        l[i] = r[i];
    }

    for(int i = 0; i < size; i++){
        r[i] = temp[i];
    }
}

/*
 * Key generation function
 */
void keyGen(int master[], int *k1, int *k2) {
    int p10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
    int left[5] = {};
    int right[5] = {};


    cout << "P10 permutation: ";
    permutate(master, p10, 10);
    printArray(master, 10);
    cout << endl;

    split(master, 10, left, right);
    cout << "Split: " << endl;
    cout << "   Left:";
    printArray(left, 5);
    cout << "   Right:";
    printArray(right, 5);
    cout << endl;

    leftShift(left, 1, 5);
    cout << "Shift-1: " << endl;
    cout << "   Left:";
    printArray(left, 5);

    leftShift(right, 1, 5);
    cout << "   Right:";
    printArray(right, 5);
    cout << endl;

    combine(left, right, master, 10);
    cout << "Merge for K1: ";
    printArray(master, 10);
    cout << endl;

    permutate(master, p8, 8);
    cout << "P8 permutation for K1: ";
    printArray(master, 10);
    cout << endl;

    for(int i = 0; i < 8; i++){
        k1[i] = master[i];
    }

    leftShift(left, 2, 5);
    cout << "Shift-2: " << endl;
    cout << "   Left:";
    printArray(left, 5);

    leftShift(right, 2 ,5);
    cout << "   Right:";
    printArray(right, 5);
    cout << endl;

    combine(left, right, master, 10);
    cout << "Merge for K2: ";
    printArray(master, 10);
    cout << endl;

    permutate(master, p8, 8);
    cout << "P8 permutation for K2: ";
    printArray(master, 10);
    cout << endl;

    for(int i = 0; i < 8; i++){
        k2[i] = master[i];
    }
}

/*
 * Encrypt input and return the result to fk
 */
void encrypt(int input[], int key1[], int key2[], int *fk){
    int IP[8] = {2,6,3,1,4,8,5,7};
    int inverseIP[8] = {4,1,3,5,7,2,8,6};
    int left[4] = {};
    int right[4] = {};

    cout << "P8 permutation: ";
    permutate(input, IP, 8);
    printArray(input, 8);
    cout << endl;

    cout << "Split: " << endl;
    split(input, 8, left, right);
    cout << "   Left:";
    printArray(left, 4);
    cout << "   Right:";
    printArray(right, 4);
    cout << endl;

    cout << "Fk function with key 1: " << endl;
    functionF(key1, left, right);

    cout<<"After Swap"<<endl;
    swap(left, right, 4);
    cout<<"l = ";
    printArray(left,4);
    cout<<"r = " ;
    printArray(right,4);
    cout<<endl;

    cout << "Fk function with key 2: " << endl;
    functionF(key2, left, right);

    cout << "Merge left and right: ";
    combine(left, right, fk, 8);
    printArray(fk, 8);
    cout << endl;

    cout << "Inverse Permutation: ";
    permutate(fk, inverseIP, 8);
    printArray(fk, 8);
    cout << endl;
}

/*
 * Decrypt input and return the result
 */
void decrypt(int arr[], int key1[], int key2[], int *fk){
    int IP[8] = {2,6,3,1,4,8,5,7};
    int inverseIP[8] = {4,1,3,5,7,2,8,6};
    int left[4] = {};
    int right[4] = {};

    cout << "P8 permutation: ";
    permutate(arr, IP, 8);
    printArray(arr, 8);
    cout << endl;

    cout << "Split: " << endl;
    split(arr, 8, left, right);
    cout << "   Left:";
    printArray(left, 4);
    cout << "   Right:";
    printArray(right, 4);
    cout << endl;

    cout << "Fk function with key 2: " << endl;
    functionF(key2, left, right);

    swap(left, right, 4);
    cout<<"After Swap"<<endl;
    cout<<"l = ";
    printArray(left,4);
    cout<<"r = " ;
    printArray(right,4);
    cout<<endl;

    cout << "Fk function with key 1: " << endl;
    functionF(key1, left, right);

    cout << "Merge left and right: ";
    combine(left, right, fk, 8);
    printArray(fk, 8);
    cout << endl;

    cout << "Inverse Permutation: ";
    permutate(fk, inverseIP, 8);
    printArray(fk, 8);
    cout << endl;
}

int main() {
    int inputKey[10] = {};
    int plaintext[8] = {};
    int cipher[8] = {};
    int k1[8] = {};
    int k2[8] = {};
    int fk[8] = {};

    cout<<"Enter 10-bit Key"<<endl;
    for(int i = 0; i < 10; i++){
        cin >> inputKey[i];
    }

    cout << endl << "Generating keys:" << endl << endl;
    keyGen(inputKey, k1, k2);

    cout << "Key 1: ";
    printArray(k1, 8);

    cout << "Key 2: ";
    printArray(k2, 8);
    cout << endl;

    cout << "1) Encryption" << endl;
    cout << "2) Decryption" << endl;
    cout << "3) Both" << endl << endl;

    while(true){
        int option;
        cout << "Pick option:" << endl;
        cin >> option;

        switch(option){
            case 1: { //Encryption
                cout << endl << "Enter 8 bit plaintext:" << endl;
                for(int i = 0; i < 8; i++){
                    cin >> plaintext[i];
                }

                cout << endl << "Encryption:" << endl;
                encrypt(plaintext, k1, k2, cipher);

                cout << "Encrypted Cipher: ";
                printArray(cipher, 8);

                return 0;
            }
            case 2: { //Decryption
                cout << endl  << "Enter 8 bit plaintext:" << endl;
                for(int i = 0; i < 8; i++){
                    cin >> cipher[i];
                }

                cout << "Decryption:" << endl;
                decrypt(cipher, k1, k2, fk);

                cout << "Decrypted plaintext: ";
                printArray(fk, 8);

                return 0;
            }
            case 3: { //Both encryption and decryption
                cout << endl  << "Enter 8 bit plaintext:" << endl;
                for(int i = 0; i < 8; i++){
                    cin >> plaintext[i];
                }

                cout << "Encryption:" << endl;
                encrypt(plaintext, k1, k2, cipher);

                cout << "Encrypted Cipher: ";
                printArray(cipher, 8);

                cout << "--------------------------" << endl;

                cout << "Decryption:" << endl;
                decrypt(cipher, k1, k2, fk);

                cout << "Decrypted plaintext: ";
                printArray(fk, 8);

                return 0;
            }
            default: {
                cout << "Please pick a valid option" << endl;
            }
        }
    }
}