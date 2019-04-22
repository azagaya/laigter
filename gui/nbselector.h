#ifndef NBSELECTOR_H
#define NBSELECTOR_H

#include <QDialog>
#include "src/imageprocessor.h"
#include "src/imageloader.h"

namespace Ui {
class NBSelector;
}

class NBSelector : public QDialog
{
    Q_OBJECT

public:
    explicit NBSelector(ImageProcessor *processor, QWidget *parent = nullptr);
    ~NBSelector();

private slots:
    void on_pushButtonResetNeighbours_clicked();
    void get_neighbours();

    void on_NUL_clicked();

    void on_NUM_clicked();

    void on_NUR_clicked();

    void on_NML_clicked();

    void on_NMM_clicked();

    void on_NMR_clicked();

    void on_NBL_clicked();

    void on_NBM_clicked();

    void on_NBR_clicked();

    void on_pushButton_clicked();

private:
    Ui::NBSelector *ui;
    ImageProcessor *processor;
    ImageLoader *il;
};

#endif // NBSELECTOR_H
