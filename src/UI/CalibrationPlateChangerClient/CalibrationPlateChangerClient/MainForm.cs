using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CalibrationPlateChangerClient {
    public partial class MainForm : Form {
        private List<Preset> m_PresetList;
        private List<Plate> m_CollimatorPlateList;
        private List<Plate> m_DrivePlateList;
        private PlateChangerAPI m_PlateChanger;

        public MainForm() {
            TESTgenerateTestData();
            InitializeComponent();
            m_PlateChanger = new PlateChangerAPI("10.0.2.2", 4244);
            UpdateUI(m_PresetList, m_CollimatorPlateList, m_DrivePlateList);
        }

        private void UpdateUI(List<Preset> presetList, List<Plate> collimatorPlateList, List<Plate> drivePlateList) {
            cbPresets.Items.Clear();
            lbCollimatorPlates.Items.Clear();
            lbDrivePlates.Items.Clear();
            foreach (Preset preset in presetList) {
                cbPresets.Items.Add(preset.GetName());
            }
            foreach (Plate plate in collimatorPlateList) {
                lbCollimatorPlates.Items.Add(plate.ToString());
            }
            foreach (Plate plate in drivePlateList) {
                lbDrivePlates.Items.Add(plate.ToString());
            }
        }

        private void btnEdit_Click(object sender, EventArgs e) {
            EditConfigForm editConfig = new EditConfigForm(ApplyUIChanges, MovePlateToCollimator, MovePlateToDrive, m_CollimatorPlateList, m_DrivePlateList);
            editConfig.ShowDialog();
        }

        private void btnShowPreset_Click(object sender, EventArgs e) {
            var selectedPreset = cbPresets.SelectedItem;
            if (selectedPreset == null) {
                MessageBox.Show("Please select a preset");
                return;
            }
            foreach (Preset preset in m_PresetList) {
                if (preset.GetName() == selectedPreset.ToString()) {
                    PresetForm presetForm = new PresetForm(preset);
                    presetForm.ShowDialog();
                }
            }
        }

        private void TESTgenerateTestData() {
            m_CollimatorPlateList = new List<Plate>();
            m_DrivePlateList = new List<Plate>();
            m_DrivePlateList.Add(new Plate(1, "Lead", 2.5));
            m_DrivePlateList.Add(new Plate(2, "Lead", 5));
            m_DrivePlateList.Add(new Plate(3, "Alluminium", 3.1));
            m_DrivePlateList.Add(new Plate(4, "Nothing", 2));
            m_DrivePlateList.Add(new Plate(5, "Copper", 0.5));
            m_DrivePlateList.Add(new Plate(6, "Copper", 1));
            m_DrivePlateList.Add(new Plate(7, "A lot", 1.25));
            m_PresetList = new List<Preset>();
            List<Plate> preset1Plates = new List<Plate>();
            preset1Plates.Add(m_DrivePlateList[0]);
            preset1Plates.Add(m_DrivePlateList[2]);
            preset1Plates.Add(m_DrivePlateList[3]);
            List<Plate> preset2Plates = new List<Plate>();
            preset2Plates.Add(m_DrivePlateList[1]);
            preset2Plates.Add(m_DrivePlateList[2]);
            preset2Plates.Add(m_DrivePlateList[5]);
            List<Plate> preset3Plates = new List<Plate>();
            preset3Plates.Add(m_DrivePlateList[0]);
            preset3Plates.Add(m_DrivePlateList[1]);
            preset3Plates.Add(m_DrivePlateList[4]);
            m_PresetList.Add(new Preset(1, "Preset 1", preset1Plates));
            m_PresetList.Add(new Preset(2, "Preset 2", preset2Plates));
            m_PresetList.Add(new Preset(3, "Preset 3", preset3Plates));
        }

        private void btnLoadPreset_Click(object sender, EventArgs e) {
            var selectedPreset = cbPresets.SelectedItem;
            if (selectedPreset == null) {
                MessageBox.Show("Please select a preset");
                return;
            }
            foreach(Preset preset in m_PresetList) {
                if (preset.GetName() == selectedPreset.ToString()) {
                    m_PlateChanger.SetPreset(preset.GetID());
                    m_DrivePlateList.AddRange(m_CollimatorPlateList);
                    m_CollimatorPlateList.Clear();
                    foreach (Plate plate in preset.GetPlates()) {
                        m_CollimatorPlateList.Add(plate);
                        m_DrivePlateList.Remove(plate);
                    }
                    UpdateUI(m_PresetList, m_CollimatorPlateList, m_DrivePlateList);
                    return;
                }
            }
            MessageBox.Show("Preset not available");
        }

        private void btnReset_Click(object sender, EventArgs e) {
            DialogResult result = MessageBox.Show("Are you sure you want to reset the system?", "Warning", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes) {
                int res = m_PlateChanger.ResetSystem();
                if (res == 0) {
                    m_DrivePlateList.AddRange(m_CollimatorPlateList);
                    m_CollimatorPlateList.Clear();
                    UpdateUI(m_PresetList, m_CollimatorPlateList, m_DrivePlateList);
                }
            }    
        }

        private int MovePlateToDrive(int plateId) {
            return m_PlateChanger.PlateToDrive(plateId);
        }

        private int MovePlateToCollimator(int plateId) {
            return m_PlateChanger.PlateToCollimator(plateId);
        }

        private int ApplyUIChanges(List<Plate> collimatorPlateList, List<Plate> driverPlateList) {
            if (collimatorPlateList == null || driverPlateList == null) {
                return -1;
            }
            m_CollimatorPlateList = collimatorPlateList;
            m_DrivePlateList = driverPlateList;
            UpdateUI(m_PresetList, m_CollimatorPlateList, m_DrivePlateList);
            return 0;
        }

        private void btnCancelOperation_Click(object sender, EventArgs e) {
            int result = m_PlateChanger.CancelCurrentOperation();
            if (result != 0) {
                MessageBox.Show("Error cancelling operation");
            }
        }

        private void btnEmergencyStop_Click(object sender, EventArgs e) {
            int result = m_PlateChanger.EmergencyStop();
            if (result != 0) {
                MessageBox.Show("Cannot go in emergency mode");
            }
        }

        private void btnContinueSystem_Click(object sender, EventArgs e) {
            int result = m_PlateChanger.ContinueSystem();
            if (result != 0) {
                MessageBox.Show("Cannot continue system");
            }
        }
    }
}
