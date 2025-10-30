#include <iostream>
#include <fstream>
#include <Windows.h>

int** create_board(int& rows, int& cols)
{
   int** mass = new int* [rows]();
    
    for (int i{ 0 }; i < rows; i++)
    {
       mass[i] = new int[cols]();
    }

    return mass;
}

void print_board(int** board, int& rows, int& cols, int& generatio, int& alive)
{
    for (int i{ 0 }; i < rows; i++)
    {
        for (int j{ 0 }; j < cols; j++)
        {
            if (board[i][j] == 1)
                std::cout << " * ";
            else
                std::cout << " - ";
        }
        std::cout << std::endl;
    }

    std::cout << "Поколение: " << generatio << ". Живых клеток: "<< alive << std::endl;
}

int count_alive(int** board, int& rows, int& cols)
{
    int summ{ 0 };
    for (int i{ 0 }; i < rows; i++)
    {
        for (int j{ 0 }; j < cols; j++)
        {
            if (board[i][j] == 1)
                summ++;
        }
    }

    return summ;
}

int count_neighbors(int** board, int& rows, int& cols, int& r, int& c)
{
    int neighbors[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    int count = 0;

    for (int i{ 0 }; i < 8; i++)
    {
        int a = r + neighbors[i][0];
        int b = c + neighbors[i][1];

        if (a >= 0 && a < rows && b >= 0 && b < cols)
        {
            if (board[a][b] == 1)
                count++;
        }
    }

    return count;
}


void next_generation(int** board1, int** board2, int& rows, int& cols)
{
    for (int i{ 0 }; i < rows; ++i)
    {
        for (int j{ 0 }; j < cols; ++j)
        {
            int n = count_neighbors(board1, rows, cols, i, j);
            if (board1[i][j] == 1)
            {
                if (n == 2 || n == 3)
                    board2[i][j] = 1;
                else
                    board2[i][j] = 0;
            }
            else
            {
                if (n == 3)
                    board2[i][j] = 1;
                else
                    board2[i][j] = 0;
            }
        }
    }
}

bool samme(int** board1, int** board2, int& rows, int& cols)
{
    for (int i{ 0 }; i < rows; ++i)
    {
        for (int j{ 0 }; j < cols; ++j)
        {
            if (board1[i][j] != board2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void copy_bord(int** board2, int** board1, int& rows, int& cols)
{
    for (int i{ 0 }; i < rows; i++)
        for (int j{ 0 }; j < cols; j++)
            board1[i][j] = board2[i][j];
}

void delete_bord(int** mass, int& rows)
{
    for (int i{ 0 }; i < rows; i++)
    {
        delete[] mass[i];
    }
    delete[] mass;
}

int main()
{
   
    setlocale(LC_ALL, "RU");

    std::ifstream fin("in.txt");
    if (!fin.is_open())
    {
        std::cout << "Не получилось открыть файл!" << std::endl;

        return EXIT_FAILURE;
    }
    
    int rows{}, cols{};
    int generation{ 1 };
    int a{}, b{};
    bool same{ 0 };

    fin >> rows;
    fin >> cols;

    int** board1 = create_board(rows, cols);
    int** board2 = create_board(rows, cols);

    while (fin >> a >> b)
    {
        board1[a][b] = 1;
    }

    fin.close();

    int alive = count_alive(board1, rows, cols);
    print_board(board1, rows, cols, generation, alive);

    while (same == 0 && alive != 0)
    {
        Sleep(1000);
        generation++;

        next_generation(board1, board2, rows, cols);

        same = samme(board1, board2, rows, cols);

        alive = count_alive(board2, rows, cols);
        std::system("CLS");
        print_board(board2, rows, cols, generation, alive);
        copy_bord(board2, board1, rows, cols);
    }
    delete_bord(board2, rows);
    delete_bord(board1, rows);
    if (same == 1)
    {
        std::cout << "Игровое поле стабильно. Конец игры." << std::endl;
    }
    else
    {
        std::cout << "Живые клетки отсутствуют. Конец игры." << std::endl;
    }
    return EXIT_SUCCESS;
}
