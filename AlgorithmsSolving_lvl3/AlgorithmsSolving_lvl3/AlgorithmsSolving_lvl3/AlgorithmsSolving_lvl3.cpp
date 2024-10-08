//all algorithms code will be in word file

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream> 
using namespace std;

const string ClientsFileName = "Clients.txt";

enum enLetterType { All, Capital, Small };

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string name;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDelete = false;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From; //Function to generate a random number
}

int ReadNumber(string Massage)
{
    int num;
    cout << Massage << endl;
    cin >> num;

    return num;
}

int ReadDouble(string Massage)
{
    double num;
    cout << Massage << endl;
    cin >> num;

    return num;
}

string ReadString(string Massage)
{
    string s = "";
    cout << Massage << endl;
    getline(cin, s);
    return s;
}

char ReadChar()
{
    char c;
    cout << "Enter a Char: " << endl;
    cin >> c;
    return c;
}

void FillMatrixWithRandomNums(int Array2D[3][3], int rows, int cols) //no need to use ByRef (&)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Array2D[i][j] = RandomNumber(0, 10);
        }
    }
}

void Print2dArray(int Array2D[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf(" %0*d   ", 2, Array2D[i][j]);
            //cout << setw(3) << Array2D[i][j] << " ";
        }
        cout << endl;
    }
}

int MatrixRowSum(int Array2D[3][3], int RowNumberToSum, int cols)
{
    int sum = 0;
    for (int j = 0; j < cols; j++)
    {
        sum += Array2D[RowNumberToSum][j]; //Row is constent
    }
    return sum;
}

int MatrixColSum(int Array2D[3][3], int rows, int ColNumberToSum)
{
    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        sum += Array2D[i][ColNumberToSum];
    }
    return sum;
}

void FillArrayWithRowSum(int Array2D[3][3], int rows, int cols, int arrSum[3])
{
    for (int i = 0; i < rows; i++)
    {
        arrSum[i] = MatrixRowSum(Array2D, i, cols);
    }
}

void FillArrayWithColSum(int Array2D[3][3], int rows, int cols, int arrSum[3])
{
    for (int i = 0; i < cols; i++)
    {
        arrSum[i] = MatrixColSum(Array2D, rows, i);
    }
}

void PrintRowSum(int Array2D[3][3], int rows, int cols)
{
    cout << endl;
    for (int i = 0; i < cols; i++)
    {
        cout << "Row " << i + 1 << " Sum: " << MatrixRowSum(Array2D, i, cols) << endl;
    }
}

void PrintColSum(int Array2D[3][3], int rows, int cols)
{
    cout << endl;
    for(int j = 0; j < cols; j++)
    {
        cout << "Column " << j + 1 << " Sum: " << MatrixColSum(Array2D, rows, j) << endl;
    }
}

void PrintArray(int arr[3], int arrLength)
{
    cout << endl;
    for (int i = 0; i < arrLength; i++)
    {
        cout << "Col " << i + 1 << " Sum: " << arr[i] << endl;
    }
}

void FillMatrixWithOrderedNums(int Array2D[3][3], int rows, int cols)
{
    int counter = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Array2D[i][j] = counter;
            counter++;
        }

    }
}

void TransposeMatrix(int FilledArray2D[3][3], int TransposedArray[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
           TransposedArray[i][j] = FilledArray2D[j][i];
        }
    }
}

void MultiplyMatrix(int arr1[3][3], int arr2[3][3], int arr3Result[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr3Result[i][j] = arr1[i][j] * arr2[i][j];
        }
    }
}

void PrintMatrixMiddleRow(int arr[3][3], int rows, int cols)
{
    int MiddleRow = round((rows - 1) / 2);
    for (int j = 0; j < cols; j++)
    {
        printf(" %0*d   ", 2, arr[MiddleRow][j]);
    }
}

void PrintMatrixMiddleCol(int arr[3][3], int rows, int cols)
{
    int MiddleCol = round((cols - 1) / 2);
    for (int i = 0; i < rows; i++)
    {
        printf(" %0*d   ", 2, arr[i][MiddleCol]);
    }
}

