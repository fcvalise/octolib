#include "HueOffset.hpp"

namespace
{
    template <class T>
    T   clamp(T value, T min, T max)
    {
        if (value > max)
            value = max;
        else if (value < min)
            value = min;
        return (value);
    }
}

class HueOffsetData : public QSharedData
{
public:
    HueOffsetData() :
        offset(0),
        saturation(255),
        value(255),
        alpha(255)
    {
    }

    HueOffsetData(qint16 offset, quint8 saturation, quint8 value, quint8 alpha) :
        offset(offset),
        saturation(saturation),
        value(value),
        alpha(alpha)
    {
    }

    qint16  offset;
    quint8  saturation;
    quint8  value;
    quint8  alpha;
};

HueOffset::HueOffset() :
    data(new HueOffsetData)
{   
}

HueOffset::HueOffset(qint16 offset, quint8 saturation, quint8 value, quint8 alpha) :
    data(new HueOffsetData(offset, saturation, value, alpha))
{
}

HueOffset::HueOffset(const HueOffset &rhs) :
    data(rhs.data)
{
}

HueOffset &HueOffset::operator = (const HueOffset &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

HueOffset::~HueOffset()
{
}

qint16 HueOffset::getOffset() const
{
    return (data->offset);
}

quint8 HueOffset::getSaturation() const
{
    return (data->saturation);
}

quint8 HueOffset::getValue() const
{
    return (data->value);
}

quint8 HueOffset::getAlpha() const
{
    return (data->alpha);
}

void HueOffset::setOffset(qint16 offset)
{
    data->offset = offset;
}

void HueOffset::setSaturation(quint8 saturation)
{
    data->saturation = saturation;
}

void HueOffset::setValue(quint8 value)
{
    data->value = value;
}

void HueOffset::setAlpha(quint8 alpha)
{
    data->alpha = alpha;
}

QColor HueOffset::computeColor(quint16 baseHue) const
{
    int hue = data->offset + baseHue;

    if (hue >= 360)
    {
        while (hue >= 360)
            hue -= 360;
    }
    else if (hue < 0)
    {
        while (hue < 0)
            hue += 360;
    }
    return (QColor::fromHsv(hue,
                            data->saturation,
                            data->value,
                            data->alpha));
}

HueOffset HueOffset::normalize() const
{
    return (HueOffset(clamp<qint16>(data->offset, 0, 359),
                      clamp<quint8>(data->saturation, 0, 255),
                      clamp<quint8>(data->value, 0, 255),
                      clamp<quint8>(data->alpha, 0, 255)));
}

HueOffset HueOffset::addOffset(int offsetToAdd)
{
    return (HueOffset(data->offset + offsetToAdd, data->saturation,
                      data->value, data->alpha));
}

