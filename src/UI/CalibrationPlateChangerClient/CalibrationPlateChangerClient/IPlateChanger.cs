
namespace CalibrationPlateChangerClient
{
    interface IPlateChanger
    {
        ApiFunction PlateToDrive(int plateID);
        ApiFunction PlateToCollimator(int plateID);
        ApiFunction SetPreset(int presetID);
        ApiFunction CancelCurrentOperation();
        ApiFunction EmergencyStop();
        ApiFunction ContinueSystem();
        ApiFunction ResetSystem();
        ApiFunction UploadConfig(/*TBD*/);
        ApiFunction DownloadConfig();
    }
}
