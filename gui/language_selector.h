#ifndef LANGUAGESELECTOR_H
#define LANGUAGESELECTOR_H

#include <QDialog>
#include <QTranslator>

namespace Ui
{
class LanguageSelector;
}

class LanguageSelector : public QDialog
{
  Q_OBJECT

private:
  Ui::LanguageSelector *ui;
  QString icon_path;

public:
  explicit LanguageSelector(QWidget *parent = nullptr);
  ~LanguageSelector();
  QPixmap icon;
  QTranslator *translator;

private slots:
  void on_listWidget_itemSelectionChanged();
  void on_pushButton_clicked();
};

#endif // LANGUAGESELECTOR_H
