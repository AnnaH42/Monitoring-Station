#include "listitemwidget.h"

ListItemWidget::ListItemWidget(const QString &text, const QString &position, QWidget *parent)
    : QWidget(parent), itemText(text)
{

    QLabel *nameLabel = new QLabel(text);
    QLabel *positionLabel = new QLabel("Position: " + position);
    buttonOver = new QPushButton("Overtaking");
    buttonStop = new QPushButton("Stop");

    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->addWidget(nameLabel);
    textLayout->addWidget(positionLabel);
    textLayout->setSpacing(2);
    textLayout->setContentsMargins(0, 0, 0, 0);

    auto *layout = new QHBoxLayout(this);
    layout->addLayout(textLayout);
    layout->addStretch();
    layout->addWidget(buttonOver);
    layout->addWidget(buttonStop);


    layout->setContentsMargins(10, 8, 10, 8); // spacing around the content

    this->setMinimumHeight(70); // <-- Make items taller

    connect(buttonOver, &QPushButton::clicked, this, &ListItemWidget::handleButtonClick);
    connect(buttonStop, &QPushButton::clicked, this, &ListItemWidget::handleButtonClickStop);
}

void ListItemWidget::handleButtonClick() {
    emit buttonClicked(itemText);
}

void ListItemWidget::handleButtonClickStop() {
    emit buttonClickedStop(itemText);
}

/*
 * void ListItemWidget::updateData(const QString &name, const QString &position) {
    nameLabel->setText(name);
    positionLabel->setText(position);
}*/

