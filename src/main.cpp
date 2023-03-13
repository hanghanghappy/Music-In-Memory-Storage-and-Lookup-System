// Music In-Memory Storage and Lookup System
// Main - Menus and Functions
// Created by: Chun Hang Chan

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include "BinarySearchTree.h"  // BST ADT
#include "Track.h"
#include "HashTable.cpp"

using namespace std;

void createFileFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void inputFileFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void displayFunction(const BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void insertFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void searchFunction(const BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void deleteFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void build(const string& filename, BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void primarysearchManager(HashTable<TrackHash>& table);
void secondarysearchManager(const BinarySearchTree<Track>& tree);
void writetoFile(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
void savetoFile(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table);
int getPrime(int i);
bool isPrime(int i);
void hDisplay(Track&);
void vDisplay(Track&);
void iDisplay(Track&, int);

int main()
{
    BinarySearchTree<Track> tree;
    HashTable<TrackHash> table;
    string mainprompt = "\nMain Menu : Enter an option(H - for help)\n";
    // Allow people to generate from file or exit the program
    cout << "==========================================================\n";
    cout << "   Welcome to Music In-Memory Storage and Lookup System   \n";
    cout << "==========================================================\n";
    cout << "1. Create a File\n";
    cout << "2. Generate from File\n";
    cout << "3. Exit\n";
    cout << "==========================================================\n";
    string option;
    string filename;
    bool valid = false;
    while (valid == false)
    {
        cin >> option;
        if (option == "1")
        {
            valid = true;
            createFileFunction(tree, table);
        }
        else if (option == "2")
        {
            valid = true;
            inputFileFunction(tree, table);
        }
        else if (option == "3")
        {
            valid = true;
            exit(0);
        }
        else
            cout << "Please try again! Make sure that you only enter 1 or 2\n";
    }
    option = "";
    // Main Menu Display and let users choose the options
    cout << "==============Main Menu==============\n";
    cout << "1. Display\n";
    cout << "2. Search\n";
    cout << "3. Insert\n";
    cout << "4. Delete\n";
    cout << "5. Write to File\n";
    cout << "6. Exit\n";
    cout << "=====================================\n";
    while (option != "6")
    {
        cin >> option;
        if (option == "1")
        {
            displayFunction(tree, table);
            cout << mainprompt;
        }
        else if (option == "2")
        {
            searchFunction(tree, table);
            cout << mainprompt;
        }
        else if (option == "3")
        {
            insertFunction(tree, table);
            cout << mainprompt;
        }
        else if (option == "4")
        {
            deleteFunction(tree, table);
            cout << mainprompt;
        }
        else if (option == "5")
        {
            writetoFile(tree, table);
            cout << mainprompt;
        }
        else if (option == "6")
        {
            savetoFile(tree, table);
            exit(0);
        }
        else if (option == "H")
        {
            cout << "==============Main Menu==============\n";
            cout << "1. Display\n";
            cout << "2. Search\n";
            cout << "3. Insert\n";
            cout << "4. Delete\n";
            cout << "5. Write to File\n";
            cout << "6. Exit\n";
            cout << "=====================================\n";
        }
        else
        {
            cout << "Please try again!\n";
            cout << mainprompt;
        }
    }
    return 0;
}

/*
createFileFunction: ask for the desired file's name and create and intialize the file before calling the build function
*/
void createFileFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string filename;
    cout << "\nWhat do you want the file's name to be? ";
    cin >> filename;
    ofstream output(filename);
    output << "1234567891234567891234 Default; You can delete this later; Default; 100 100";
    output.close();
    build(filename, tree, table);
}

/*
inputFileFunction: ask for the file's name and call the build function
*/
void inputFileFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string filename;
    cout << "\nWhat is the input file's name? ";
    cin >> filename;
    build(filename, tree, table);
}

/*
build: build the binary search tree and hash table with the data in the file
*/
void build(const string& filename, BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    ifstream fin(filename);
    ifstream linereader(filename);
    int numberoflines = 0;
    int size = 0;
    string line;
    //cout << "Reading data from \"" << filename << "\"";

    if (!fin)
    {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }
    while (getline(linereader, line))
    {
        numberoflines++;
    }
    size = getPrime(numberoflines);
    table.setHashSize(size);
    string id, name, artist, album;
    int length, plays;

    while (fin >> id)
    {
        fin.ignore(); // to ignore space in front of name
        getline(fin, name, ';');
        fin.ignore();
        getline(fin, artist, ';');
        fin.ignore();
        getline(fin, album, ';');
        fin >> length;
        fin >> plays;
        // create a Track object and TrackHash object and initialize it with data
        // Track is sorted by name(secondary key) for Binary Search Tree
        // TrackHash is sorted by id(primary key) for Hash Table
        Track aTrack(id, name, artist, album, length, plays);
        TrackHash aTrack2(id, name, artist, album, length, plays);
        tree.insert(aTrack);
        table.insert(aTrack2, id);
    }
    fin.close();
}

/*
displayFunction: call the display menu and allow users to choose the options
*/
void displayFunction(const BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string displayprompt = "\nDisplay Menu: Enter an option(H - for help)\n";
    //5 is the hidden option to display the indented tree
    cout << "==============Display Menu==============\n";
    cout << "1. Display Inorder\n";
    cout << "2. Hash Table Display\n";
    cout << "3. Hash Table Statistics\n";
    cout << "4. Go back to main menu\n";
    cout << "========================================\n";
    string option = "";
    while (option != "4")
    {
        cin >> option;
        if (option == "1")
        {
            cout << endl << "Inorder: " << endl;
            cout << left;
            cout << "================================================="
                 << "================================================="
                 << "=================================================\n";
            cout << " " << setw(25) << "Track ID" << "  ";
            cout << " " << setw(22) << "Name" << "  ";
            cout << " " << setw(22) << "Artist" << " ";
            cout << " " << setw(15) << "Album" << "  ";
            cout << " " << setw(30) << "Music Length (in seconds)" << "  ";
            cout << " " << setw(20) << "Number of Plays" << "  ";
            cout << endl;
            cout << "================================================="
                << "================================================="
                << "=================================================\n";
            tree.inOrder(hDisplay);
            cout << "================================================="
                << "================================================="
                << "=================================================\n";
            cout << displayprompt;
        }
        else if (option == "2")
        {
            cout << "Hash Table: \n";
            table.traverseAll();
            cout << displayprompt;
        }
        else if (option == "3")
        {
            table.statistic();
            cout << displayprompt;
        }
        else if (option == "4")
        {
            return;
        }
        else if (option == "5")
        {
            cout << "Indented Tree: " << endl;
            tree.printTree(iDisplay);
            cout << endl;
            cout << displayprompt;
        }
        else if (option == "H")
        {
            cout << "==============Display Menu==============\n";
            cout << "1. Display Inorder\n";
            cout << "2. Hash Table Display\n";
            cout << "3. Hash Table Statistics\n";
            cout << "4. Go back to main menu\n";
            cout << "========================================\n";
        }
        else
        {
            cout << "Please try again!\n";
            cout << displayprompt;
        }

    }
}

/*
searchFunction: call the search menu and allow users to choose the options
*/
void searchFunction(const BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string option = "";
    string searchprompt = "\nSearch Menu : Enter an option(H - for help)\n";
    cout << "==============Search Menu==============\n";
    cout << "1. Search by ID\n";
    cout << "2. Search by Name\n";
    cout << "3. Go back to main menu\n";
    cout << "=======================================\n";
    while (option != "3")
    {
        cin >> option;
        if (option == "1")
        {
            primarysearchManager(table);
            cout << searchprompt;
        }
        else if (option == "2")
        {
            secondarysearchManager(tree);
            cout << searchprompt;
        }
        else if (option == "3")
        {
            return;
        }
        else if (option == "H")
        {
            cout << "==============Search Menu==============\n";
            cout << "1. Search by ID\n";
            cout << "2. Search by Name\n";
            cout << "3. Go back to main menu\n";
            cout << "=======================================\n";
        }
        else
        {
            cout << "Please try again!\n";
            cout << searchprompt;
        }
    }
}

/*
primarysearchManager: search the tree with the id until the user enters Q to quit searching
*/
void primarysearchManager(HashTable<TrackHash>& table)
{
    string targetID = "";
    TrackHash aTrack;

    cout << "=================\n";
    cout << "ID Search Manager\n";
    cout << "=================\n";

    cin.ignore();
    while (toupper(targetID[0]) != 'Q')
    {
        cout << "\nEnter a track id (or Q to stop searching) : \n";
        getline(cin, targetID);
        aTrack.setId(targetID);

        if (toupper(targetID[0]) != 'Q')
        {
            if (table.search(aTrack, aTrack.getId()))
            {
                cout << endl;
                vDisplay(aTrack);
            }
            else
                cout << "Track \"" << targetID << "\" was not found in this list." << endl;
        }
    }
    cout << "======END SEARCH SECTION======\n";
}

/*
secondarysearchManager: search the tree with the name and show all the matches until the user enters Q to quit searching
*/
void secondarysearchManager(const BinarySearchTree<Track>& tree)
{
    string targetName = "";
    Track aTrack;

    cout << "===================\n";
    cout << "Name Search Manager\n";
    cout << "===================\n";

    cin.ignore();
    while (toupper(targetName[0]) != 'Q')
    {
        cout << "\nEnter a track name (or Q to stop searching) : \n";
        getline(cin, targetName);
        Track temp;
        BinarySearchTree<Track> templist = tree;
        temp.setName(targetName);
        bool found = false;

        if (toupper(targetName[0]) != 'Q')
        {
            for (int i = 0; i < tree.getCount(); i++)
            {
                if (templist.search(temp, aTrack))
                {
                    found = templist.remove(aTrack);
                    cout << endl;
                    vDisplay(aTrack);
                    cout << endl;
                    found = true;
                }
            }
            if (found == false)
                cout << "Track \"" << targetName << "\" was not found in this list." << endl;
        }
    }
    cout << "======END SEARCH SECTION======\n";
}

/*
insertFunction: call the insert menu and allow users to choose the options
*/
void insertFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string option = "";
    string insertprompt = "\nInsert Menu : Enter an option(H - for help)\n";
    cout << "==============Insert Menu==============\n";
    cout << "1. Insert\n";
    cout << "2. Go back to main menu\n";
    cout << "=======================================\n";
    while (option != "2")
    {
        cin >> option;
        if (option == "1")
        {
            string id, name, artist, album;
            string lengthtest, playstest;
            bool valid = false;
            int length, plays;
            cout << "Please input the ID\n";
            cin >> id;
            TrackHash temp;
            temp.setId(id);
            if (table.search(temp, id))
            {
                cout << "Rejected! Duplicated Key!\n";
                cout << insertprompt;
            }
            else
            {
                cout << "Please input the Track Name\n";
                cin.ignore();
                getline(cin, name);
                cout << "Please input the Artist Name\n";
                getline(cin, artist);
                cout << "Please input the Album Name\n";
                getline(cin, album);
                cout << "Please input the Music Length (In Seconds)\n";
                //The following operation makes sure that the input is an integer
                while (valid == false)
                {
                    cin >> lengthtest;
                    for (int i = 0; i < lengthtest.length(); i++)
                    {
                        if (isdigit(lengthtest[i]) == false)
                        {
                            valid = false;
                            break;
                        }
                        else
                            valid = true;
                    }
                    if (valid == false)
                        cout << "It must be an integer, please try again.\n";
                }
                length = stoi(lengthtest);
                valid = false;
                cout << "Please input the number of plays\n";
                //The following operation makes sure that the input is an integer
                while (valid == false)
                {
                    cin >> playstest;
                    for (int i = 0; i < playstest.length(); i++)
                    {
                        if (isdigit(playstest[i]) == false)
                        {
                            valid = false;
                            break;
                        }
                        else
                            valid = true;
                    }
                    if (valid == false)
                        cout << "It must be an integer, please try again.\n";
                }
                plays = stoi(playstest);
                // create a Track object and TrackHash object and initialize it with data
                // Track is sorted by name(secondary key) for Binary Search Tree
                // TrackHash is sorted by id(primary key) for Hash Table
                Track aTrack(id, name, artist, album, length, plays);
                TrackHash aTrack2(id, name, artist, album, length, plays);
                tree.insert(aTrack);
                table.insert(aTrack2, aTrack2.getId());
                cout << "Inserted!\n";
                cout << insertprompt;
            }
        }
        else if (option == "2")
            return;
        else if (option == "H")
        {
            cout << "==============Insert Menu==============\n";
            cout << "1. Insert\n";
            cout << "2. Go back to main menu\n";
            cout << "=======================================\n";
        }
        else
        {
            cout << "Please try again!\n";
            cout << insertprompt;
        } 
    }
}

/*
deleteFunction: call the delete menu and allow users to choose the options
*/
void deleteFunction(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string option = "";
    string deleteprompt = "\nDelete Menu : Enter an option(H - for help)\n";
    cout << "==============Delete Menu==============\n";
    cout << "1. Delete by ID\n";
    cout << "2. Delete by Name\n";
    cout << "3. Go back to main menu\n";
    cout << "=======================================\n";
    while (option != "3")
    {
        cin >> option;
        cin.ignore();
        if (option == "1")
        {
            string trackID;
            cout << "Remove Track? Please enter the Track ID:\n";
            cin >> trackID;
            TrackHash temp;
            Track output;
            temp.setId(trackID);
            table.search(temp, temp.getId());
            //Remove the track from the tree and hash table if found
            if (table.remove(temp, temp.getId()))
            {
                cout << "Removed Successfully!\n";
                output.setName(temp.getName());
                tree.remove(output);
            }
            else
            {
                cout << "Not found!\n";
            }
            cout << deleteprompt;
        }
        else if (option == "2")
        {
            string trackName;
            cout << "Remove Track?  Please enter the Track Name:\n";
            getline(cin, trackName);
            Track temp;
            TrackHash output;
            temp.setName(trackName);
            tree.search(temp, output);
            //Remove the track from the tree and hash table if found
            if (tree.remove(temp))
            {
                cout << "Removed Successfully!\n";
                table.remove(output, output.getId());
            }
            else
            {
                cout << "Not found!\n";
            }
            cout << deleteprompt;
        }
        else if (option == "3")
            return;
        else if (option == "H")
        {
            cout << "==============Delete Menu==============\n";
            cout << "1. Delete by ID\n";
            cout << "2. Delete by Name\n";
            cout << "3. Go back to main menu\n";
            cout << "=======================================\n";
        }
        else
        {
            cout << "Please try again!\n";
            cout << deleteprompt;
        }
    }
}

/*
writetoFile: write the data in hash table sequence to the file chosen by the user
*/
void writetoFile(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string file;
    cout << "Please input the file name to write, the hash table sequence will be saved to this file.\n";
    cout << "(To save the tracks to the file, you can do it before exiting the program)\n";
    cin >> file;
    ofstream outputFile(file);
    if (outputFile.is_open())
    {
        outputFile << "Hash Table Sequence: \n";
        table.traverseFile(outputFile);
    }
    cout << "Written to file successfully!\n";
}

/*
savetoFile: write the data in original input format to the file chosen by the user
*/
void savetoFile(BinarySearchTree<Track>& tree, HashTable<TrackHash>& table)
{
    string file;
    string choice = "";
    bool valid = false;
    cout << "Do you want to save the data into a file? (Y for Yes, N for No)\n";
    while (valid == false)
    {
        cin >> choice;
        if (choice == "Y")
        {
            cout << "Please input the file name to save, this file will be in the same format as the original one.\n";
            cin >> file;
            ofstream output(file);
            Track temp;
            while (!tree.isEmpty())
            {
                tree.findRoot(temp);
                tree.remove(temp);
                output << temp.getId() << " " << temp.getName() <<
                    "; " << temp.getArtist() << "; " << temp.getAlbum()
                    << "; " << temp.getLength() << " " << temp.getPlays() << endl;
            }
            cout << "Saved to file: " << file << endl;
            valid = true;
        }
        else if (choice == "N")
        {
            valid = true;
            return;
        }
        else
        {
            cout << "Please try again!\n";
        }
    }
}

/*
getPrime: get the next prime number after multiplying the numbers of lines by 2 for the hash size
*/
int getPrime(int i)
{
    int number = i * 2;
    bool prime = false;
    while (!isPrime(number))
    {
        number++;
    }
    return number;
}

/*
isPrime: determine whether the number is a prime number
*/
bool isPrime(int number)
{
    bool prime = true;
    for (int count = 2; count < number && prime; count++)
    {
        if (number % count == 0)
        {
            prime = false;
        }
    }
    return prime;
}

/*
horizontal display: all items on one line
*/
void hDisplay(Track& track)
{
    cout << left;
    cout << " " << setw(20) << track.getId() << "  ";
    cout << " " << setw(20) << track.getName() << "  ";
    cout << " " << setw(20) << track.getArtist() << " ";
    cout << " " << setw(30) << track.getAlbum() << "  ";
    cout << " " << setw(22) << track.getLength() << "  ";
    cout << " " << setw(20) << track.getPlays() << "  ";
    cout << endl;
}

/*
vertical display: one item per line
*/
void vDisplay(Track& track)
{
    cout << "          Track ID: " << track.getId() << endl;
    cout << "              Name: " << track.getName() << endl;
    cout << "            Artist: " << track.getArtist() << endl;
    cout << "             Album: " << track.getAlbum() << endl;
    cout << "      Music Length: " << track.getLength() << " seconds" << endl;
    cout << "   Number of Plays: " << track.getPlays() << endl;
}

/*
indented tree display: one item per line, including the level number
*/
void iDisplay(Track& track, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << track.getName() << endl;
}