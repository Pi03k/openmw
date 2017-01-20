#include <QApplication>
#include <QMainWindow>
#include "reporttable.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;
    ReportModel model;
    ReportTable table(&window, &model);
    window.setCentralWidget(&table);
    window.show();
    return app.exec();
}
