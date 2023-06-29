
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

class text_editor
{
    std::string name;

public:
    void create();
    void open();
    void insert_text();
    void delete_text();
    void move_cursor();
    void display();
    void search();
    void search_replace();
    void save();
};

void text_editor::create()
{
    std::cout << "Enter file name: " << std::endl;
    std::cin >> name;
    name = name + ".txt";
    std::fstream file;
    file.open(name, std::ios::out);
    if (!file)
    {
        std::cout << "Error in creating file";
        return;
    }
    else
    {
        std::cout << "Successfully created " << name << std::endl;
    }
    file.close();
}

void text_editor::open()
{
    std::string name;
    std::cout << "Enter the name of the file to open: ";
    std::cin >> name;

    std::ifstream inputFile(name);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << name << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }

    inputFile.close();
}
void text_editor::insert_text()
{
    std::string name;
    std::cout << "Enter the name of the file to insert text: ";
    std::cin >> name;

    std::ofstream outputFile(name, std::ios::app);

    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << name << std::endl;
        return;
    }

    std::string text;
    std::cout << "Enter text to insert: ";
    std::cin.ignore(); // Ignore the newline character from previous input
    std::getline(std::cin, text);

    outputFile << text << std::endl;

    outputFile.close();

    std::cout << "Text inserted successfully." << std::endl;
}
void text_editor::delete_text()
{

    std::string fn;
    std::cout << "Enter file name: ";
    std::cin >> fn;
    std::ifstream inputFile(fn);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << fn << std::endl;
        return;
    }

    std::string line;
    std::cout << "Enter line to delete";
    std::cin >> line;
    while (std::getline(inputFile, line))
    {
        // std::cout << line << std::endl;
        int curpos = line.length();
        for (int i = 0; i < curpos; i++)
        {
            std::cout << "\b \b";
        }
    }

    inputFile.close();
}
void text_editor::move_cursor()
{
    std::string name;
    std::cout << "Enter the name of the file to open: ";
    std::cin >> name;

    std::fstream fs(name);

    if (!fs.is_open())
    {
        std::cerr << "Failed to open the file: " << name << std::endl;
        return;
    }

    else
    {
        int opt;
        int pos;
        char c;

        std::cout << "1 : read" << std::endl;
        std::cout << "2 : write" << std::endl;

        /* int count = 0;
         char ch;
        while (fs.get(ch)) {
            count++;
        }


   std::cout << "The file contains " << count << " characters." << std::endl;*/

        std::cout << "Enter option:" << std::endl;
        std::cin >> opt;
        if (opt == 1)
        {

            std::cout << "Enter position: ";
            std::cin >> pos;
            fs.seekg(pos, std::ios::cur);
            while (!fs.eof())
            {
                fs.get(c);
                std::cout << c;
            }
            std::cout << "" << std::endl;
        }

        else if (opt == 2)
        {
            std::string text;
            std::cout << "Enter position: ";
            std::cin >> pos;
            fs.seekp(pos, std::ios::beg);
            std::cout << "Enter text to insert: ";
            std::cin >> text;
            fs << text;
        }

        else
        {
            std::cout << "Invalid" << std::endl;
        }
    }
    fs.close();
}

