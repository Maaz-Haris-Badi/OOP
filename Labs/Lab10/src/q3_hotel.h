#include <iostream>

class HotelRoom {
protected:

    int m_bedrooms;
    int m_bathrooms;

public:

    HotelRoom(int bedrooms, int bathrooms);
    int         getBedrooms() const;
    int         getBathrooms() const;
    virtual int get_price() const;
    virtual ~HotelRoom();
};

class HotelApartment : public HotelRoom {
public:

    HotelApartment(int bedrooms, int bathrooms);
    int get_price() const override;
    virtual ~HotelApartment() override;
};

HotelRoom::HotelRoom(int bedrooms, int bathrooms)
    : m_bedrooms(bedrooms), m_bathrooms(bathrooms) {}

int HotelRoom::getBedrooms() const { return m_bedrooms; }

int HotelRoom::getBathrooms() const { return m_bathrooms; }

int HotelRoom::get_price() const {
    return (50 * m_bedrooms) + (100 * m_bathrooms);
}

HotelRoom::~HotelRoom() {}

HotelApartment::HotelApartment(int bedrooms, int bathrooms)
    : HotelRoom(bedrooms, bathrooms) {}

int HotelApartment::get_price() const { return HotelRoom::get_price() + 100; }

HotelApartment::~HotelApartment() {}