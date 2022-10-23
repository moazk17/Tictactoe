#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

// Prints the grid
void print_grid(int grid[])
{

    for (int i = 0; i < 9; i++)
    {

        cout << "|";
        // if box is x
        if (grid[i] == 1)
        {
            cout << "x";
        }
        // if box is o
        else if (grid[i] == 2)
        {
            cout << "o";
        }
        // else is box free
        else
        {
            cout << " ";
        }
        // check if its the end of a row
        if (i % 3 == 2)
        {
            cout << "|" << endl;
        }
    }
}

// Checks if the game is over and returns winner
int check_win(int grid[])
{
    int win = 0;
    for (int i = 0; i < 3; i++)
    {
        // check rows
        if (grid[i] == grid[i + 3] && grid[i] == grid[i + 6] && grid[i] != 0)
        {
            win = grid[i];
        }
    }
    // check columns
    for (int i = 0; i < 9; i += 3)
    {
        if (grid[i] == grid[i + 1] && grid[i] == grid[i + 2] && grid[i] != 0)
        {
            win = grid[i];
        }
    }
    // check diagonals
    if (grid[0] == grid[4] && grid[0] == grid[8] && grid[0] != 0)
    {
        win = grid[0];
    }
    // check other diagonal
    if (grid[2] == grid[4] && grid[2] == grid[6] && grid[2] != 0)
    {
        win = grid[2];
    }
    // returns 0 if no one has won or 1 or 2 if someone has won
    return win;
}
// checks if the game is a tie
int tie(int grid[])
{
    int tie = 1;
    for (int i = 0; i < 9; i++)
    {
        if (grid[i] == 0)
        {
            tie = 0;
            return tie;
        }
    }
    return tie;
}

int main(int argc, char *argv[])
{
    cout << argc << endl;
    // intialize variables
    int exit = 0;
    int x_wins = 0;
    int o_wins = 0;
    int draw = 0;
    int aborted = 0;

    
    // start games
    for (int i = 0; i < argc - 1; i++)
    {
        // if there are arguments, we use files as games
        if (argc > 1)
        {

            // open input file stream
            ifstream file(argv[i+1]);
            // if file is not found or does not read we abort
            if (!file.is_open())
            {
                ++aborted;
                cerr << "Bad file: " << argv[i+1] << endl;
                exit = 1;
                continue;
            }
            else
            {
                
                // intialize grid
                int grid[9];
                for (int i = 0; i < 9; i++)
                {
                    grid[i] = 0;
                }
                // x always goes first, so turn = 1
                int turn = 1;
                string line;
                // read file line by line
                while (getline(file, line))
                {
                    
                    // initialize variables for input, row and column
                    char input = 0;
                    int row = -1;
                    int col = -1;
                    // convert line to input stream and assign first 3 variables to input, row and column respectively(correct input)
                    istringstream iss(line);
                    iss >> input;
                    iss >> row;
                    iss >> col;                
                    // count number of words in a line to check if there is more than 3 words
                    int count = 0;
                    string word;
                    while (iss >> word)
                    {
                        count++;
                    }
                    if ((turn == 1 && input == 'o') || (turn == 2 && input == 'x') || // if wrong player tries to play
                        row > 2 || col > 2 || row < 0 || col < 0 ||                   // if row or column is out of bounds
                        grid[(row * 3) +col] != 0 ||                       // if box is already taken
                        (input != 'x' && input != 'o') ||
                        count != 0                             // if input is not x or o
                        )                                                             // if there is more items on line
                    {
                        ++aborted;
                        cerr << "Invalid move: " << line << endl;
                        exit = 1;
                        break;
                    }
                    else // play the move
                    {
                        if (input == 'x')
                        {
                            grid[(row * 3) + col] = 1;
                            turn = 2;
                        }
                        else
                        {
                            grid[(row * 3) + col] = 2;
                            turn = 1;
                        }
                    }
                    // print grid
                    print_grid(grid);
                    // check if game is over
                    int win = check_win(grid);
                    if (win == 1)
                    {
                        ++x_wins;
                        cout << "x won!" << endl;
                        break;
                    }
                    else if (win == 2)
                    {
                        ++o_wins;
                        cout << "o won!"<<endl;
                        break;
                    }
                    // check tie
                    int ties = tie(grid);
                    if (ties == 1)
                    {
                        ++draw;
                        cout << "Tie" << endl;
                        break;
                    }
                }
            }
        }
        else // if there are no arguments, we play one game from stdin
        {
            int grid[9];
            for (int i = 0; i < 9; i++)
            {
                grid[i] = 0;
            }
            int turn = 1;
            while (!cin.fail())
            {
                // take first line from stdin
                string line;
                getline(cin, line);
                cout << line << endl;
                // initialize variables for input, row and column
                char input = 0;
                int row = -1;
                int col = -1;

                // convert line to input stream and assign first 3 variables to input, row and column respectively(correct input)
                istringstream iss(line);
                iss >> input;
                iss >> row;
                iss >> col;
                cout << "input: " << input << " row: " << row << " col: " << col << endl;
                // count number of words in a line to check if there is more than 3 words
                int count = 0;
                string word;
                while (iss >> word)
                {
                    count++;
                }
                if ((turn == 1 && input == 'o') || (turn == 2 && input == 'x') || // if wrong player tries to play
                    row > 2 || col > 2 || row < 0 || col < 0 ||                   // if row or column is out of bounds or row and col have not been assignedr
                    grid[(row * 3) + col] != 0 ||                                 // if box is already taken
                    (input != 'x' && input != 'o') ||
                    count != 0) // if input is not x or o
                                // if there is more items on line
                {
                    ++aborted;
                    cerr << "Invalid move: " << line << endl;
                    exit = 1;
                    break;
                }
                else // play the move
                {
                    if (input == 'x')
                    {
                        grid[(row * 3) + col] = 1;
                        turn = 2;
                    }
                    else
                    {
                        grid[(row * 3) + col] = 2;
                        turn = 1;
                    }
                }
                print_grid(grid);
                // check if game is over
                int win = check_win(grid);
                if (win == 1)
                {
                    ++x_wins;
                    cout << "x won!" << endl;
                    break;
                }
                else if (win == 2)
                {
                    ++o_wins;
                    cout << "o won!" << endl;
                    break;
                }
                // check tie
                int ties = tie(grid);
                if (ties == 1)
                {
                    
                    ++draw;
                    cout << "Tie" << endl;
                    break;
                }
            }
        }
        if (x_wins + o_wins + aborted != i ) {
            cout << "Unfinished game" << endl;
            ++aborted;
        }
    }
    // print results
    cout.width(16);
    cout << left << "x Wins: " << x_wins << endl;
    cout.width(16);
    cout << left << "o Wins: " << o_wins << endl;
    cout.width(16);
    cout << left << "Ties: " << draw << endl;
    cout.width(16);
    cout << left << "Aborted Games: " << aborted << endl;
    return exit;
}