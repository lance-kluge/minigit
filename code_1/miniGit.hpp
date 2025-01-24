#pragma once

#include <iostream>
#include <vector>
#include "hash.hpp"
// #include <filesystem>

using namespace std;

enum GITOP
{
    init,
    add,
    rm,
    commit,
    checkout,
    status
};

struct FileNode
{
    string name;
    int version;
    FileNode *next;
    bool alive;
};

struct BranchNode
{
    int commitID;
    string commitMessage;
    BranchNode *next;
    BranchNode *previous;
    FileNode *fileHead;
};

//*** You can add helper functions if you desire ***//
class MiniGit
{
private:
    BranchNode *commitHead;
    int commits;
    HashTable *ht;

public:
    bool actionLock;

    MiniGit();
    ~MiniGit();

    void init(int hashtablesize);
    void add(string fileName);
    void rm(string fileName);
    void search(string key);
    int commit(string msg);
    void checkout(int commitID);
    void printSearchTable();
    bool addListContains(string key);
    void restoreFile(string fileName, int version);
    void copy_File(string fileName, int version);
    bool commitMessageValid(string msg);
    int getNumCommits();
    bool isFileChanged(string sourceFile, string currVersionFile);
    BranchNode *getCommitFromID(int id);
    bool haveAnyFilesChanged();
};

string getSourcePath(string filename, int version);