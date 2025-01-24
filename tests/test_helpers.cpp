#include <gtest/gtest.h>
#include "test_helpers.hpp"

#include "../code_1/hash.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
//        cout << buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_insert(string arr[], int len, int tabSize)
{

    testing::internal::CaptureStdout();
    HashTable* ht = new HashTable(tabSize);

    for(int i=0;i<len;i++)
    {
        ht->insertItem(arr[i],i);
    }

    ht->printTable();
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_MiniGit_Add(string files[], int len) {
    MiniGit *g = new MiniGit;
    testing::internal::CaptureStdout();
    g->init(5);
    for(int i = 0; i < len; i++) {
        g->add(files[i]);
        if(!g->addListContains(files[i])) {
            cout << "Says that file was not added for file :" << files[i] << endl;
            break;
        } else {
            cout << "Succesfully added file :" << files[i] << endl;
        }
    }



    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_MiniGit_RM(string files[], int len, string rmFiles[], int rmLen) {
    MiniGit *g = new MiniGit;
    testing::internal::CaptureStdout();
    g->init(5);
    for(int i = 0; i < len; i++) {
        g->add(files[i]);
        if(!g->addListContains(files[i])) {
            cout << "Says that file was not added for file :" << files[i] << endl;
            break;
        } else {
            cout << "Succesfully added file :" << files[i] << endl;
        }
    }
    for(int j = 0; j< rmLen; j++) {
        g->rm(rmFiles[j]);
        if(g->addListContains(rmFiles[j])) {
            cout << "Still says that file exists for :" << rmFiles[j] << endl;
            break;
        } else {
            cout << "Succesfully removed file :" << rmFiles[j] << endl;
        }
    }
    for(int i = 0; i < len; i++) {
        g->add(files[i]);
        if(!g->addListContains(files[i])) {
            cout << "Says that file was not added for file :" << files[i] << endl;
            break;
        } else {
            cout << "Succesfully added file :" << files[i] << endl;
        }
    }


    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_MiniGit_GetSourcePath(string files[], int versions[], int len){
    testing::internal::CaptureStdout();
    MiniGit *g = new MiniGit;

    for(int i = 0; i< len; i++){
        string path = getSourcePath(files[i], versions[i]);
        cout << path <<endl;
    }
    string output = testing::internal::GetCapturedStdout();
    return output;
}



void setValue(MiniGit *g, string path, string val, string msg){
    ofstream w1(path);
    w1 << val << endl;
    g->add(path);
    g->commit(msg);


}
void readValue(string path){
    std::ifstream r1(path);
    if (r1.is_open())
        std::cout << r1.rdbuf();
    r1.close();
}

string test_MiniGit_CHECKOUT(){

    testing::internal::CaptureStdout();
    MiniGit *g = new MiniGit;
    g->init(5);

    string path = "f.txt";
    setValue(g, path, "test", "bruh");
    readValue(path);


    setValue(g, path, "super epic file msg", "commit two");
    readValue(path);

    setValue(g, path, "final commit", "eff");
    readValue(path);

    g->checkout(1);
    readValue(path);

    cout << "Action Lock: " << g->actionLock << endl;
//    g->commit("this should fail");

    g->checkout(2);
    g->commit("this should succeed");
    readValue(path);


    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_MiniGit_SEARCH(){

    testing::internal::CaptureStdout();
    MiniGit *g = new MiniGit;
    g->init(5);

    string path = "f.txt";
    setValue(g, path, "test", "bruh");


    setValue(g, path, "super epic commit", "commit two");

    setValue(g, path, "final commit", "commit three");

    g->search("commit");
    g->search("bruh");
    g->search("two");
    g->search("hippo");


    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_MiniGit_isFileChanged(string file1, string file2) {
    MiniGit *g = new MiniGit;
    testing::internal::CaptureStdout();
    g->init(5);
    if(g->isFileChanged(file1, file2)) {
        cout << "File " << file1 << " is changed/different from file :" << file2 << endl;
    } else {
        cout << "File " << file1 << " is not changed/different from file :" << file2 << endl;
    }
    string output = testing::internal::GetCapturedStdout();
    return output;
}

string test_MiniGit_Commit(string file1, string commitName) {
    MiniGit *g = new MiniGit;
    testing::internal::CaptureStdout();
    g->init(5);
    g->add(file1);
    cout << "number of commits is now: " << to_string(g->getNumCommits()) << endl;
    g->commit(commitName);
    cout << "number of commits is now: " << to_string(g->getNumCommits()) << endl;
    cout << "commit message is : '" <<g->getCommitFromID(0)->commitMessage << "' and should be '" << commitName << "'" << endl; 
    ifstream file;
    string sourcePath = getSourcePath(file1, 0);
    file.open(sourcePath);
    if (file){
        cout << "correct file exists in miniGit" << endl;
        if(g->isFileChanged(file1, sourcePath)) {
            cout << "incorrect copy function of the file" << endl;
        } else {
            cout << "correctly copied the contents of the file" << endl;
        }
    } else {
        cout << "File does not exist" << endl;
    }
    if (!g->haveAnyFilesChanged()) {
        cout << "Correctly identified that no files have changed" << endl;
    } else {
        cout << "Incorrectly indentified that files have changed" << endl;
    }
    //check now if the correct version of the file exists in minigit
    //try and modify
    //then check commit again
    // then check again that correct and new version is in minigit while preserving the older file
    file.close();
    string output = testing::internal::GetCapturedStdout();
    return output;
}


string test_MiniGit_CommitExtended(string file1, string commitName, string file2) {
    MiniGit *g = new MiniGit;
    testing::internal::CaptureStdout();
    g->init(5);
    g->add(file1);
    cout << "number of commits is now: " << to_string(g->getNumCommits()) << endl;
    g->commit(commitName);
    cout << "number of commits is now: " << to_string(g->getNumCommits()) << endl;
    cout << "commit message is : '" <<g->getCommitFromID(0)->commitMessage << "' and should be '" << commitName << "'" << endl; 
    ifstream file;
    string sourcePath = getSourcePath(file1, 0);
    file.open(sourcePath);
    if (file){
        cout << "correct file1 exists in miniGit" << endl;
        if(g->isFileChanged(file1, sourcePath) || g->isFileChanged(file2, sourcePath)) {
            cout << "incorrect copy function of the file1" << endl;
        } else {
            cout << "correctly copied the contents of the file1" << endl;
        }
    } else {
        cout << "File does not exist" << endl;
        file.close();
        string output = testing::internal::GetCapturedStdout();
        return output;
    }

    ofstream fileOut;
    fileOut.open(file1);
    g->add(file2);
    fileOut << "testing the add and comparison" << endl;
    fileOut.close();
    cout << "number of commits is now: " << to_string(g->getNumCommits()) << endl;
    g->commit(commitName + " v2");
    cout << "number of commits is now: " << to_string(g->getNumCommits()) << endl;
    cout << "commit message is : '" <<g->getCommitFromID(1)->commitMessage << "' and should be '" << commitName << " v2'" << endl; 

    if(!g->isFileChanged(sourcePath, file2)) {
        cout << "Correctly did not overwrite the previous file1 version" << endl;
    } else {
        cout << "incorrectly wrote to override the previous version of file1" << endl;
    }
    ifstream file2Reader;
    file2Reader.open(getSourcePath(file2, 0));
    if(file2Reader) {
        cout << "correct file2 exists in miniGit" << endl;
        if(g->isFileChanged(file2, getSourcePath(file2, 0))) {
            cout << "incorrect copy function of the file2" << endl;
        } else {
            cout << "correctly copied the contents of the file2" << endl;
        }
    } else {
        cout << "File does not exist" << endl;
        file.close();
        file2Reader.close();
        string output = testing::internal::GetCapturedStdout();
        return output;
    }

    ifstream file1ReaderV2;
    file1ReaderV2.open(getSourcePath(file1, 1));

     if(file1ReaderV2) {
        cout << "correct file1 version 1 exists in miniGit" << endl;
        if(g->isFileChanged(file2, getSourcePath(file2, 0))) {
            cout << "incorrect copy function of the file1 for version 1" << endl;
        } else {
            cout << "correctly copied the contents of the file1 for version 1" << endl;
        }
    } 

    file2Reader.close();
    file.close();
    string output = testing::internal::GetCapturedStdout();
    return output;
}