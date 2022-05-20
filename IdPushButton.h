//
// Created by Codes on 20/05/2022.
//

#ifndef BLOCCONOTE_IDPUSHBUTTON_H
#define BLOCCONOTE_IDPUSHBUTTON_H

#include <QtWidgets/QPushButton>
#include <iostream>

class IdPushButton : public QPushButton{
public:
    explicit IdPushButton(const QString& text, int id) : QPushButton(text), id(id){}

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return this->id;
    }

private:
    int id;

};


#endif //BLOCCONOTE_IDPUSHBUTTON_H
