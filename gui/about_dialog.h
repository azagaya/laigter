#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QWidget>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QWidget {
  Q_OBJECT

private:
  Ui::AboutDialog *ui;

public:
  explicit AboutDialog(QWidget *parent = nullptr);
  ~AboutDialog();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
};

#endif // ABOUTDIALOG_H
