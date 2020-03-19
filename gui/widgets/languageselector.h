#ifndef LANGUAGESELECTOR_H
#define LANGUAGESELECTOR_H

#include <QWidget>

namespace Ui {
class LanguageSelector;
}

class LanguageSelector : public QWidget
{
  Q_OBJECT

  public:
  explicit LanguageSelector(QWidget *parent = nullptr);
  ~LanguageSelector();

  private:
  Ui::LanguageSelector *ui;
};

#endif // LANGUAGESELECTOR_H