int SumOfMatrixElements(int matrix[3][3], int rows, int cols)
{
    int sum = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum += matrix[i][j];
        }
    }

    return sum;
}

bool CheckMatricesEquality(int matrix1[3][3], int matrix2[3][3], int rows, int cols)
{
    return (SumOfMatrixElements(matrix1, rows, cols) == SumOfMatrixElements(matrix2, rows, cols));
}

bool CheckMatricesTypicality(int matrix1[3][3], int matrix2[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix1[i][j] != matrix2[i][j])
                return false;
        }
    }

    return true;
}

bool CheckIdentityMatrix(int matrix[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        if (matrix[i][i] != 1) //checks for the diagonal to equal 1 
            return false;
        else
        {
            for (int j = 0; j < cols; j++)
            { //check for the other elements that arent't in the diagonal to equal 0
                if (i != j && matrix[i][j] != 0 && matrix[i][j] != 1)
                    return false;
            }
        }
    }

    return true;
}

bool CheckScalarMatrix(int matrix[3][3], int rows, int cols)
{
    int FirstElementInDiagonal = matrix[0][0];

    for (int i = 0; i < rows; i++)
    {     
        for (int j = 0; j < cols; j++)  
        { 
            //check for diagonal elements to equal first element
            if (i == j && matrix[i][j] != FirstElementInDiagonal)
                return false;
            if (i != j && matrix[i][j] != 0)//check for the rest elements to equal zero
                return false;
        }
    }
    return true;
}

int CountNumberInMatrix(int matrix[3][3], int rows, int cols, int RequiredNumber)
{
    int RequiredNumberCounter = 0;
    for (int i = 0; i < rows; i++)
    {  
        for (int j = 0; j < cols; j++)   
        { 
            if (matrix[i][j] == RequiredNumber)
                RequiredNumberCounter++;
        }
    }
    return RequiredNumberCounter;
}

bool CheckSparseMatrix(int matrix[3][3], int rows, int cols)
{
    return (CountNumberInMatrix(matrix, rows, cols, 0) > (rows * cols) / 2);
}

bool CheckIfNumberInMatrix(int matrix[3][3], int rows, int cols, int RequiredNumber)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == RequiredNumber)
                return true;
        }
    }
    return false;
}

void PrintIntersectedNumbersInMatrices(int Matrix1[3][3], int Matrix2[3][3], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (CheckIfNumberInMatrix(Matrix1, rows, cols, Matrix2[i][j]))
                cout << Matrix2[i][j] << "   ";
        }
    }
}

int MaxNumberInMatrix(int matrix[3][3], int rows, int cols)
{
    int Max = matrix[0][0];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] >= Max)
                Max = matrix[i][j];
        }
    }

    return Max;
}

int MinNumberInMatrix(int matrix[3][3], int rows, int cols)
{
    int Min = matrix[0][0];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] <= Min)
                Min = matrix[i][j];
        }
    }

    return Min;
}

bool CheckPalindromeMatrix(int matrix[3][3], int rows, int cols)
{
    for (short i = 0; i < rows; i++) 
    { 
        for (short j = 0; j < cols / 2; j++)
        { 
            if (matrix[i][j] != matrix[i][cols - 1 - j]) //matrix[i][cols - 1 - j] is the last element in the Row
            { 
                return false; 
            }
        }
    }
    return true;
}

void PrintFebonacciSeries(int SeriesLength)
{
    cout << "Febonacci Series: \n";
    int Prev1 = 1, Prev2 = 0, NextNum = 0;

    for (int i = 0; i < SeriesLength; i++)
    {
        if (i <= 1)
            NextNum = i;
        else
        {
            NextNum = Prev1 + Prev2;
            Prev2 = Prev1;
            Prev1 = NextNum;
        }
        cout << NextNum << endl;
    }
}

