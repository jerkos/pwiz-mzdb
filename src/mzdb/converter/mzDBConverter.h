#ifndef __MZDBCONVERTER__
#define __MZDBCONVERTER__

#include "pwiz/data/msdata/MSDataFile.hpp"
#include "../reader/mzDBReader.h"
#include "stdlib.h"

namespace mzdb {

using namespace std;


struct PWIZ_API_DECL mzConverter {

    enum FileFormat {
        MZ_XML,
        MZ_DATA,
        MZ_ML,
        MZ5
    };


    /*inline static double unifRand(double a, double b) {
        return (b - a)*(rand() / double(RAND_MAX)) + a;
    }*/

    class UserFeedbackIterationListener : public pwiz::util::IterationListener
    {
        public:

        virtual Status update(const UpdateMessage& updateMessage)
        {
            // add tabs to erase all of the previous line
            cout << updateMessage.iterationIndex+1 << "/" << updateMessage.iterationCount << "\t\t\t\r" << flush;

            // spectrum and chromatogram lists both iterate; put them on different lines
            if (updateMessage.iterationIndex+1 == updateMessage.iterationCount)
                cout << endl;
            return pwiz::util::IterationListener::Status_Ok;
        }
    };

    string destination;
    MzDBFile* _mzdb;

    mzDBReader* mzdbReader;
    pwiz::msdata::MSData msd;



    PWIZ_API_DECL mzConverter( MzDBFile* mzdb);
    PWIZ_API_DECL ~mzConverter();

    PWIZ_API_DECL void convert(bool noLoss = false, FileFormat = MZ_XML);

    //
    //PWIZ_API_DECL void regionExtractorPwizImpl(const MSDataFile& msdata, const string& filename, double minmz, double maxmz, double minrt, double maxrt) const;
    //PWIZ_API_DECL void xicExtractorPwizImpl(const MSDataFile& msdata, const string& filename,  double mz, double radius) const;


    //mzdb specialized functions for tests purposes
    PWIZ_API_DECL void enumerateSpectra();
   // PWIZ_API_DECL void rtreeRequest();

};

}//end namespace

#endif 
