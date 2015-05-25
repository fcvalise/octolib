#include "AboutDialog.hpp"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QFont>

namespace
{
    QLabel* createLabel(QString const& text)
    {
        QLabel* label = new QLabel(text);

        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        return (label);
    }
}
AboutDialog::AboutDialog(QPixmap const& appIcon, QWidget* parent) :
    QDialog(parent)
{
    QFormLayout*    infoLayout = new QFormLayout(this);
    QHBoxLayout*    titleLayout = new QHBoxLayout;
    QLabel*         appIconLabel = new QLabel;
    QLabel*         appNameLabel = new QLabel(QApplication::applicationDisplayName());
    QFrame*         line = new QFrame;
    QFont           font;
    QString         version = QApplication::applicationVersion();

#if (defined GIT_BRANCH && defined GIT_COMMIT_SHORT)
    version += QString(" %0-%1").arg(GIT_BRANCH).arg(GIT_COMMIT_SHORT);
#endif
#if !defined NDEBUG
    version += " [DEBUG]";
#endif
    font.setPointSize(40);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    appIconLabel->setPixmap(appIcon);
    titleLayout->addWidget(appIconLabel);
    titleLayout->addWidget(appNameLabel, 4);
    appNameLabel->setFont(font);
    infoLayout->addRow(titleLayout);
    infoLayout->addWidget(line);
    infoLayout->addRow(tr("Version:"), createLabel(version));
    infoLayout->addRow(tr("Compilation date:"), createLabel(__DATE__));
    infoLayout->addRow(tr("Compilation time:"), createLabel(__TIME__));
}

AboutDialog::~AboutDialog()
{
}

