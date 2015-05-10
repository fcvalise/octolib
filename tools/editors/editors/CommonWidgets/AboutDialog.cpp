#include "AboutDialog.hpp"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QFont>

AboutDialog::AboutDialog(QPixmap const& appIcon, QWidget* parent) :
    QDialog(parent)
{
    QFormLayout*    infoLayout = new QFormLayout(this);
    QHBoxLayout*    titleLayout = new QHBoxLayout;
    QLabel*         appIconLabel = new QLabel;
    QLabel*         appNameLabel = new QLabel(QApplication::applicationDisplayName());
    QFrame*         line = new QFrame;
    QFont           font;

    font.setPointSize(40);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    appIconLabel->setPixmap(appIcon);
    titleLayout->addWidget(appIconLabel);
    titleLayout->addWidget(appNameLabel, 4);
    appNameLabel->setFont(font);
    infoLayout->addRow(titleLayout);
    infoLayout->addWidget(line);
    infoLayout->addRow(tr("Version:"), new QLabel(QApplication::applicationVersion()));
    infoLayout->addRow(tr("Compilation date:"), new QLabel(__DATE__));
    infoLayout->addRow(tr("Compilation time:"), new QLabel(__TIME__));
}

AboutDialog::~AboutDialog()
{
}

