#include "TapeInterface.h"

class Tape : public TapeInterface {
private:

    ConfigurationProperties properties_;

public:

    Tape(const ConfigurationProperties& properties);

    void StartSorting();

};