#include "gui/frame_splitter.h"
#include "ui_frame_splitter.h"

FrameSplitter::FrameSplitter(int *h_frames, int* v_frames, QWidget *parent) :
                                                                              QDialog(parent),
                                                                              ui(new Ui::FrameSplitter),
                                                                              m_h_frames(h_frames),
                                                                              m_v_frames(v_frames)
{
  ui->setupUi(this);
  *m_h_frames = 1;
  *m_v_frames = 1;
}

FrameSplitter::~FrameSplitter()
{
  delete ui;
}

void FrameSplitter::on_spinBoxHFrames_valueChanged(int arg1)
{
  *m_h_frames = arg1;
}

void FrameSplitter::on_spinBoxVFrames_valueChanged(int arg1)
{
  *m_v_frames = arg1;
}

void FrameSplitter::on_pushButtonOk_clicked()
{
  close();
}

void FrameSplitter::on_pushButtonCancel_clicked()
{
  *m_h_frames = 0;
  *m_v_frames = 0;
  close();
}
