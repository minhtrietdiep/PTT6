
namespace CalibrationPlateChangerClient {
    interface IPlateChangerAPI {
        int PlateToDrive(int plateID);
        int PlateToCollimator(int plateID);
        int SetPreset(int presetID);
        int CancelCurrentOperation();
        int EmergencyStop();
        int ContinueSystem();
        int ResetSystem();
        int UploadConfig(/*TBD*/);
        int DownloadConfig();
    }
}
