using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CalibrationPlateChangerClient
{
    public partial class EditConfigForm : Form
    {
        private List<Plate> m_CollimatorPlateList, m_DrivePlateList;
        private Func<int, int> m_ToCollimator, m_ToDrive;

        public EditConfigForm(Func<int, int> toCollimator, Func<int, int> toDrive, List<Plate> collimatorPlateList, List<Plate> drivePlateList)
        {
            m_CollimatorPlateList = collimatorPlateList;
            m_DrivePlateList = drivePlateList;
            m_ToCollimator = toCollimator;
            m_ToDrive = toDrive;
            InitializeComponent();
            UpdateUI(m_CollimatorPlateList, m_DrivePlateList);
        }

        public void SetCollimatorPlateList(List<Plate> collimatorPlateList)
        {
            m_CollimatorPlateList = collimatorPlateList;
            UpdateUI(m_CollimatorPlateList, m_DrivePlateList);
        }
       
        public void SetDrivePlateList(List<Plate> drivePlateList)
        {
            m_DrivePlateList = drivePlateList;
            UpdateUI(m_CollimatorPlateList, m_DrivePlateList);
        }



        private void UpdateUI(List<Plate> collimatorPlateList, List<Plate> drivePlateList)
        {
            if (collimatorPlateList == null || drivePlateList == null)
            {
                MessageBox.Show("No plate list(s) available.");
                return;
            }
            lbCollimator.Items.Clear();
            lbDrive.Items.Clear();
            foreach (Plate plate in collimatorPlateList) {
                lbCollimator.Items.Add(plate.ToString());
            }
            foreach(Plate plate in drivePlateList) {
                lbDrive.Items.Add(plate.ToString());
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnMoveToDrive_Click(object sender, EventArgs e)
        {
            var selectedPlate = lbCollimator.SelectedItem;
            Plate plateToChange = null;
            if (selectedPlate == null)
            {
                MessageBox.Show("Please select a plate in the collimator list.");
                return;
            }
            foreach(Plate plate in m_CollimatorPlateList)
            {
                if (plate.ToString() == selectedPlate.ToString())
                    plateToChange = plate;
            }
            if (plateToChange != null)
            {
                int result = m_ToDrive(plateToChange.GetID());
                if (result != 0)
                {
                    return;
                }
            }
        }

        private void btnMoveToCollimator_Click(object sender, EventArgs e)
        {
            var selectedPlate = lbDrive.SelectedItem;
            Plate plateToChange = null;
            if (selectedPlate == null)
            {
                MessageBox.Show("Please select a plate in the drive list.");
                return;
            }
            foreach (Plate plate in m_DrivePlateList)
            {
                if (plate.ToString() == selectedPlate.ToString())
                    plateToChange = plate;
            }
            if (plateToChange != null)
            {
                int result = m_ToCollimator(plateToChange.GetID());
                if (result != 0)
                {
                    return;
                }
            }
        }
    }
}
