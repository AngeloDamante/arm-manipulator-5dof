#ifndef CLINK_H
#define CLINK_H

class CLink{
    private:
        double m_dLength;

    public:
        inline explicit     CLink(double dLength):m_dLength(dLength){}
        inline double       getLength() {return this->m_dLength;}
};

#endif // CLINK_H
