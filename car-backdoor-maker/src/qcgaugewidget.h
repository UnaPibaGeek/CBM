/***************************************************************************
**                                                                        **
**  QcGauge, for instrumentation, and real time data measurement          **
**  visualization widget for Qt.                                          **
**  Copyright (C) 2015 Hadj Tahar Berrima                                 **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU Lesser General Public License as        **
**  published by the Free Software Foundation, either version 3 of the    **
**  License, or (at your option) any later version.                       **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU Lesser General Public License for more details.                   **
**                                                                        **
**  You should have received a copy of the GNU Lesser General Public      **
**  License along with this program.                                      **
**  If not, see http://www.gnu.org/licenses/.                             **
**                                                                        **
****************************************************************************
**           Author:  Hadj Tahar Berrima                                  **
**           Website: http://pytricity.com/                               **
**           Contact: berrima_tahar@yahoo.com                             **
**           Date:    1 dec 2014                                          **
**           Version:  1.0                                                **
****************************************************************************/

#ifndef QCGAUGEWIDGET_H
#define QCGAUGEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QObject>
#include <QRectF>
#include <QtMath>



#if defined(QCGAUGE_COMPILE_LIBRARY)
#  define QCGAUGE_DECL  Q_DECL_EXPORT
#elif defined(QCGAUGE_USE_LIBRARY)
#  define QCGAUGE_DECL Q_DECL_IMPORT
#else
#  define QCGAUGE_DECL
#endif

class QcGaugeWidget;
class QcItem;
class QcBackgroundItem;
class QcDegreesItem;
class QcValuesItem;
class QcArcItem;
class QcColorBand;
class QcNeedleItem;
class QcLabelItem;
class QcGlassItem;
class QcAttitudeMeter;
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
class QCGAUGE_DECL QcGaugeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QcGaugeWidget(QWidget *parent = 0);

    QcBackgroundItem* addBackground(float position);
    QcDegreesItem* addDegrees(float position);
    QcValuesItem* addValues(float position);
    QcArcItem* addArc(float position);
    QcColorBand* addColorBand(float position);
    QcNeedleItem* addNeedle(float position);
    QcLabelItem* addLabel(float position);
    QcGlassItem* addGlass(float position);
    QcAttitudeMeter* addAttitudeMeter(float position);


    void addItem(QcItem* item, float position);
    int removeItem(QcItem* item);
    QList <QcItem*> items();
    QList <QcItem*> mItems;


signals:

