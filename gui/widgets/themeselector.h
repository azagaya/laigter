#ifndef THEMESELECTOR_H
#define THEMESELECTOR_H

#include <QWidget>

#include <QListWidgetItem>

namespace Ui
{
class ThemeSelector;
}

class ThemeSelector : public QWidget
{
  Q_OBJECT

public:
  explicit ThemeSelector(QWidget *parent = nullptr);
  ~ThemeSelector();

private slots:
  void on_listWidget_itemClicked(QListWidgetItem *item);

private:
  Ui::ThemeSelector *ui;
};

#endif // THEMESELECTOR_H
