#include <string>

using namespace std;

class sphere{
public:
    sphere();
    sphere(const sphere & orig);
    
private:
    double theRadius;
    int numAtts;
    string * atts;
};