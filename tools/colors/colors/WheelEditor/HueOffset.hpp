#ifndef HUEOFFSET_HPP
#define HUEOFFSET_HPP

#include <QSharedDataPointer>
#include <QColor>

class HueOffsetData;

class HueOffset
{
public:
    HueOffset();
    HueOffset(qint16 offset, quint8 saturation, quint8 value, quint8 alpha);
    HueOffset(const HueOffset &);
    HueOffset &operator=(const HueOffset &);
    ~HueOffset();

    qint16      getOffset()const;
    quint8      getSaturation()const;
    quint8      getValue()const;
    quint8      getAlpha()const;

    void        setOffset(qint16 offset);
    void        setSaturation(quint8 saturation);
    void        setValue(quint8 value);
    void        setAlpha(quint8 alpha);

    QColor      computeColor(quint16 baseHue)const;
    HueOffset   normalize()const;
private:
    QSharedDataPointer<HueOffsetData> data;
};

Q_DECLARE_METATYPE(HueOffset);

#endif // HUEOFFSET_HPP
