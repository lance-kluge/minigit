// If you change anything in this file, your changes will be ignored
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
//#include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test
{
protected:
    // This function runs only once before any TEST_F function
    static void SetUpTestCase()
    {
        std::ofstream outgrade("./total_grade.txt");
        if (outgrade.is_open())
        {
            outgrade.clear();
            outgrade << (int)0;
            outgrade.close();
        }
    }

    // This function runs after all TEST_F functions have been executed
    static void TearDownTestCase()
    {
        std::ofstream outgrade("./total_grade.txt");
        if (outgrade.is_open())
        {
            outgrade.clear();
            outgrade << (int)std::ceil(100 * total_grade / max_grade);
            outgrade.close();
            std::cout << "Total Grade is : " << (int)std::ceil(100 * total_grade / max_grade) << std::endl;
        }
    }

    void add_points_to_grade(double points)
    {
        if (!::testing::Test::HasFailure())
        {
            total_grade += points;
        }
    }

    // this function runs before every TEST_F function
    void SetUp() override {}

    // this function runs after every TEST_F function
    void TearDown() override
    {
        std::ofstream outgrade("./total_grade.txt");
        if (outgrade.is_open())
        {
            outgrade.clear();
            outgrade << (int)std::ceil(100 * total_grade / max_grade);
            outgrade.close();
        }
    }

    static double total_grade;
    static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;

/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////
TEST_F(test_x, TestInsert)
{

    string result;
    string expected;

    int len = 5;

    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;

    result = test_insert(commits, len, tabSize);

    expected = "0|| science(1,4,)\n1|| \n2|| \n3|| \n4|| difficult(3,)-->fun(2,)-->computer(0,)\n";

    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

    string commits2[] = {"computer", "science", "fun", "difficult", "science", "computer", "science", "fun", "difficult", "science"};
    len = 10;
    result = test_insert(commits2, len, tabSize);
    expected = "0|| science(1,4,6,9,)\n1|| \n2|| \n3|| \n4|| difficult(3,8,)-->fun(2,7,)-->computer(0,5,)\n";

    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}

TEST_F(test_x, TestMiniGit_ADD)
{
    string result;
    string expected;

    ofstream MyFile("f1.txt");
    MyFile << "test" << endl;
    string files[] = {"f1.txt"};
    result = test_MiniGit_Add(files, 1);
    expected = "Succesfully added file :f1.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

    ofstream MyFile2("f2.txt");
    MyFile2 << "test2" << endl;
    string files2[] = {"f1.txt", "f2.txt"};
    result = test_MiniGit_Add(files2, 2);
    expected = "Succesfully added file :f1.txt\nSuccesfully added file :f2.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(3);

    MyFile.close();
    MyFile2.close();
    remove("f2.txt");
    remove("f1.txt");
}

//TestMiniGit_ADD
TEST_F(test_x, TestMiniGit_GETSOURCEPATH)
{ //test source path
    string result;
    string expected;

    int len = 5;
    string files[] = {"f1.txt", "f4.txt", "edward.txt", "billy bob.txt", "dir/file.mov"};
    int versions[] = {0, 4, 2, 999, 3};
    result = test_MiniGit_GetSourcePath(files, versions, len);
    expected = ".minigit/f1.txt_0\n.minigit/f4.txt_4\n.minigit/edward.txt_2\n.minigit/billy bob.txt_999\n.minigit/dir/file.mov_3\n";
    ASSERT_EQ(expected, result);
}

TEST_F(test_x, TestMiniGit_RM)
{
    string result;
    string expected;

    ofstream MyFile("f1.txt");
    MyFile << "test" << endl;
    string files[] = {"f1.txt"};
    result = test_MiniGit_RM(files, 1, files, 1);
    expected = "Succesfully added file :f1.txt\nSuccesfully removed file :f1.txt\nSuccesfully added file :f1.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

    ofstream MyFile2("f2.txt");
    MyFile2 << "test" << endl;
    string files2[] = {"f1.txt", "f2.txt"};
    result = test_MiniGit_RM(files2, 2, files2, 2);
    expected = "Succesfully added file :f1.txt\nSuccesfully added file :f2.txt\nSuccesfully removed file :f1.txt\nSuccesfully removed file :f2.txt\nSuccesfully added file :f1.txt\nSuccesfully added file :f2.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

    MyFile.close();
    remove("f1.txt");
}

TEST_F(test_x, TestMiniGit_isFileChanged)
{
    string result;
    string expected;

    ofstream MyFile("f1.txt");
    MyFile << "test" << endl;
    result = test_MiniGit_isFileChanged("f1.txt", "f1.txt");
    expected = "File f1.txt is not changed/different from file :f1.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

    ofstream MyFile2("f2.txt");
    MyFile2 << "test2" << endl;
    result = test_MiniGit_isFileChanged("f1.txt", "f2.txt");
    expected = "File f1.txt is changed/different from file :f2.txt\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);

    MyFile.close();
    MyFile2.close();
    remove("f2.txt");
    remove("f1.txt");
}

TEST_F(test_x, TestMiniGit_Commit)
{
    string result;
    string expected;

    ofstream MyFile("f1.txt");
    MyFile << "test" << endl;
    result = test_MiniGit_Commit("f1.txt", "commit one");
    expected = "number of commits is now: 0\nnumber of commits is now: 1\ncommit message is : 'commit one' and should be 'commit one'\ncorrect file exists in miniGit\ncorrectly copied the contents of the file\nCorrectly identified that no files have changed\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);

    ofstream MyFile2("f2.txt");
    MyFile2 << "test" << endl;
    result = test_MiniGit_CommitExtended("f1.txt", "commit one", "f2.txt");
    expected = "number of commits is now: 0\nnumber of commits is now: 1\ncommit message is : 'commit one' and should be 'commit one'\ncorrect file1 exists in miniGit\ncorrectly copied the contents of the file1\nnumber of commits is now: 1\nnumber of commits is now: 2\ncommit message is : 'commit one v2' and should be 'commit one v2'\nCorrectly did not overwrite the previous file1 version\ncorrect file2 exists in miniGit\ncorrectly copied the contents of the file2\ncorrect file1 version 1 exists in miniGit\ncorrectly copied the contents of the file1 for version 1\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);

    MyFile2.close();
    MyFile.close();
    remove("f2.txt");
    remove("f1.txt");
}
TEST_F(test_x, TestMiniGit_SEARCH)
{
    string result;
    string expected;

    result = test_MiniGit_SEARCH();
    expected = "All commit numbers that contain \"commit\":\n1, 2\nAll commit numbers that contain \"bruh\":\n0\nAll commit numbers that contain \"two\":\n1\nNo commits contain \"hippo\"\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}
TEST_F(test_x, TestMiniGit_CHECKOUT)
{
    string result;
    string expected;

    result = test_MiniGit_CHECKOUT();
    expected = "test\nsuper epic file msg\nfinal commit\nsuper epic file msg\nAction Lock: 1\nfinal commit\n";
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
}
TEST_F(test_x, TestMain)
{
    string desired = readFileIntoString("../tests/main_test/output1.txt");
    string resp = exec("./run_app_1 ../tests/main_test/input1.txt");
    ASSERT_EQ(desired, resp);
    add_points_to_grade(30);
}
