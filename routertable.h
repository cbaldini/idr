#ifndef ROUTERTABLE_H
#define ROUTERTABLE_H

#include <QMainWindow>

namespace Ui {
class RouterTable;
}

class RouterTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit RouterTable(QWidget *parent = 0);
    ~RouterTable();

private:
    Ui::RouterTable *ui;
};

#endif // ROUTERTABLE_H
