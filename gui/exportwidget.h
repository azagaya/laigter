#ifndef EXPORTWIDGET_H
#define EXPORTWIDGET_H

#include <QWidget>

namespace Ui {
class ExportWidget;
}

class ExportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExportWidget(QWidget *parent = nullptr);
    ~ExportWidget();

private:
    Ui::ExportWidget *ui;
};

#endif // EXPORTWIDGET_H
