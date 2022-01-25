#ifndef CJOINT_H
#define CJOINT_H

class CJoint{

    private:
        double m_dMinAngleRad;
        double m_dMaxAngleRad;

    public:
        inline          CJoint(double dMinRad, double dMaxRad):
            m_dMinAngleRad(dMinRad),
            m_dMaxAngleRad(dMaxRad)
        {}

        inline bool     isInRange(double dAngleRad){
            if(dAngleRad <= m_dMaxAngleRad && dAngleRad >= m_dMinAngleRad){
                return true;
            }else{
                return false;
            }
        }
};

#endif // CJOINT_H
