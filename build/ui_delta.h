/********************************************************************************
** Form generated from reading UI file 'delta.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELTA_H
#define UI_DELTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Delta
{
public:
    QPushButton *getImage;
    QPushButton *runDrawing;
    QGraphicsView *picture;

    void setupUi(QWidget *DeltaUi)
    {
        if (DeltaUi->objectName().isEmpty())
            DeltaUi->setObjectName(QStringLiteral("DeltaUi"));
        DeltaUi->resize(811, 501);
        getImage = new QPushButton(DeltaUi);
        getImage->setObjectName(QStringLiteral("getImage"));
        getImage->setGeometry(QRect(180, 380, 151, 81));
        runDrawing = new QPushButton(DeltaUi);
        runDrawing->setObjectName(QStringLiteral("runDrawing"));
        runDrawing->setGeometry(QRect(480, 380, 151, 81));
        picture = new QGraphicsView(DeltaUi);
        picture->setObjectName(QStringLiteral("picture"));
        picture->setGeometry(QRect(180, 40, 451, 321));

        retranslateUi(DeltaUi);

        QMetaObject::connectSlotsByName(DeltaUi);
    } // setupUi

    void retranslateUi(QWidget *DeltaUi)
    {
        DeltaUi->setWindowTitle(QApplication::translate("Delta", "Form", Q_NULLPTR));
        getImage->setText(QApplication::translate("Delta", "get Image", Q_NULLPTR));
        runDrawing->setText(QApplication::translate("Delta", "runDrawing", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Delta: public Ui_Delta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELTA_H
