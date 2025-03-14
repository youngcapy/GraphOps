// GraphEditor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ShObjIdl_core.h>
#include <commdlg.h>


#include "graph.h"
#include "MainGraph.h"
#include "FileReader.h"



#include <string>
#include <fstream>
#include <algorithm>

int main()
{

    std::string graph_path{ FileReader::reader() };

    MainGraph gr{ graph_path };

    gr.print_tops_degrees();
    gr.print_aliquot_edges();
    gr.incidence_matrix();

    std::stringstream ss;
    
    auto file_pair = gr.get_names();
    std::string command{};
    ss << "dot -Tpng -ostarter_dia.png " << file_pair[0];
    command = ss.str();
    system(command.c_str());
    ss.str("");
    ss << "dot -Tpng -onon_iso_dia.png " << file_pair[1];
    command = ss.str();
    system(command.c_str());
    ss.str("");
    ss << "dot -Tpng -oadd_dia.png " << file_pair[2];
    command = ss.str();
    system(command.c_str());


    return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
