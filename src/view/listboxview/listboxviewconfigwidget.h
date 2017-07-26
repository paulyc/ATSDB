/*
 * ListBoxViewConfigWidget.h
 *
 *  Created on: Nov 11, 2012
 *      Author: sk
 */

#ifndef LISTBOXVIEWCONFIGWIDGET_H_
#define LISTBOXVIEWCONFIGWIDGET_H_

#include <QWidget>
#include "dbovariable.h"

class DBOVariableOrderedSetWidget;
class QCheckBox;
class ListBoxView;
class QLineEdit;

/**
 * @brief Widget with configuration elements for a ListBoxView
 *
 */
class ListBoxViewConfigWidget : public QWidget
{
    Q_OBJECT

public slots:
    void toggleUsePresentation();
    void toggleUseOverwrite();
    /// @brief Called when database view checkbox is un/checked
    //void toggleDatabaseView ();
    void exportSlot();

signals:
     void exportSignal ();

public:
    /// @brief Constructor
    ListBoxViewConfigWidget (ListBoxView* view, QWidget* parent=nullptr);
    /// @brief Destructor
    virtual ~ListBoxViewConfigWidget();

protected:
    /// Base view
    ListBoxView* view_;
    /// Variable read list widget
    DBOVariableOrderedSetWidget *variable_set_widget_;

    QCheckBox *presentation_check_;
    QCheckBox *overwrite_check_;
};

#endif /* LISTBOXVIEWCONFIGWIDGET_H_ */
