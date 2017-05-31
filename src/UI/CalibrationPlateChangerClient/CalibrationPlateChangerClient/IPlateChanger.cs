
namespace CalibrationPlateChangerClient
{
    /// <summary>
    /// These functions are provided by the server
    /// </summary>
    interface IPlateChanger
    {
        ApiFunction PlateToDrive(int plateID);
        ApiFunction PlateToCollimator(int plateID);
        ApiFunction SetPreset(int presetID);
        ApiFunction CancelCurrentOperation();
        ApiFunction EmergencyStop();
        ApiFunction ContinueSystem();
        ApiFunction ResetSystem();
        ApiFunction UploadPresets();
        ApiFunction UploadDriveState();
        ApiFunction UploadCollimatorState();
    }
}
