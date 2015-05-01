#include "HueOffset.hpp"

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
    return (QColor::fromHsv(data->offset + baseHue,
                            data->saturation,
                            data->value,
                            data->alpha));
}

