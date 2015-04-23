#include "ColorEditor.hpp"
#include "AbstractColorEditor.hpp"
#include "RgbaColorEditor.hpp"
#include "HsvColorEditor.hpp"

ColorEditor::ColorEditor(QWidget *parent) :
    QTabWidget(parent)
{
    addEditor(new HsvColorEditor(this), tr("HSV"));
    addEditor(new RgbaColorEditor(this), tr("RGBA"));

    connect(this, SIGNAL(currentChanged(int)), SLOT(onEditorChanged(int)));
}

ColorEditor::~ColorEditor()
{
}

void ColorEditor::setColor(QColor color)
{
    for (auto p : m_editors)
    {
        p->setColor(color);
    }
    m_color = color;
}

void ColorEditor::addEditor(AbstractColorEditor *editor, const QString &label)
{
    int id = addTab(editor, label);

    m_editors[id] = editor;
    connect(editor, SIGNAL(colorChanged(QColor)), this, SLOT(onColorChanged(QColor)));
}

void ColorEditor::onColorChanged(QColor color)
{
    m_color = color;
    emit colorChanged(color);
}

void ColorEditor::onEditorChanged(int editorId)
{
    if (editorId < m_editors.size())
        m_editors[editorId]->setColor(m_color);
}

