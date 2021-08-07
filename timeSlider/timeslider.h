#ifndef TIMESLIDER_H
#define TIMESLIDER_H

#include <QWidget>

namespace Ui
{
class TimeSlider;
}

class TimeSlider : public QWidget
{
    Q_OBJECT

  public:
    explicit TimeSlider(QWidget *parent = nullptr);
    ~TimeSlider();

    void setMaxVal(qreal val);
    void setMinVal(qreal val);
    void setVal(qreal val);

    qreal getCurVal() const;
    qreal getMinVal() const;
    qreal getMaxVal() const;

  protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

  private:
    void getCurPoint(QMouseEvent *event);

  signals:
    void sigPositonChange(qreal curVal);

  private:
    QPoint m_curPoint;
    qreal m_maxVal;
    qreal m_minVal;
    qreal m_curVal;

    QPixmap m_handlerImage;

  private:
    Ui::TimeSlider *ui;
};

#endif  // TIMESLIDER_H
