#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

enum SubsysType
{
  SUB_ARMAMENT,
  SUB_ENGINE,
  SUB_SHIELD,
  SUB_SENSOR,
  SUB_CARGO,
  SUB_QUARTERS,
  SUB_INFIRMARY,
  SUB_SECURITY
};

class Subsystem
{
  private:
    int _type;

    int _x, _y;
    int _w, _h;

    int _weight;
    int _maxIntegrity;
    int _integrity;
    int _powerDrain;

  public:
    Subsystem(SubsysType type, int x, int y, int w, int h,
        int weight, int maxIntegrity, int powerDrain);

    const int GetType() const { return _type; }
    const int GetX() const { return _x; }
    const int GetY() const { return _y; }
    const int GetSize() const { return _x * _y; }
    const int GetWeight() const { return _weight; }
    const int GetMaxIntegrity() const { return _maxIntegrity; }
    const int GetIntegrity() const { return _integrity; }
    const int GetPowerDrain() const { return _powerDrain; }

    void SetIntegrity(int integrity) { _integrity = integrity; }
    void SetPowerDrain(int powerDrain) { _powerDrain = powerDrain; }
};

#endif
