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

class Ui_DeltaUi
{
public:
    QPushButton *getImage;
    QPushButton *runDrawing;
    QGraphicsView *Whole;
    QGraphicsView *Face;

    void setupUi(QWidget *DeltaUi)
    {
        if (DeltaUi->objectName().isEmpty())
            DeltaUi->setObjectName(QStringLiteral("DeltaUi"));
        DeltaUi->resize(1069, 660);
        getImage = new QPushButton(DeltaUi);
        getImage->setObjectName(QStringLiteral("getImage"));
        getImage->setGeometry(QRect(250, 440, 151, 81));
        runDrawing = new QPushButton(DeltaUi);
        runDrawing->setObjectName(QStringLiteral("runDrawing"));
        runDrawing->setGeometry(QRect(650, 440, 151, 81));
        Whole = new QGraphicsView(DeltaUi);
        Whole->setObjectName(QStringLiteral("Whole"));
        Whole->setGeometry(QRect(90, 70, 431, 291));
        Face = new QGraphicsView(DeltaUi);
        Face->setObjectName(QStringLiteral("Face"));
        Face->setGeometry(QRect(550, 70, 431, 291));

        retranslateUi(DeltaUi);

        QMetaObject::connectSlotsByName(DeltaUi);
    } // setupUi

    void retranslateUi(QWidget *DeltaUi)
    {
        DeltaUi->setWindowTitle(QApplication::translate("DeltaUi", "Form", Q_NULLPTR));
        getImage->setText(QApplication::translate("DeltaUi", "get Image", Q_NULLPTR));
        runDrawing->setText(QApplication::translate("DeltaUi", "runDrawing", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DeltaUi: public Ui_DeltaUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELTA_H