void PrintFebonacciSeriesUsingRecursion(int SeriesLength,int Prev1, int Prev2)
{
    int NextNum = 0;
    
    if (SeriesLength > 0)
    {
    NextNum = Prev1 + Prev2;
    Prev2 = Prev1;
    Prev1 = NextNum;
    cout << NextNum << " ";
    
    PrintFebonacciSeriesUsingRecursion(SeriesLength - 1, Prev1, Prev2);//will keep looping until it became 0
    }
}

void PrintFirstLetterOfEachWord(string s)
{
    cout << "Fisrt Letters:\n";
    bool isFirstLetter = true;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ' && isFirstLetter)
            cout << s[i] << endl;

        isFirstLetter = (s[i] == ' ' ? true : false);
    }
}

void UpperFirstLetterOfEachWord(string& s)
{
    bool isFirstLetter = true;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ' && isFirstLetter)
        {
            s[i] = toupper(s[i]);
        }

        isFirstLetter = (s[i] == ' ' ? true : false);
    }

}

void LowerFirstLetterOfEachWord(string& s)
{
    bool isFirstLetter = true;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ' && isFirstLetter)
        {
            s[i] = tolower(s[i]);
        }

        isFirstLetter = (s[i] == ' ' ? true : false);
    }
}

string AllToUpper(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
            s[i] = toupper(s[i]);
    }
    return s;
}

string AllToLower(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

char ConvertCharacterCase(char c)
{
    return (islower(c) ? toupper(c) : tolower(c));
}

string InvertAllLettersCase(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = ConvertCharacterCase(s[i]);
    }
    return s;
}

int CountCapitalLetters(string s)
{
    int CapsCounter = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (isupper(s[i]))
            CapsCounter++;
    }
    return CapsCounter;
}

int CountSmallLetters(string s)
{
    int SmolCounter = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (islower(s[i]))
            SmolCounter++;
    }
    return SmolCounter;
}

int CountLetters(string s, enLetterType type = All)
{
    if (type == All)
        return s.length();
    else if (type == Capital)
        return CountCapitalLetters(s);
    else
        return CountSmallLetters(s);
}

int CountSpecificLetter(string s, char letter, bool MatchCase = true)
{
    int counter = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (MatchCase) {
            if (s[i] == letter)
                counter++;
        }
        else {
            if (s[i] == letter || s[i] == ConvertCharacterCase(letter))
                counter++;
        }
    }
    return counter;
}

bool isVowel(char c)
{
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'u' || c == 'o');
}

int CountVowelLetters(string s)
{
    int VowelCounter = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (isVowel(s[i]))
            VowelCounter++;
    }
    return VowelCounter;
}

void PrintVowelLetters(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isVowel(s[i]))
            cout << s[i] << "\t";
    }
}

void PrintEachWordInString(string s)
{
    cout << "\nString Words: \n";
    string word, delim = " "; //delimiter means space string --> " " 
    short position = 0; 

    while ( (position = s.find(delim)) != s.npos) //position of the first delimiter != s.npos
    {
        word = s.substr(0, position);
        if (word != "")
            cout << word << endl; //print the word from 0 to delimiter position

        s.erase(0, position + delim.length()); //erase the word we printed and the delimiter after it
    }

    if (s != "") //if the string is not empty yet, print the last word
        cout << s << endl;

}

int CountEachWordInString(string s)
{
    string word, delim = " "; //delimiter means space string --> " " 
    short position = 0, counter = 0;

    while ((position = s.find(delim)) != s.npos) //position of the first delimiter != s.npos
    {
        word = s.substr(0, position);
        if (word != "")
            counter++;

        s.erase(0, position + delim.length()); //erase the word we printed and the delimiter after it
    }

    return ++counter; //print the counter + 1 because there is still one word in the string 
}

vector <string> SplitString(string s, string separator)
{
    //separator is the same as delimeter

    vector <string> vStringWords;

    string word;
    short position = 0;

    while ((position = s.find(separator)) != s.npos)
    {
        word = s.substr(0, position);
        if (word != "") 
            vStringWords.push_back(word);

        s.erase(0, position + separator.length());
    }

    if (s != "")
        vStringWords.push_back(s);

    return vStringWords;
}

