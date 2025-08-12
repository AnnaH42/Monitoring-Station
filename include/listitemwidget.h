#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ListItemWidget : public QWidget {
    Q_OBJECT

public:
    explicit ListItemWidget(const QString &text, const QString &position, QWidget *parent = nullptr);

signals:
    void buttonClicked(const QString &text);
    void buttonClickedStop(const QString &text);

private slots:
    void handleButtonClick();
    void handleButtonClickStop();

private:
    QLabel *label;
    QPushButton *buttonOver;
    QString itemText;
    QPushButton *buttonStop;
};

#endif // LISTITEMWIDGET_H
