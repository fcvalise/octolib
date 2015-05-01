#ifndef ADDOFFSETSDIALOG_HPP
#define ADDOFFSETSDIALOG_HPP

#include <QDialog>

namespace Ui {
class AddOffsetsDialog;
}

class AddOffsetsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOffsetsDialog(QWidget *parent = 0);
    ~AddOffsetsDialog();

    quint16 getInitial()const;
    int     getCount()const;
    qint16  getInterval()const;
private:
    Ui::AddOffsetsDialog *ui;
};

#endif // ADDOFFSETSDIALOG_HPP
