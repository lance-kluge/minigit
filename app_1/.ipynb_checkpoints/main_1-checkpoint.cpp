#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

using namespace std;

void readValue(string path)
{
    std::ifstream r1(path);
    if (r1.is_open())
        std::cout << r1.rdbuf();
    r1.close();
}
/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init" << endl;
    cout << " 2. add" << endl;
    cout << " 3. rm" << endl;
    cout << " 4. commit" << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit" << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        freopen(argv[1], "r", stdin);
    }
    bool inited = false;

    MiniGit *git;
    while (true)
    {
        displayMenu();
        string opt;
        getline(cin >> ws, opt);
        //allows for comments in test file
        if (opt.at(0) == '/')
            continue;
        while ((!isdigit(opt.at(0)) && opt!= "-99") || (stoi(opt) != -99 && (stoi(opt) <= 0 || stoi(opt) >= 8)))
        {
            cout << "Please enter a valid option: ";
            getline(cin >> ws, opt);
        }
        int option = stoi(opt);
        if (!inited && 2 <= option && option < 7)
        {
            cout << "You must init before you can do that." << endl;
            continue;
        }
        if (option == -99)
        {
            cout << "This menu is for debugging only" << endl;
            cin >> option;
            if (option == 0)
            { //create/modify a file
                string filename;
                getline(cin >> ws, filename);
                string msg;
                getline(cin >> ws, msg);

                ofstream MyFile(filename);
                MyFile << msg << endl;
                MyFile.close();
            }
            else if (option == 2)
            { //delete a file
                string fileToDelete;
                getline(cin >> ws, fileToDelete);
                fs::remove(fileToDelete);
            }
            else if (option == 3)
            { //print contents of file
                string fileName;
                getline(cin >> ws, fileName);

                readValue(fileName);
            }
        }
        else if (option == 1)
        { //init
            git = new MiniGit();
            git->init(5);
            inited = true;
        }
        else if (option == 2)
        { //add
            if (git->actionLock)
            {
                cout << "Cannot perform this action while on an old commit" << endl;
                continue;
            }
            cout << "File to add: ";
            string filePath;
            getline(cin >> ws, filePath);

            while (!fs::exists(filePath))
            {
                cout << "Enter a valid path: ";
                getline(cin >> ws, filePath);
            }
            if (git->addListContains(filePath))
                continue;

            git->add(filePath);
        }
        else if (option == 3)
        {
            if (git->actionLock)
            {
                cout << "Cannot perform this action while on an old commit" << endl;
                continue;
            } //rm
            cout << "File to remove: ";
            string fileName;
            getline(cin >> ws, fileName);
            if (git->addListContains(fileName))
                git->rm(fileName);
        }
        else if (option == 4)
        {
            if (git->actionLock)
            {
                cout << "Cannot perform this action while on an old commit" << endl;
                continue;
            } //commit
            if (!git->haveAnyFilesChanged())
            {
                cout << "No added files have been modified." << endl;
                continue;
            }
            string message;
            cout << "Enter a commit message: ";
            getline(cin >> ws, message);
            while (!git->commitMessageValid(message))
            {
                cout << "Please enter valid commit message: ";
                getline(cin >> ws, message);
            }

            cout << "Your message is: " << message << endl;
            git->commit(message);
        }
        else if (option == 5)
        {
            //checkout
            if(git->getNumCommits()==0) {
                cout << "Cannot checkout when there are no commits" << endl;
                continue;
            }
            cout << "Enter a commit number: ";
            int commitNumber;
            cin >> commitNumber;
            while (commitNumber >= git->getNumCommits() || commitNumber < 0)
            {
                cout << "Enter a valid commit number: ";
                cin >> commitNumber;
            }
            cout << "This will overwrite existing files. Enter \"Yes\" if you want to continue." << endl;
            string confirmation;
            cout << "#> ";
            cin >> confirmation;
            if (confirmation != "Yes")
            {
                cout << "You entered: \"" << confirmation << "\"" << endl;
                cout << "Cancelling checkout" << endl;
                continue;
            }
            BranchNode *commit = git->getCommitFromID(commitNumber);
            if (commit == nullptr)
            {
                cout << "commit not found" << endl;
                continue;
            }
            cout << "Checking Out: " << commit->commitID << endl;
            git->checkout(commit->commitID);
        }
        else if (option == 6)
        {
            cout << "Word to search: ";
            string word;
            cin >> word;
            git->search(word);
        }
        else if (option == 7)
        { //quit
            cout << "Quitting" << endl;
            delete git;
            return 0;
        }
    }

    return 0;
}