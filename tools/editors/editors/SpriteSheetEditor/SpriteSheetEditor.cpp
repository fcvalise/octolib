#include "SpriteSheetEditor.hpp"
#include "SpriteSheetView.hpp"

#include <QGridLayout>

#include <BinaryInputStream.hpp>

#include <fstream>

SpriteSheetEditor::SpriteSheetEditor(QWidget *parent) :
    QWidget(parent),
    m_spriteSheetView(new SpriteSheetView)
{
    QGridLayout*    layout = new QGridLayout(this);

    layout->addWidget(m_spriteSheetView, 0, 0);
}

SpriteSheetEditor::~SpriteSheetEditor()
{
}

void SpriteSheetEditor::newSpriteSheet(QPixmap const& pixmap)
{
    m_spriteSheetView->newSpriteSheet(pixmap);
}

void SpriteSheetEditor::openSpriteSheet(const QString &filePath)
{
    QPixmap                 pixmap;
    octo::ByteArray         buffer;
    octo::BinaryInputStream is(buffer);
    std::fstream            file;
    quint32                 textureByteCount = 0u;

    file.open(filePath.toStdString(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open() == false)
        return;
    if (buffer.read(file) == false)
        return;
    is.read(textureByteCount);
    pixmap.loadFromData(static_cast<uchar const*>(buffer.bytes() + is.getPosition()));
}

