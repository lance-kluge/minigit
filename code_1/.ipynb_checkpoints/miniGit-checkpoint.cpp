#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
// #include <experimental/filesystem>
namespace fs = std::filesystem;
using namespace std;

#include "miniGit.hpp"
#include <vector>

MiniGit::MiniGit()
{
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
    actionLock = false;
    ht = NULL;
    commits = 0;
    commitHead = nullptr;
}

MiniGit::~MiniGit()
{
    // Any postprocessing that may be required
    delete ht;
    BranchNode *temp = commitHead;
    while (temp != nullptr)
    {
        FileNode *t = temp->fileHead;
        while (t != nullptr)
        {
            temp->fileHead = t->next;
            delete t;
            t = temp->fileHead;
        }
        commitHead = commitHead->previous;
        delete temp;
        temp = commitHead;
    }
    fs::remove_all(".miniGit");
}

void MiniGit::init(int hashtablesize)
{
    ht = new HashTable(hashtablesize);
    commits = 0;
    commitHead = new BranchNode;
    commitHead->commitID = 0;
    commitHead->commitMessage = "";
    commitHead->fileHead = nullptr;
    commitHead->next = nullptr;
    commitHead->previous = nullptr;
}

void MiniGit::add(string fileName)
{
    FileNode *t = commitHead->fileHead;
    while (t != nullptr)
    {
        if (t->name == fileName)
        {
            t->alive = true;
            return;
        }
        t = t->next;
    }

    FileNode *temp = new FileNode;
    temp->name = fileName;
    temp->alive = true;
    temp->version = 0;
    temp->next = commitHead->fileHead;

    commitHead->fileHead = temp;
}

void MiniGit::rm(string fileName)
{
    FileNode *temp = commitHead->fileHead;
    while (temp != nullptr)
    {
        if (temp->name == fileName)
        {
            temp->alive = false;
        }
        temp = temp->next;
    }
    //TODO: Delete files from commitHead
}

void MiniGit::printSearchTable()
{
    ht->printTable();
}

void MiniGit::search(string key)
{
    HashNode *temp = ht->searchItem(key);
    if (temp == nullptr)
    {
        cout << "No commits contain \"" << key << "\"" << endl;
        return;
    }
    cout << "All commit numbers that contain \"" << key << "\":" << endl;
    for (uint i = 0; i < temp->commitNums.size() - 1; i++)
    {
        cout << temp->commitNums.at(i) << ", ";
    }
    if (temp->commitNums.size() > 0)
    {
        cout << temp->commitNums.at(temp->commitNums.size() - 1) << endl;
    }
}

bool MiniGit::addListContains(string key)
{
    FileNode *n = commitHead->fileHead;
    while (n != nullptr)
    {
        if (n->name == key && n->alive)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

int MiniGit::commit(string msg)
{
    stringstream s(msg);
    string word;
    while (s >> word)
    {
        ht->insertItem(word, commitHead->commitID);
    }
    commitHead->commitMessage = msg;
    FileNode *temp = commitHead->fileHead;
    BranchNode *newBranchNode = new BranchNode;

    newBranchNode->fileHead = nullptr;
    newBranchNode->next = nullptr;
    newBranchNode->previous = nullptr;
    newBranchNode->commitID = -1;
    while (temp != nullptr)
    {
        if (temp->alive)
        {
            string writePath = getSourcePath(temp->name, temp->version);
            if (isFileChanged(temp->name, writePath))
            {
                temp->version++;
            }
            writePath = getSourcePath(temp->name, temp->version);
            if ((fs::status(writePath)).type() == fs::file_type::not_found)
            {
                copy_File(temp->name, temp->version);
            }
        }

        FileNode *t = new FileNode;
        t->next = newBranchNode->fileHead;
        newBranchNode->fileHead = t;
        t->name = temp->name;
        t->version = temp->version;
        t->alive = temp->alive;
        temp = temp->next;
    }
    commits++;
    newBranchNode->commitID = commits;
    newBranchNode->previous = commitHead;
    newBranchNode->next = nullptr;
    commitHead->next = newBranchNode;
    commitHead = newBranchNode;

    return commitHead->previous->commitID; //should return the commitID of the commited DLL node
}

void MiniGit::checkout(int commitID)
{
    BranchNode *commit = getCommitFromID(commitID);
    actionLock = commit != commitHead->previous;

    FileNode *scanner = commit->fileHead;
    while (scanner != nullptr)
    {
        if (!scanner->alive)
        {
            scanner = scanner->next;
            continue;
        }
        restoreFile(scanner->name, scanner->version);
        scanner = scanner->next;
    }
}
void MiniGit::restoreFile(string filename, int version)
{
    string sourcePath = getSourcePath(filename, version);

    ifstream source(sourcePath);

    ofstream out(filename, std::ofstream::trunc);

    string line;

    while (getline(source, line))
    {
        out << line << "\n";
    }

    // Closing file
    source.close();
    out.close();
}

void MiniGit::copy_File(string fileName, int version)
{
    ifstream source(fileName);

    string writePath = getSourcePath(fileName, version);
    ofstream out(writePath, std::ofstream::trunc);

    string line;

    while (getline(source, line))
    {
        out << line << "\n";
    }

    // Closing file
    source.close();
    out.close();
}

bool MiniGit::commitMessageValid(string msg)
{
    if (msg.empty())
    {
        return false;
    }
    BranchNode *temp = commitHead;
    while (temp != nullptr)
    {
        if (temp->commitMessage == msg)
        {
            return false;
        }
        temp = temp->previous;
    }
    return true;
}

int MiniGit::getNumCommits()
{
    return commits;
}

BranchNode *MiniGit::getCommitFromID(int id)
{
    BranchNode *search = commitHead;
    while (search != nullptr && search->commitID != id)
        search = search->previous;
    return search;
}

bool MiniGit::isFileChanged(std::string sourceFile, std::string currVersionFile)
{
    ifstream sourceFi(sourceFile);
    ifstream versionFile(currVersionFile);
    if (!versionFile)
    {
        return false;
    }
    string sourceFileLine;
    string versionFileLine;
    string temp;
    while (getline(sourceFi, temp))
    {
        sourceFileLine += temp;
    }
    while (getline(versionFile, temp))
    {
        versionFileLine += temp;
    }

    return (versionFileLine != sourceFileLine);
}

string getSourcePath(string filename, int version)
{
    return ".minigit/" + filename + "_" + to_string(version);
}

bool MiniGit::haveAnyFilesChanged()
{
    FileNode *temp = commitHead->fileHead;
    while (temp != nullptr)
    {
        if (!temp->alive)
        {
            temp = temp->next;
            continue;
        }
        ifstream file;
        file.open(getSourcePath(temp->name, 0));

        if (!file || isFileChanged(temp->name, getSourcePath(temp->name, temp->version)))
        {
            return true;
        }
        file.close();
        temp = temp->next;
    }
    return false;
}