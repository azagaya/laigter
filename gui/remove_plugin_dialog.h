#ifndef REMOVEPLUGINDIALOG_H
#define REMOVEPLUGINDIALOG_H

#include <QDialog>

namespace Ui {
class RemovePluginDialog;
}

class RemovePluginDialog : public QDialog {
  Q_OBJECT

private:
  Ui::RemovePluginDialog *ui;

public:
  explicit RemovePluginDialog(QWidget *parent = nullptr);
  ~RemovePluginDialog();
  void setPluginList(QStringList plugin_list);

private slots:
  void on_buttonBox_accepted();
};

#endif // REMOVEPLUGINDIALOG_H
