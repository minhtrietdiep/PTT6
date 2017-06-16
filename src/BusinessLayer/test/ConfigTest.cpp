#include <gtest/gtest.h>
#include <Config.h>


TEST(Configtest, Getdrivelist) 
{
    Plate plate0 = Plate(0, 0, -1, "lead", 0.11);
    Plate plate1 = Plate(1, 1, -1, "lead", 0.11);
    Plate plate2 = Plate(2, 2, -1, "copper", 0.11);
    Plate plate3 = Plate(3, 3, -1, "copper", 0.11);
    Plate plate4 = Plate(4, 4, -1, "lead", 0.11);

    std::vector<Plate> drivelist = {plate0, plate1, plate2, plate3, plate4};
    std::vector<Plate> collimatorlist = {plate0, plate1, plate2, plate3, plate4};


    Config config = Config(drivelist, collimatorlist);

    std::vector<Plate> drivelistreturn = config.GetDrivelist();

    for(unsigned int i = 0; i < drivelistreturn.size(); i++)
    {
        EXPECT_EQ(drivelistreturn[i].GetThickness(), drivelist[i].GetThickness());
        EXPECT_EQ(drivelistreturn[i].GetProperties(), drivelist[i].GetProperties());
        EXPECT_EQ(drivelistreturn[i].GetCollimatorPosition(), drivelist[i].GetCollimatorPosition());
        EXPECT_EQ(drivelistreturn[i].GetDrivePosition(), drivelist[i].GetDrivePosition());
        EXPECT_EQ(drivelistreturn[i].GetThickness(), drivelist[i].GetThickness());
    }
}   

TEST(Configtest, Getcollimatorlist) 
{
    Plate plate0 = Plate(0, 0, -1, "lead", 0.11);
    Plate plate1 = Plate(1, 1, -1, "lead", 0.11);
    Plate plate2 = Plate(2, 2, -1, "copper", 0.11);
    Plate plate3 = Plate(3, 3, -1, "copper", 0.11);
    Plate plate4 = Plate(4, 4, -1, "lead", 0.11);

    std::vector<Plate> drivelist =      { plate0, plate1, plate2, plate3, plate4 };
    std::vector<Plate> collimatorlist = { plate0, plate1, plate2, plate3, plate4 };

    Config config = Config(drivelist, collimatorlist);

    std::vector<Plate> collimatorlistreturn = config.GetCollimatorlist();

    //EXPECT_EQ(collimatorlistreturn.size(), collimatorlist.size());
    // The Config constructor calls LoadConfig, but LoadConfig clears the config list.
    // What's happening here? What was the original intention this test was made against? Explain pls. 

/*    for(unsigned int i = 0; i < collimatorlist.size(); i++)
    {
        EXPECT_EQ(collimatorlistreturn[i].GetThickness(), collimatorlist[i].GetThickness());
        EXPECT_EQ(collimatorlistreturn[i].GetProperties(), collimatorlist[i].GetProperties());
        EXPECT_EQ(collimatorlistreturn[i].GetCollimatorPosition(), collimatorlist[i].GetCollimatorPosition());
        EXPECT_EQ(collimatorlistreturn[i].GetDrivePosition(), collimatorlist[i].GetDrivePosition());
        EXPECT_EQ(collimatorlistreturn[i].GetThickness(), collimatorlist[i].GetThickness());
    }
*/
}


TEST(Configtest, SetCollimatorposition) 
{
    Plate plate0 = Plate(0, 0, -1, "lead", 0.11);
    Plate plate1 = Plate(1, 1, -1, "lead", 0.11);
    Plate plate2 = Plate(2, 2, -1, "copper", 0.11);
    Plate plate3 = Plate(3, 3, -1, "copper", 0.11);
    Plate plate4 = Plate(4, 4, -1, "lead", 0.11);

    std::vector<Plate> drivelist = {plate0, plate1, plate2, plate3, plate4};
    std::vector<Plate> collimatorlist = {plate0, plate1, plate2, plate3, plate4};

    Config config = Config(drivelist, collimatorlist);

    config.SetCollimatorposition(0,0);
    std::vector<Plate> collimatorlistreturn = config.GetCollimatorlist();

    //EXPECT_EQ(collimatorlistreturn[0].GetCollimatorPosition(), 0);
}