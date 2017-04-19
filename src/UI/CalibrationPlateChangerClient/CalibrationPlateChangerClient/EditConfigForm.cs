using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CalibrationPlateChangerClient {
    public partial class EditConfigForm : Form {
        private List<Plate> m_CollimatorPlateList, m_DrivePlateList;
        private Func<List<Plate>, List<Plate>, int> m_UpdateMainUI;
        private Func<int, int> m_ToCollimator, m_ToDrive;

        public EditConfigForm(Func<List<Plate>, List<Plate>, int> updateMainUI, Func<int, int> toCollimator, Func<int, int> toDrive, List<Plate> collimatorPlateList, List<Plate> drivePlateList) {
            m_CollimatorPlateList = collimatorPlateList;
            m_DrivePlateList = drivePlateList;
            m_UpdateMainUI = updateMainUI;
            m_ToCollimator = toCollimator;
            m_ToDrive = toDrive;
            InitializeComponent();
            UpdateUI(m_CollimatorPlateList, m_DrivePlateList);
        }

        private void UpdateUI(List<Plate> collimatorPlateList, List<Plate> drivePlateList) {
            lbCollimator.Items.Clear();
            lbDrive.Items.Clear();
            foreach (Plate plate in collimatorPlateList) {
                lbCollimator.Items.Add(plate.ToString());
            }
            foreach(Plate plate in drivePlateList) {
                lbDrive.Items.Add(plate.ToString());
            }
        }

        private void btnClose_Click(object sender, EventArgs e) {
            int result = m_UpdateMainUI(m_CollimatorPlateList, m_DrivePlateList);
            if (result != 0) {
                MessageBox.Show("Error, cannot update user interface!");
                return;
            }
            this.Close();
        }

        private void btnMoveToDrive_Click(object sender, EventArgs e) {
            var selectedPlate = lbCollimator.SelectedItem;
            Plate plateToChange = null;
            if (selectedPlate == null) {
                MessageBox.Show("Please select a plate in the collimator list.");
                return;
            }
            foreach(Plate plate in m_CollimatorPlateList) {
                if (plate.ToString() == selectedPlate.ToString())
                    plateToChange = plate;
            }
            if (plateToChange != null) {
                int result = m_ToDrive(plateToChange.GetID());
                if (result != 0) {
                    MessageBox.Show("Moving plate failed!");
                    return;
                }
                MessageBox.Show("Moving plate...");
                m_CollimatorPlateList.Remove(plateToChange);
                m_DrivePlateList.Add(plateToChange);
                UpdateUI(m_CollimatorPlateList, m_DrivePlateList);
            }
        }

        private void btnMoveToCollimator_Click(object sender, EventArgs e) {
            var selectedPlate = lbDrive.SelectedItem;
            Plate plateToChange = null;
            if (selectedPlate == null) {
                MessageBox.Show("Please select a plate in the drive list.");
                return;
            }
            foreach (Plate plate in m_DrivePlateList) {
                if (plate.ToString() == selectedPlate.ToString())
                    plateToChange = plate;
            }
            if (plateToChange != null) {
                int result = m_ToCollimator(plateToChange.GetID());
                if (result != 0) {
                    MessageBox.Show("Moving plate failed!");
                    return;
                }
                MessageBox.Show("Moving plate...");
                m_DrivePlateList.Remove(plateToChange);
                m_CollimatorPlateList.Add(plateToChange);
                UpdateUI(m_CollimatorPlateList, m_DrivePlateList);
            }
        }

        private void btnApply_Click(object sender, EventArgs e) {

        }

    }
}
