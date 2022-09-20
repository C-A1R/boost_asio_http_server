#pragma once

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

namespace TestJsonQt
{

struct TestJsonQ
{
    QString FirstName;
    QString LastName;
    int Age;
    struct Address
    {
        QString Street;
        QString City;
        QString Country;
        void read(const QJsonObject &json)
        {
            if (json.contains("Street") && json["Street"].isString())
                Street = json["Street"].toString();
            if (json.contains("City") && json["City"].isString())
                City = json["City"].toString();
            if (json.contains("Country") && json["Country"].isString())
                Country = json["Country"].toString();
        }
        void write(QJsonObject &json) const
        {
            json["Street"] = Street;
            json["City"] = City;
            json["Country"] = Country;
        }
    };
    Address m_Address1;
    Address m_Address2;
    Address m_Address3;
    Address m_Address4;
    Address m_Address5;
    Address m_Address6;
    Address m_Address7;
    Address m_Address8;
    Address m_Address9;
    Address m_Address10;

    void read(const QJsonObject &json)
    {
        if (json.contains("FirstName") && json["FirstName"].isString())
            FirstName = json["FirstName"].toString();
        if (json.contains("LastName") && json["LastName"].isString())
            LastName = json["LastName"].toString();
        if (json.contains("Age") && json["Age"].isDouble())
            Age = json["Age"].toInt();
        if (json.contains("Address1") && json["Address1"].isObject())
            m_Address1.read(json["Address1"].toObject());
        if (json.contains("Address2") && json["Address2"].isObject())
            m_Address2.read(json["Address2"].toObject());
        if (json.contains("Address3") && json["Address3"].isObject())
            m_Address3.read(json["Address3"].toObject());
        if (json.contains("Address4") && json["Address4"].isObject())
            m_Address4.read(json["Address4"].toObject());
        if (json.contains("Address5") && json["Address5"].isObject())
            m_Address5.read(json["Address5"].toObject());
        if (json.contains("Address6") && json["Address6"].isObject())
            m_Address6.read(json["Address6"].toObject());
        if (json.contains("Address7") && json["Address7"].isObject())
            m_Address7.read(json["Address7"].toObject());
        if (json.contains("Address8") && json["Address8"].isObject())
            m_Address8.read(json["Address8"].toObject());
        if (json.contains("Address9") && json["Address9"].isObject())
            m_Address9.read(json["Address9"].toObject());
        if (json.contains("Address10") && json["Address10"].isObject())
            m_Address10.read(json["Address10"].toObject());
    }
    void write(QJsonObject &json) const
    {
        json["FirstName"] = FirstName;
        json["LastName"] = LastName;
        json["Age"] = Age;
        QJsonObject adressObject1;
        m_Address1.write(adressObject1);
        json["Address1"] = adressObject1;
        QJsonObject adressObject2;
        m_Address2.write(adressObject2);
        json["Address2"] = adressObject2;
        QJsonObject adressObject3;
        m_Address3.write(adressObject3);
        json["Address3"] = adressObject3;
        QJsonObject adressObject4;
        m_Address4.write(adressObject4);
        json["Address4"] = adressObject4;
        QJsonObject adressObject5;
        m_Address5.write(adressObject5);
        json["Address5"] = adressObject5;
        QJsonObject adressObject6;
        m_Address6.write(adressObject6);
        json["Address6"] = adressObject6;
        QJsonObject adressObject7;
        m_Address7.write(adressObject7);
        json["Address7"] = adressObject7;
        QJsonObject adressObject8;
        m_Address8.write(adressObject8);
        json["Address8"] = adressObject8;
        QJsonObject adressObject9;
        m_Address9.write(adressObject9);
        json["Address9"] = adressObject9;
        QJsonObject adressObject10;
        m_Address10.write(adressObject10);
        json["Address10"] = adressObject10;
    }
};

std::string TestJson(const std::string &body)
{
    QString qbody = body.c_str();
    QJsonDocument doc = QJsonDocument::fromJson(qbody.toUtf8());
    TestJsonQ testJsonQ;
    testJsonQ.read(doc.object());

    QJsonObject responseObject;
    testJsonQ.write(responseObject);
    QJsonDocument responseDoc(responseObject);
    return responseDoc.toJson().toStdString();
}

}
