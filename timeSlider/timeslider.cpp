#include "timeslider.h"
#include <QMouseEvent>
#include <QPainter>
#include "ui_timeslider.h"

TimeSlider::TimeSlider(QWidget *parent) : QWidget(parent), ui(new Ui::TimeSlider)
{
    ui->setupUi(this);

    this->setFixedSize(600, 100);
    m_curPoint = QPoint(11, 0);

    m_handlerImage.load(":/slider/img/handler.png");
}

TimeSlider::~TimeSlider()
{
    delete ui;
}

void TimeSlider::setMaxVal(qreal val)
{
    m_maxVal = val;
}

void TimeSlider::setMinVal(qreal val)
{
    m_minVal = val;
}

void TimeSlider::setVal(qreal val)
{
    m_curVal   = val;
    int posX   = (this->width() - 22) * (m_curVal - m_minVal) / (m_maxVal - m_minVal) + 11;
    m_curPoint = QPoint(posX, 0);
    update();
}

qreal TimeSlider::getCurVal() const
{
    return m_curVal;
}

qreal TimeSlider::getMinVal() const
{
    return m_minVal;
}

qreal TimeSlider::getMaxVal() const
{
    return m_maxVal;
}

void TimeSlider::paintEvent(QPaintEvent *e)
{
    // 绘制滑块前面区域
    QPainter painter(this);
    painter.setBrush(QColor(39, 105, 188));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(QRect(0, this->height() / 5 * 2, m_curPoint.x(), this->height() / 5), 4,
                            4);

    // 绘制滑块后面区域
    painter.setBrush(QColor(206, 206, 206));
    painter.drawRoundedRect(QRect(m_curPoint.x(), this->height() / 5 * 2,
                                  this->width() - m_curPoint.x(), this->height() / 5),
                            4, 4);

    // 绘制滑块
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(206, 206, 206));
    painter.setBrush(Qt::white);
    painter.setPen(pen);
    painter.drawEllipse(QPointF(m_curPoint.x(), this->height() / 2), 10, 10);
    painter.drawPixmap(QRect(m_curPoint.x(), this->height() / 2, 13, 13), m_handlerImage);
}

void TimeSlider::mousePressEvent(QMouseEvent *event)
{
    getCurPoint(event);
}

void TimeSlider::mouseMoveEvent(QMouseEvent *event)
{
    getCurPoint(event);
}

void TimeSlider::getCurPoint(QMouseEvent *event)
{
    if (event->pos().x() < 11)
    {
        m_curPoint = QPoint(11, 0);
    }
    else if (event->pos().x() > this->width() - 11)
    {
        m_curPoint = QPoint(this->width() - 11, 0);
    }
    else
    {
        m_curPoint = event->pos();
    }
    update();

    m_curVal =
        (qreal)(m_curPoint.x() - 11) / (this->width() - 22) * (m_maxVal - m_minVal) + m_minVal;
    emit sigPositonChange(m_curVal);
}
