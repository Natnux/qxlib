#ifndef SELECTION_H
#define SELECTION_H

#include <QObject>
#include <QString>
#include <QRect>
#include <QDebug>

class Selection : public QObject, public QRect
{
    Q_OBJECT
public:
    explicit Selection(const QPoint & topLeft, const QPoint & bottomRight)
                : QRect(topLeft, bottomRight)
    {
        p_integral = 0;
        p_weighted_x = 0;
        p_weighted_y = 0;
    }
    explicit Selection(const QPoint & topLeft, const QSize & size)
                : QRect(topLeft, size)
    {
        p_integral = 0;
        p_weighted_x = 0;
        p_weighted_y = 0;
    }
    explicit Selection(int x, int y, int width, int height)
                : QRect(x, y, width, height)
    {
        p_integral = 0;
        p_weighted_x = 0;
        p_weighted_y = 0;
    }

    Selection();
    Selection(const Selection & other);
    ~Selection();


//    QRect area() const;
    double integral() const;
    double weighted_x() const;
    double weighted_y() const;

//    void setArea(QRect rect);
    void setSum(double value);
    void setWeightedX(double value);
    void setWeightedY(double value);

    Selection &operator =(QRect other);
    Selection &operator =(Selection other);

private:
//    QRect p_area;
    double p_integral;
    double p_weighted_x;
    double p_weighted_y;
};

Q_DECLARE_METATYPE(Selection);

QDebug operator<<(QDebug dbg, const Selection &file);

QDataStream &operator<<(QDataStream &out, const Selection &selection);
QDataStream &operator>>(QDataStream &in, Selection &selection);

#endif // SELECTION_H