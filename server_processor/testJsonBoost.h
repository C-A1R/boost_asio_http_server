#pragma once

#include <boost/property_tree/json_parser.hpp>

#include <iostream>

namespace TestJsonBoost
{

using boost::property_tree::ptree;

struct TestJsonB
{
    std::string FirstName;
    std::string LastName;
    int Age = 0;
    struct Address
    {
        std::string Street;
        std::string City;
        std::string Country;
        void read(const ptree &root)
        {
            if (root.count("Street") > 0)
                Street = root.get<std::string>("Street");
            if (root.count("City") > 0)
                City = root.get<std::string>("City");
            if (root.count("Country") > 0)
                Country = root.get<std::string>("Country");
        }
        ptree write() const
        {
            ptree root;
            root.put("Street", Street);
            root.put("City", City);
            root.put("Country", Country);
            return  root;
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

    void read(const ptree &root)
    {
        if (root.count("FirstName") > 0)
            FirstName = root.get<std::string>("FirstName");
        if (root.count("LastName") > 0)
            LastName = root.get<std::string>("LastName");
        if (root.count("Age") > 0)
            Age = root.get<int>("Age");

        if (root.count("Address1") > 0)
            m_Address1.read(root.get_child("Address1"));
        if (root.count("Address2") > 0)
            m_Address2.read(root.get_child("Address2"));
        if (root.count("Address3") > 0)
            m_Address3.read(root.get_child("Address3"));
        if (root.count("Address4") > 0)
            m_Address4.read(root.get_child("Address4"));
        if (root.count("Address5") > 0)
            m_Address5.read(root.get_child("Address5"));
        if (root.count("Address6") > 0)
            m_Address6.read(root.get_child("Address6"));
        if (root.count("Address7") > 0)
            m_Address7.read(root.get_child("Address7"));
        if (root.count("Address8") > 0)
            m_Address8.read(root.get_child("Address8"));
        if (root.count("Address9") > 0)
            m_Address9.read(root.get_child("Address9"));
        if (root.count("Address10") > 0)
            m_Address10.read(root.get_child("Address10"));
    }
    ptree write() const
    {
        ptree root;
        root.add_child("Address1", m_Address1.write());
        root.add_child("Address2", m_Address2.write());
        root.add_child("Address3", m_Address3.write());
        root.add_child("Address4", m_Address4.write());
        root.add_child("Address5", m_Address5.write());
        root.add_child("Address6", m_Address6.write());
        root.add_child("Address7", m_Address7.write());
        root.add_child("Address8", m_Address8.write());
        root.add_child("Address9", m_Address9.write());
        root.add_child("Address10", m_Address10.write());
        root.put("FirstName", FirstName);
        root.put("LastName", LastName);
        root.put("Age", Age);
        return root;
    }
};

std::string TestJson(const std::string &body, bool &ok)
{
    ptree request_root;
    std::stringstream request_stream(body);
    try
    {
        boost::property_tree::read_json(request_stream, request_root);
    }
    catch (std::exception& e)
    {
        ok = false;
        std::cerr << "ERR invalid json: " << e.what() << std::endl;
        return "Invalid json:\n" + std::string(e.what()) + '\n' + body;
    }

    TestJsonB testJsonB;
    testJsonB.read(request_root);

    ptree response_root = testJsonB.write();
    std::stringstream response_stream;
    boost::property_tree::write_json(response_stream, response_root);
    return response_stream.str();
}

}