public slots:
private:
    void paintEvent(QPaintEvent *);

};

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcItem : public QObject
{
    Q_OBJECT
public:
    explicit QcItem(QObject *parent = 0);
    virtual void draw(QPainter *) = 0;
    virtual int type();

    void setPosition(float percentage);
    float position();
    QRectF rect();
    enum Error{InvalidValueRange,InvalidDegreeRange,InvalidStep};


protected:
    QRectF adjustRect(float percentage);
    float getRadius(const QRectF &);
    float getAngle(const QPointF&, const QRectF &tmpRect);
    QPointF getPoint(float deg, const QRectF &tmpRect);
    QRectF resetRect();
    void update();

private:
    QRectF mRect;
    QWidget *parentWidget;
    float mPosition;
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcScaleItem : public QcItem
{
    Q_OBJECT
public:
    explicit QcScaleItem(QObject *parent = 0);

    void setValueRange(float minValue,float maxValue);
    void setDgereeRange(float minDegree,float maxDegree);
    void setMinValue(float minValue);
    void setMaxValue(float maxValue);
    void setMinDegree(float minDegree);
    void setMaxDegree(float maxDegree);

signals:

public slots:
protected:

    float getDegFromValue(float);

    float mMinValue;
    float mMaxValue;
    float mMinDegree;
    float mMaxDegree;

};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcBackgroundItem : public QcItem
{
    Q_OBJECT
public:
    explicit QcBackgroundItem(QObject *parent = 0);
    void draw(QPainter*);
    void addColor(float position, const QColor& color);
    void clearrColors();


private:
    QPen mPen;
    QList<QPair<float,QColor> > mColors;
    QLinearGradient mLinearGrad;
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QcGlassItem : public QcItem
{
    Q_OBJECT
public:
    explicit QcGlassItem(QObject *parent = 0);
    void draw(QPainter*);
};



///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcLabelItem : public QcItem
{
    Q_OBJECT
public:
    explicit QcLabelItem(QObject *parent = 0);
    virtual void draw(QPainter *);
    void setAngle(float);
    float angle();
    void setText(const QString &text, bool repaint = true);
    QString text();
    void setColor(const QColor& color);
    QColor color();

private:
    float mAngle;
    QString mText;
    QColor mColor;
};

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcArcItem : public QcScaleItem
{
    Q_OBJECT
public:
    explicit QcArcItem(QObject *parent = 0);
    void draw(QPainter*);
    void setColor(const QColor& color);

private:
    QColor mColor;

signals:

public slots:


};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcColorBand : public QcScaleItem
{
    Q_OBJECT
public:
    explicit QcColorBand(QObject *parent = 0);
    void draw(QPainter*);
    void setColors(const QList<QPair<QColor,float> >& colors);

private:
   QPainterPath createSubBand(float from,float sweep);

   QList<QPair<QColor,float> > mBandColors;
   float mBandStartValue;
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
class QCGAUGE_DECL QcDegreesItem : public QcScaleItem
{
    Q_OBJECT
public:
    explicit QcDegreesItem(QObject *parent = 0);
    void draw(QPainter *painter);
    void setStep(float step);
    void setColor(const QColor& color);
    void setSubDegree(bool );
private:
    float mStep;
    QColor mColor;
    bool mSubDegree;
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcNeedleItem : public QcScaleItem
{
    Q_OBJECT
public:
    explicit QcNeedleItem(QObject *parent = 0);
    void draw(QPainter*);
    void setCurrentValue(float value);
    float currentValue();
    void setValueFormat(QString format);
    QString currentValueFormat();
    void setColor(const QColor & color);
    QColor color();

    void setLabel(QcLabelItem*);
    QcLabelItem * label();

    enum NeedleType{DiamonNeedle,TriangleNeedle,FeatherNeedle,AttitudeMeterNeedle,CompassNeedle};//#

    void setNeedle(QcNeedleItem::NeedleType needleType);
private:
    QPolygonF mNeedlePoly;
    float mCurrentValue;
    QColor mColor;
    void createDiamonNeedle(float r);
    void createTriangleNeedle(float r);
    void createFeatherNeedle(float r);
    void createAttitudeNeedle(float r);
    void createCompassNeedle(float r);
    NeedleType mNeedleType;
    QcLabelItem *mLabel;
    QString mFormat;
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


class QCGAUGE_DECL QcValuesItem : public QcScaleItem
{
    Q_OBJECT
public:
    explicit QcValuesItem(QObject *parent = 0);
    void draw(QPainter*);
    void setStep(float step);
    void setColor(const QColor& color);
private:
    float mStep;
    QColor mColor;
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

class QCGAUGE_DECL QcAttitudeMeter : public QcItem
{
    Q_OBJECT
public:
    explicit QcAttitudeMeter(QObject *parent = 0);

    void draw(QPainter *);
    void setCurrentPitch(float pitch);
    void setCurrentRoll(float roll);
private:
    float mRoll;
    float mPitch;
    float mPitchOffset;

    QPolygonF mHandlePoly;
    QPainterPath mStepsPath;

    QPointF getIntersection(float r,const QPointF& pitchPoint,const QPointF& pt);
    float getStartAngle(const QRectF& tmpRect);

    void drawDegrees(QPainter *);
    void drawDegree(QPainter * painter, const QRectF& tmpRect,float deg);
    void drawUpperEllipse(QPainter *,const QRectF&);
    void drawLowerEllipse(QPainter *,const QRectF&);
    void drawPitchSteps(QPainter *,const QRectF&);
    void drawHandle(QPainter *);
    void drawSteps(QPainter *,float);

};

#endif // QCGAUGEWIDGET_H
