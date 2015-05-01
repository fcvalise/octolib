#ifndef ABOUTDIALOG_HPP
#define ABOUTDIALOG_HPP

#include <QDialog>

class AboutDialog : public QDialog
{
public:
    explicit AboutDialog(const QPixmap &appIcon, QWidget* parent = nullptr);
    ~AboutDialog();
};

#endif // ABOUTDIALOG_HPP