string TrimLeft(string s)
{
    char delim = ' ';
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != delim && s[0] == delim)
            s = s.substr(i, s.length() - 1);
    }
    return s;
}

string TrimRight(string s)
{
    char delim = ' ';
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s[i] != delim && s[s.length() - 1] == delim)
            s = s.substr(0, i + 1);
    }
    return s;
}

string Trim(string s)
{
    return TrimRight(TrimLeft(s));
}

string JoinString(vector <string> vStrings, string separator)
{
    string FullString = "";
    for (string& i : vStrings)
    {
        FullString = FullString + i + separator;
    }
    //return the string without the last separator 
    return FullString.substr(0, FullString.length() - separator.length()); 
}

string JoinString(string arrStrings[6], int arrLength, string separator)
{
    string FullString = "";
    for (int i = 0; i < arrLength; i++)
    {
        FullString = FullString + arrStrings[i] + separator;

    }

    //return the string without the last separator 
    return FullString.substr(0, FullString.length() - separator.length());
}

string ReverseString(string s)
{
    string ReversedString = "", separator = " ";
    vector <string> vString = SplitString(s, separator);
    vector <string>::iterator iter = vString.end();

    while (iter != vString.begin())
    {
        iter--;
        ReversedString = ReversedString + *iter + separator;
    }

    return ReversedString.substr(0,ReversedString.length() -  separator.length());
}

string ReplaceWordUsingBuiltInFunction(string s, string WordToReplace, string NewWord)
{
    int WordPosition = s.find(WordToReplace);

    if (WordPosition == s.npos)
        return "\nWord Not Found\n";

    while (WordPosition != s.npos)//use while to check for multiple words
    {
        s.replace(WordPosition, WordToReplace.length(), NewWord);// built-in funcation

        WordPosition = s.find(WordToReplace); //check if there is another word
    }

    return s;
}

string ReplaceWord(string s, string WordToReplace, string NewWord)
{
    int WordPosition = s.find(WordToReplace);

    if (WordPosition == s.npos)
        return "\nWord Not Found\n";

    while (WordPosition != s.npos)//use while to check for multiple words
    {
        s.erase(WordPosition, WordToReplace.length());
        s.insert(WordPosition, NewWord);

        WordPosition = s.find(WordToReplace); //check if there is another word
    }

    return s;
}

string ReplaceWordUsingSplit(string s, string WordToReplace, string NewWord, bool MatchCase = true)
{
    vector <string> vStringWords = SplitString(s, " ");

    s.clear(); //clear the string to refill it
    for (string& i : vStringWords)
    {
        if (MatchCase == true && i == WordToReplace)
            i = NewWord;
        
        if (MatchCase == false && AllToLower(i) == AllToLower(WordToReplace))
            i = NewWord;
    }

    return JoinString(vStringWords, " ");// refilling the string and return it
}

string RemovePunctuations(string s)
{
    string NewString = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (! ispunct(s[i]))
        {
            NewString = NewString + s[i];
        }
    }
    return NewString;
}

stClientData ReadClientData()
{
    stClientData data;

    // Usage of >>std::ws will extract all the whitespace character
    cout << "Enter Account Number: ";     
    getline(cin >> ws, data.AccountNumber);

    cout << "Enter PIN Code: ";     
    getline(cin, data.PinCode);

    cout << "Enter Name: ";     
    getline(cin, data.name);

    cout << "Enter Phone Number: ";     
    getline(cin, data.PhoneNumber);

    cout << "Enter Account Balance: ";     
    cin >> data.AccountBalance;

    return data;
}

string ConvertDataToLine(stClientData data, string separator = "#//#")
{
    string Record = "";

    Record += data.AccountNumber + separator;
    Record += data.PinCode + separator;
    Record += data.name + separator;
    Record += data.PhoneNumber+ separator;
    Record += to_string(data.AccountBalance);

    return Record;
}