void text_editor::display()
{
    std::string name;
    std::cout << "Enter the name of the file to display: ";
    std::cin >> name;

    std::ifstream inputFile(name);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << name << std::endl;
        return;
    }
    char ch;

    while (!inputFile.eof())
    {
        inputFile.get(ch);
        std::cout << ch;
    }

    inputFile.close();
    std::cout << "" << std::endl;
}
void text_editor::save() //call open function before this to ensure correct name is taken
{
    std::ofstream outputFile(name);//Current File Name is read
    if(!outputFile)
    {
        std::cerr<<"Error in opening File :"<<std::endl;
        return;
    }
    std::string text;
    while (std::getline(std::cin, text))
    {
        if (text == ":wq")  // Exit condition, use ":wq" to save and exit
        {
            break;
        }
        outputFile << text << std::endl;      
    }
    outputFile.close();
    std::cout << "File saved successfully." << std::endl;
    
}
void text_editor::search()
{
    std::string name;
    std::cout << "Enter the name of the file to be searched: ";
    std::cin >> name;

    std::ifstream open_file(name);

    if (!open_file.is_open())
    {
        std::cerr << "Failed to open the file: " << name << std::endl;
        return;
    }
    char text[100];
    char target[10];
    int count = 0;
    std::cout << "Enter word to be searched: " << std::endl;
    std::cin >> target;

    std::vector<int> positions;
    std::vector<int> line_number;
    std::string line;
    int lineNumber = 1;

    while (std::getline(open_file, line)) // one line of open_file stored in 'line' in each iteration
    {
        std::istringstream iss(line);
        std::string word;
        int wordPosition = 1;

        while (iss >> word) // one word of line is stored in 'word' in each iteration
        {
            if (word == target)
            {
                count++;
                positions.push_back(wordPosition);
                line_number.push_back(lineNumber);
            }
            wordPosition++;
        }

        lineNumber++;
    }

    open_file.close();

    if (count == 0)
    {
        std::cout << "Word not found" << std::endl;
    }
    else
    {
        std::cout << "Number of occurrences: " << count << std::endl;
        int n = positions.size();
        for (int i = 0; i < n; i++)
        {
            std::cout << "Line " << line_number[i] << ", Position " << positions[i] << std::endl;
        }

        std::cout << std::endl;
    }
}

void text_editor::search_replace()
{
    std::string name;
    std::cout << "Enter file name in which you want to replace: " << std::endl;
    std::cin >> name;

    std::ifstream inputFile(name);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file: " << name << std::endl;
        return;
    }

    std::string old_word;
    std::string new_word;
    std::cout << "Enter the word to be replaced: " << std::endl;
    std::cin >> old_word;

    std::string temp;
    int count = 0;
    while (inputFile >> temp)
    {
        if (temp == old_word)
        {
            count++;
        }
    }

    if (count == 0)
    {
        std::cout << "Word to be replaced cannot be found" << std::endl;
        return;
    }

    else
    {
        std::cout << "Enter the new word : " << std::endl;
        std::cin >> new_word;
        std::ifstream inputFile(name);
        /*std::string Contents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());*/
        inputFile.open(name.c_str(), std::ios::in | std::ios::out | std::ios::binary);
        // The c_str() function in C++ converts a string to an array of characters and terminates this array with a null character at the end

        std::stringstream text;

        text << inputFile.rdbuf();
        std::string Contents = text.str(); // the content of file is present in text.str()

        inputFile.close();

        size_t pos = 0;
        while ((pos = Contents.find(old_word, pos)) != std::string::npos)
        {
            Contents.replace(pos, old_word.length(), new_word);
            pos += new_word.length();
        }

        std::ofstream outputFile(name);
        outputFile << Contents;
        outputFile.close();

        std::cout << "Word replaced successfully in the file." << std::endl;
    }
}

void menu()
{
    std::cout << "1: Create a File" << std::endl;
    std::cout << "2: Open a File" << std::endl;
    std::cout << "3: Insert text to a File" << std::endl;
    std::cout << "4: Delete from a File" << std::endl;
    std::cout << "5: Move cursor " << std::endl;
    std::cout << "6: Display a File" << std::endl;
    std::cout << "7: Search " << std::endl;
    std::cout << "8: Search and replace" << std::endl;
    std::cout << "9: Save" << std::endl;
}
int main()
{
    text_editor t;
    menu();
    int choice;

    while (1)

    {
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            t.create();
            break;

        case 2:
            t.open();
            break;
            /* case 3:
                 t.insert_text();
                 break;*/
        case 4:
            t.delete_text();
            break;
        case 5:
            t.move_cursor();
            break;
        case 6:
            t.display();
            break;
        case 7:
            t.search();
            break;
        case 8:
            t.search_replace();
            break;
        /*case 9:
            t.save();
            break;*/
        case 0:
            exit(0);
        }
    }
}
