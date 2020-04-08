#ifndef FRAME_SPLITTER_H
#define FRAME_SPLITTER_H

#include <QDialog>

namespace Ui {
class FrameSplitter;
}

class FrameSplitter : public QDialog
{
  Q_OBJECT

public:
  explicit FrameSplitter(int *h_frames, int* v_frames, QWidget *parent = nullptr);
  ~FrameSplitter();

private slots:
  void on_spinBoxHFrames_valueChanged(int arg1);

  void on_spinBoxVFrames_valueChanged(int arg1);

  void on_pushButtonOk_clicked();

  void on_pushButtonCancel_clicked();

private:
  Ui::FrameSplitter *ui;
  int *m_h_frames, *m_v_frames;
};

#endif // FRAME_SPLITTER_H