stClientData ConvertLineToData(string Line, string separator = "#//#")
{
    stClientData data;
    vector <string> vClientData = SplitString(Line, separator);

    data.AccountNumber = vClientData[0];
    data.PinCode = vClientData[1];
    data.name = vClientData[2];
    data.PhoneNumber = vClientData[3];
    data.AccountBalance = stod(vClientData[4]); //cast string to double

    return data;
}

void PrintClientDataStruct(stClientData data)
{
    cout << "\n\n**************Client Record**************" << endl;
    cout << "Account Number : " << data.AccountNumber << endl;
    cout << "PIN Code       : " << data.PinCode << endl;
    cout << "Name           : " << data.name << endl;
    cout << "Phone Number   : " << data.PhoneNumber << endl;
    cout << "Account Balance: " << data.AccountBalance << endl;
}

void AddClientToFile(string FileName, string RecordLine)
{
    fstream MyFile;
    
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << RecordLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    stClientData ClientData = ReadClientData();

    string RecordLine = ConvertDataToLine(ClientData);

    AddClientToFile(ClientsFileName, RecordLine);
}

void AddClients()
{
    char AddMore = 'Y';

    do
    {
        system("cls");
        cout << "Adding New Client ...\n\n";

        AddNewClient();

        cout << "Client Added Successfully. ";
        cout << "Do You Want To Add More Clients? 'Y' / 'N' :\n";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

vector <stClientData> LoadClientDataFromFileToVector(string FileName)
{
    vector <stClientData> vClientsData;
    fstream Client;
    
    Client.open(ClientsFileName, ios::in);

    if (Client.is_open())
    {
        string line;
        
        while (getline(Client, line))
        {
            vClientsData.push_back(ConvertLineToData(line));
        }
        Client.close();
    }
    return vClientsData;
}

void PrintClientRecord(stClientData data)
{
    cout << "| " << left << setw(14) << data.AccountNumber;
    cout << "| " << left << setw(9) << data.PinCode;
    cout << "| " << left << setw(39) << data.name;
    cout << "| " << left << setw(11) << data.PhoneNumber;
    cout << "| " << left << setw(11) << data.AccountBalance;
    cout << "| ";
}

void PrintAllClientsData(vector <stClientData> vClientsData)
{
    cout << "\t\t\t\t\tClient List: (" << vClientsData.size() << ") Cient(s).\n";
    cout << "|---------------|----------|----------------------------------------|------------|------------|\n";

    cout << "| " << left << setw(13) << "Account Number";
    cout << "| " << left << setw(9) << "PIN Code";
    cout << "| " << left << setw(39) << "Client Name";
    cout << "| " << left << setw(11) << "Phone";
    cout << "| " << left << setw(11) << "Balance";
    cout << "| \n";

    cout << "|---------------|----------|----------------------------------------|------------|------------|\n";

    for (stClientData data : vClientsData)
    {
        PrintClientRecord(data);
        cout << endl;
    }
    cout << "|---------------|----------|----------------------------------------|------------|------------|\n";
}

string ReadClientAccountNumber()
{
    string AccNum;
    cout << "Enter Account Number: \n";
    cin >> AccNum;
    return AccNum;
}

bool FindClientUsingAccountNum(string AccountNumber, stClientData& ClientData)//ByRef
{
    vector <stClientData> vClientData = LoadClientDataFromFileToVector(ClientsFileName);

    for (stClientData c : vClientData)
    {
        if (c.AccountNumber == AccountNumber)
        {
            ClientData = c;
            return true;
        }
    }
    return false;
}

bool FindClientUsingAccountNum(string AccountNumber, stClientData& Client,vector <stClientData> vClient)//ByRef
{
    for (stClientData c : vClient)
    {
        if (c.AccountNumber == AccountNumber)
        {
            Client = c;
            return true;
        }
    }
    return false;
}

void PrintClientCard(stClientData Client)
{
    cout << "\nThe following are the client details:\n";  
    cout << "\nAccout Number  : " << Client.AccountNumber;    
    cout << "\nPin Code       : " << Client.PinCode;     
    cout << "\nName           : " << Client.name;
    cout << "\nPhone          : " << Client.PhoneNumber;  
    cout << "\nAccount Balance: " << Client.AccountBalance; 
}

void MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{
    for (stClientData& c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
            c.MarkForDelete = true; 
    }
}

void SaveClientDataToFile(string fileName, vector <stClientData> vClients)
{
    fstream Client;

    Client.open(fileName, ios::out); //overwrite

    if (Client.is_open())
    {
        for(stClientData c: vClients)
        {
            // now we send the vector data to the file while skipping the MarkForDelete data
            if (c.MarkForDelete == false)
                Client << ConvertDataToLine(c) << endl;
        }
        Client.close();
    }

}

bool ConfirmDelete(string massage)
{
    char ConfirmDelete = 'n';
    cout << endl << massage << endl;
    cin >> ConfirmDelete;
    
    return(tolower(ConfirmDelete) == 'y' ? true : false);
}

bool Confirm_Y_N(string massage) // generic function to confirm Yes/No Questions
{
    char Confirm = 'n';
    cout << endl << massage << endl;
    cin >> Confirm;
    
    return(tolower(Confirm) == 'y' ? true : false);
}

void DeleteClientRecordByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{
    stClientData Clients;

    //the below function will fill the Client Struct because it is ByRef, Also, it will return true if client account number is found
    if (FindClientUsingAccountNum(AccountNumber, Clients, vClients))
    {
        PrintClientCard(Clients);

        //Delete Confirmation Generic Function (my idea)
        if (ConfirmDelete("Are You Sure You Want to Delete This Client?"))
        {
            //this will mark the client with the enterd account num
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);//vector is updated cause func is ByRef

            SaveClientDataToFile(ClientsFileName, vClients);//update the file

            //here we update the vector again to remove the clients that is marked for delete (from file)
            vClients = LoadClientDataFromFileToVector(ClientsFileName);

            cout << "\nClient Deleted Successfully.\n";
        }

    }
    else
        cout << "\nClient Number [" << AccountNumber << "] Not Found!\n";
}

stClientData ChangeClientRecord(string AccountNumber)
{
    stClientData Clients;

    Clients.AccountNumber = AccountNumber;

    cout << "\nEnter PIN Code: ";
    getline(cin >> ws, Clients.PinCode);

    cout << "Enter Name: ";
    getline(cin, Clients.name);

    cout << "Enter Phone Number: ";
    getline(cin, Clients.PhoneNumber);

    cout << "Enter Account Balance: ";
    cin >> Clients.AccountBalance;

    return Clients;
}

void UpdateClientRecordByAccountNumber(string AccountNumber, vector <stClientData>& vClients)
{
    stClientData Clients;

    //the below function will fill the Client Struct because it is ByRef, Also, it will return true if client account number is found
    if (FindClientUsingAccountNum(AccountNumber, Clients, vClients))
    {
        PrintClientCard(Clients);
        if (Confirm_Y_N("Are You Sure You Want To Update This Client?"))
        {
            // Usage of >>std::ws will extract all the whitespace character

            for (stClientData& c : vClients)
            {
                if (c.AccountNumber == AccountNumber)
                {
                    c = ChangeClientRecord(AccountNumber);
                    break; //quit the for loop cuase no need to continue after we updated the client
                }
            }
            
            SaveClientDataToFile(ClientsFileName, vClients);

            cout << "\nClient Updated Successfully.\n";
        }

    }
    else
        cout << "\nClient Number [" << AccountNumber << "] Not Found!\n";
}

int main()
{
    srand((unsigned)time(NULL)); 
    //Add the File Data to a Vector
    vector <stClientData> vClients = LoadClientDataFromFileToVector(ClientsFileName);

    UpdateClientRecordByAccountNumber("b14", vClients);
    cout << endl << endl;
     return 0;
}
