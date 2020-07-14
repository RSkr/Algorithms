#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

using namespace std;

struct heapNode{
    /// A value of character
    int sign = 0;

    /// Frquency of that character in the text
    int frequency = 0;

    /// Children of the node
    struct heapNode *left = NULL, *right = NULL;
};


/// Reading text to code and saving it to string
string readInputFileToCode(){
    ifstream ifs("text.txt");
    string textFromFile((istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>()));
    return textFromFile;
}

/// Reading text to decode and saving it to string
string readInputFileToDecode(){
    ifstream ifs("code.txt");
    string textCodeFromFile((istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>()));
    return textCodeFromFile;
}


int countSizeOfHeap(const int& differentLetters){
    int levelsOfTree = ceil(log2(differentLetters)) + 1;
    return (1 << levelsOfTree);
}

/// Creating heap
void createHeap(const int& size){
    vector<heapNode> heap(size);
}

int countDiffLettersAndFillPriorityQue(priority_queue<int>& allLetters, const string& textFromFile){
    int differentLetters = 0;
    vector<bool> letterExist (128, false);
    for(int i = 0; i < textFromFile.size(); i++) {
        int letter = textFromFile[i];
        if(!letterExist[letter]){
            letterExist[letter] = true;
            differentLetters++;
        }
        allLetters.push(letter);
    }
    return differentLetters;
}

/// Huffman algorith to code text file
void huffmanCoding(){
    /// Reading file
    string textFromFile = readInputFileToCode();

    /// Priority queue for sorting by most frequency
    priority_queue<int> allLetters;
    /// Getting number of different charaters to create Heap later on
    int differentLetters = countDiffLettersAndFillPriorityQue(allLetters, textFromFile);


    /*cout <<  differentLetters << endl;
    while(!allLetters.empty()){
        cout << allLetters.top() << ' ';
        allLetters.pop();
    }*/


}


void testcase(){
    huffmanCoding();
}


int main() {
    testcase();
    return 0;

}
