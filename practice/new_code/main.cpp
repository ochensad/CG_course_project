#include "mainwindow.h"
#include "scene.h"
#include <getopt.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc == 1) {

            QApplication a(argc, argv);

            MainWindow w;

            w.show();

            return a.exec();

        }
    int res = 0;
    printf("%d", res);
    int sc = 0;
        while ((res = getopt(argc, argv, "f:s:t")) != -1) {

            switch (res) {

            case 'f':
                sc = 1;
                break;
            case 's':
                sc = 2;
                break;
            case 't':
                sc = 3;
                break;
            }
        }

    printf("%d", res);

    if (sc == 1)
    {
        Scene *sc = new Scene(1000, 800, 1);
        QImage cur_image = sc->draw_scene_1();
        cur_image.save("img.png");
    }

    if (sc == 2)
    {
        Scene *sc = new Scene(1000, 800, 1);
        QImage cur_image = sc->draw_scene_2();
        cur_image.save("img.png");
    }

    if (sc == 3)
    {
        Scene *sc = new Scene(1000, 800, 1);
        QImage cur_image = sc->draw_scene_3();
        cur_image.save("img.png");
    }
    return 0;
}
