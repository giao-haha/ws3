#include <iostream>
#include "cstr.h"
#include "CC.h"
using namespace std;
namespace seneca {
    CC::CC() : m_name(nullptr), m_number(0), m_cvv(0), m_expMon(0), m_expYear(0) {}

    CC::~CC() {
        cleanUp();
    }

    void CC::set() {
        cleanUp();
    }

    void CC::cleanUp() {
        freeMem(m_name);
        m_number = 0;
        m_cvv = 0;
        m_expMon = 0;
        m_expYear = 0;
    }

    bool CC::isEmpty() const {
        return m_name == nullptr;
    }

    bool CC::validate(const char* name, unsigned long long cardNo, short cvv, short expMon, short expYear) const {
        return name && strlen(name) > 2 &&
            cardNo >= 4000000000000000ull && cardNo <= 4099999999999999ull &&
            cvv >= 100 && cvv <= 999 &&
            expMon >= 1 && expMon <= 12 &&
            expYear >= 24 && expYear <= 32;
    }

    void CC::prnNumber(unsigned long long no) const {
        cout << no / 1000000000000ull << " ";
        no %= 1000000000000ull;
        cout.fill('0');
        cout.width(4);
        cout.setf(ios::right);
        cout << no / 100000000ull << " ";
        no %= 100000000ull;
        cout.width(4);
        cout << no / 10000ull << " ";
        no %= 10000ull;
        cout.width(4);
        cout << no;
        cout.unsetf(ios::right);
        cout.fill(' ');
    }

    void CC::display(const char* name, unsigned long long number, short expYear, short expMon, short cvv) const {
        char lname[31]{};
        strcpy(lname, name, 30);
        cout << "| ";
        cout.width(30);
        cout.fill(' ');
        cout.setf(ios::left);
        cout << lname << " | ";
        prnNumber(number);
        cout << " | " << cvv << " | ";
        cout.unsetf(ios::left);
        cout.setf(ios::right);
        cout.width(2);
        cout << expMon << "/" << expYear << " |" << endl;
        cout.unsetf(ios::right);
    }

    void CC::set(const char* cc_name, unsigned long long cc_no, short cvv, short expMon, short expYear) {
        cleanUp();
        if (validate(cc_name, cc_no, cvv, expMon, expYear)) {
            alocpy(m_name, cc_name);
            m_number = cc_no;
            m_cvv = cvv;
            m_expMon = expMon;
            m_expYear = expYear;
        }
    }

    void CC::display() const {
        if (isEmpty()) {
            cout << "Invalid Credit Card Record" << endl;
        }
        else {
            display(m_name, m_number, m_expYear, m_expMon, m_cvv);
        }
    }
}