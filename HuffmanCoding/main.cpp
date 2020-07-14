#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

vector<string> codedValues(128);

class HuffmanCodeClass{
    struct node{
        char data;
        int freq;
        node* left;
        node* right;
        node(char data, int freq) : data(data), freq(freq), left(NULL), right(NULL){}
        ~node(){
            delete left;
            delete right;
        }
    };

    struct compare{
        bool operator()(node* l, node* r)
        {
            return (l->freq > r->freq);
        }
    };

    node* top;

    void print_Code(node* root, string str)    {
        if(root == NULL)
            return;

        if(root->data == '#'){
            print_Code(root->left, str + "0");
            print_Code(root->right, str + "1");
        }

        if(root->data != '#'){
            codedValues[root->data] = str;
            cout << root->data <<" : " << str << "\n";
            print_Code(root->left, str + "0");
            print_Code(root->right, str + "1");
        }
    }

public:
    HuffmanCodeClass() {};
    ~HuffmanCodeClass(){
        delete top;
    }
    void generateTree(vector<char>& data, vector<int>& freq, int size){
        node* left;
        node* right;
        priority_queue<node*, vector<node*>, compare > minHeap;

        for(int i = 0; i < size; ++i){
            minHeap.push(new node(data[i], freq[i]));
        }

        while(minHeap.size() != 1){
            right = minHeap.top();
            minHeap.pop();
            left = minHeap.top();
            minHeap.pop();

            top = new node('#', left->freq + right->freq);
            top->left  = left;
            top->right = right;
            minHeap.push(top);
        }
        print_Code(minHeap.top(), "");
    }

    string decode(string text){
        node* root = top;
        string decodedMsg = "";
        string codedChar = "";
        for(int i = 0; i < text.size(); i++){
            if(text[i] == '0'){
                root = root->left;
                codedChar += "0";
            }
            else{
                root = root-> right;
                codedChar += "1";
            }
            if(root-> data != '#') {
                decodedMsg += root->data;
                codedChar = "";
                root = top;
            }
        }
        return decodedMsg;
    }

};

string readInputFileToCode(){
    ifstream ifs("code.txt");
    string textFromFile((istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>()));
    return textFromFile;
}

string readInputFileToDecode(){
    ifstream ifs("decode.txt");
    string textFromFile((istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>()));
    return textFromFile;
}

int countDiffLettersAndFillPriorityQue(priority_queue<int>& allLetters, const string& textFromFile){
    int differentLetters = 0;
    vector<bool> letterExist (128, false);
    for(int i = 0; i < textFromFile.size(); i++) {
        char letter = textFromFile[i];
        if(!letterExist[letter]){
            letterExist[letter] = true;
            differentLetters++;
        }
        allLetters.push(letter);
    }
    return differentLetters;
}

void fillCharArrayAndFreqArray(vector<char>& characterArray, vector<int>& freqArray, priority_queue<int> allLetters){
    int currentChar = allLetters.top();
    characterArray[0] = currentChar;
    int index = 0;
    while(!allLetters.empty()){
        currentChar = allLetters.top();
        allLetters.pop();
        if(currentChar != characterArray[index]){
            index++;
            characterArray[index] = currentChar;
        }
        freqArray[index]++;
    }
    ofstream myfile;
    myfile.open ("tree.txt");
    myfile << characterArray.size() << endl;
    for(int i  = 0; i <= characterArray.size(); i++){
        if(characterArray[i] == '\n')
            myfile << freqArray['i'] << endl;
    }

    for(int i  = 0; i < characterArray.size(); i++){
        myfile << characterArray[i] << endl;
        myfile << freqArray[i] << endl;
    }
    myfile.close();

}


void HuffmanEncode(string& text){
    cout << "Encoded text: " << endl;
    string output = "";
    for(int i = 0; i < text.size(); i++){
        output += codedValues[text[i]];
    }
    cout << output << endl;
    ofstream myfile;
    myfile.open ("decode.txt");
    myfile << output;
    myfile.close();
}


void countEfficiency(const string& text, const vector<char>& charactersArray, const vector<int>& freqArray){
    cout << "Without coding: " <<  text.size() * 8 << endl;
    int couter = 0;
    for(int i = 0; i < charactersArray.size(); i++){
        couter += codedValues[charactersArray[i]].size() * freqArray[i];
    }
    cout << "With Huffman Coding: " << couter << endl;
}

void getTree(int& differentLetters, vector<char>& charactersArray, vector<int>& freqArray, vector<char>& data, vector<int>& freq ){
    int f;
    char ch;

    for (int i=0;i<differentLetters;i++)
    {
        cin>>ch;
        if(ch == '\n') cout << "test";
        data.insert(data.end(), ch);
        cin>>f;
        freq.insert(freq.end(), f);
    }
}

void HuffmanCoding(){
    char ch;
    int f;
    HuffmanCodeClass huffmanCode;
    vector<char> data;
    vector<int> freq;
    int differentLetters;
    priority_queue<int> allLetters;

    //CODING
    string textFromFile = readInputFileToCode();
    differentLetters = countDiffLettersAndFillPriorityQue(allLetters, textFromFile);
    vector<char> charactersArray (differentLetters);
    vector<int> freqArray(differentLetters, 0);
    fillCharArrayAndFreqArray(charactersArray, freqArray, allLetters);
    for (int i = 0;i < differentLetters; i++){
        ch = charactersArray[i];
        data.insert(data.end(), ch);
    }
    for (int i = 0;i < differentLetters;i++){
        f = freqArray[i];
        freq.insert(freq.end(), f);
    }

    huffmanCode.generateTree(data, freq, differentLetters);
    HuffmanEncode(textFromFile);

    ///DECODING

    /*cin >> differentLetters;
    vector<char> charactersArray (differentLetters);
    vector<int> freqArray(differentLetters, 0);

    getTree(differentLetters, charactersArray, freqArray, data, freq);
    huffmanCode.generateTree(data, freq, differentLetters);
    cout << "Decoded text: " << endl << huffmanCode.decode(readInputFileToDecode()) << endl;
*/
    //countEfficiency(textFromFile, charactersArray, freqArray);
}

int main()
{
    HuffmanCoding();
    return 0;
}