#ifndef GEN_ID_H
#define GEN_ID_H

#include <QDialog>
#include "chains.h"

namespace Ui {
class gen_id;
}

class gen_id : public QDialog
{
    Q_OBJECT

public:
    explicit gen_id(QWidget *parent = nullptr);
    ~gen_id();

private slots:
    void on_genId_clicked();

    void on_backButton_clicked();

private:
    Ui::gen_id *ui;
    HashTable hashTable;
};

#endif // GEN_ID_H
