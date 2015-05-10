#ifndef COLOREDITOR_HPP
#define COLOREDITOR_HPP

#include <QTabWidget>
#include <QMap>
#include <QColor>

class AbstractColorEditor;

class ColorEditor : public QTabWidget
{
    Q_OBJECT
public:
    explicit ColorEditor(QWidget* parent = nullptr);
    ~ColorEditor();

    void    setColor(QColor color);
private:
    void    addEditor(AbstractColorEditor* editor, QString const& label);
private slots:
    void    onColorChanged(QColor color);
    void    onEditorChanged(int editorId);
signals:
    void    colorChanged(QColor);
private:
    QMap<int, AbstractColorEditor*> m_editors;
    QColor                          m_color;
};

#endif // COLOREDITOR_HPP
