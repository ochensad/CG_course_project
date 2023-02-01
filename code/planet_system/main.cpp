#include "mainwindow.h"

#include <QApplication>
#include <getopt.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <QTest>
#include "testg.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
    int res = 0;

    int sc = 0;
    int time_m = 0;
    int k = 0;
    QApplication a(argc, argv);
    MainWindow w;
    myGraphicsView* g = w.GetView();
    while ((res = getopt(argc, argv, "t:e:i:")) != -1) {
    switch (res) {
        case 't':
            k = std::stoi(optarg);
            sc = 1;
            break;
        case 'e':
            return QTest::qExec(new TestG(nullptr,g));
        case 'i':
            time_m = std::stoi(optarg);
            sc = 3;
            break;
        }
    }
    if (sc == 1)
    {
        using std::chrono::duration_cast;
        using std::chrono::microseconds;

        auto end = std::chrono::steady_clock::now();
        auto start = std::chrono::steady_clock::now();
        std::fstream f;
        f.open("measure.txt");
        for(int i = 0; i <= k; i++)
        {
            int l = 0;
            start = std::chrono::steady_clock::now();

            l = g->DrawMeasureSystem(i);

            end = std::chrono::steady_clock::now();


            f << (double)duration_cast<microseconds>(end - start).count() / 1000 << " " << l << std::endl;
        }
        f.close();
        system("../graphics.py");
        return 0;
    }
    if (sc == 3)
    {
        w.genImage(time_m);
    }

    return 0;
}
