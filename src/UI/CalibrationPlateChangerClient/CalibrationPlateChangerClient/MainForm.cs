using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace CalibrationPlateChangerClient
{
    public partial class MainForm : Form
    {
        private Func<ApiFunction, int> m_sendRequestFunction;
        private ApiFunctionBuilder m_Api;
        private EditConfigForm m_EditConfigForm;
        private List<Preset> m_PresetList;
        private List<Plate> m_CollimatorPlateList;
        private List<Plate> m_DrivePlateList;

        public MainForm(Func<ApiFunction, int> sendRequestFunction)
        {
            this.m_sendRequestFunction = sendRequestFunction;
            m_Api = new ApiFunctionBuilder();
            InitializeComponent();
        }

        public void LogMessage(string message)
        {
            lbLog.Items.Add(DateTime.Now.ToLocalTime() + ": " + message);
        }

        public void LogFromAnotherThread(string message)
        {
            lbLog.BeginInvoke((MethodInvoker)delegate () 
            {
                lbLog.Items.Add(DateTime.Now.ToLocalTime() + ": " + message);
            });
        }

        public void SetCollimatorPlateList(List<Plate> collimatorPlateList)
        {
            m_CollimatorPlateList = collimatorPlateList;
            lbCollimatorPlates.Items.Clear();
            foreach(Plate plate in m_CollimatorPlateList)
            {
                lbCollimatorPlates.Items.Add(plate.ToString());
            }
            if (m_EditConfigForm != null)
            {
                m_EditConfigForm.SetCollimatorPlateList(m_CollimatorPlateList);
            }
        }

        public void SetDriverPlateList(List<Plate> driverPlateList)
        {
            m_DrivePlateList = driverPlateList;
            lbDrivePlates.Items.Clear();
            foreach(Plate plate in m_DrivePlateList)
            {
                lbDrivePlates.Items.Add(plate.ToString());
            }
            if (m_EditConfigForm != null)
            {
                m_EditConfigForm.SetDrivePlateList(m_DrivePlateList);
            }
        }

        public void SetPresetList(List<Preset> presetList)
        {
            m_PresetList = presetList;
            cbPresets.Items.Clear();
            foreach(Preset preset in presetList)
            {
                cbPresets.Items.Add(preset.GetName());
            }
        }



        private void btnCancelOperation_Click(object sender, EventArgs e)
        {
            ApiFunction request = m_Api.CancelCurrentOperation();
            int result = m_sendRequestFunction(request);
            if (result == 0)
            {
                LogMessage("Cancel Operation request sent to server");
            }
            else
            {
                LogMessage("Sending Cancel Operation request failed");
            }
            return;
        }

        private void btnEmergencyStop_Click(object sender, EventArgs e)
        {
            ApiFunction request = m_Api.EmergencyStop();
            int result = m_sendRequestFunction(request);
            if (result == 0)
            {
                LogMessage("Emergency Stop request sent to server");
            }
            else
            {
                LogMessage("Sending Emergency Stop request failed");
            }
            return;
        }

        private void btnEdit_Click(object sender, EventArgs e)
        {
            m_EditConfigForm = new EditConfigForm(MovePlateToCollimator, MovePlateToDrive, m_CollimatorPlateList, m_DrivePlateList);
            m_EditConfigForm.ShowDialog();
            m_EditConfigForm.FormClosed += M_EditConfigForm_FormClosed;
        }

        private void M_EditConfigForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            m_EditConfigForm = null;
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            ApiFunction request = m_Api.ResetSystem();
            m_sendRequestFunction(request);
        }

        private int MovePlateToDrive(int plateId)
        {
            ApiFunction request = m_Api.PlateToDrive(plateId);
            int result = m_sendRequestFunction(request);
            if (result == 0)
            {
                LogMessage("Move (" + plateId + ") to Drive request sent to server");
            }
            else
            {
                LogMessage("Sending Move (" + plateId + ") to Drive request failed");
            }
            return result;
        }

        private int MovePlateToCollimator(int plateId)
        {
            ApiFunction request = m_Api.PlateToCollimator(plateId);
            int result = m_sendRequestFunction(request);
            if (result == 0)
            {
                LogMessage("Move (" + plateId + ") to Collimator request sent to server");
            }
            else
            {
                LogMessage("Sending Move (" + plateId + ") to Collimator request failed");
            }
            return result;
        }

        private void btnContinueSystem_Click(object sender, EventArgs e)
        {
            ApiFunction request = m_Api.ContinueSystem();
            int result = m_sendRequestFunction(request);
            if (result == 0)
            {
                LogMessage("Continue System request sent to server");
            }
            else
            {
                LogMessage("Sending Continue System request failed");
            }
            return;
        }

        private void btnShowPreset_Click(object sender, EventArgs e)
        {
            var selectedPreset = cbPresets.SelectedItem;
            if (selectedPreset == null)
            {
                MessageBox.Show("Please select a preset");
                return;
            }
            foreach (Preset preset in m_PresetList)
            {
                if (preset.GetName() == selectedPreset.ToString())
                {
                    PresetForm presetForm = new PresetForm(preset);
                    presetForm.ShowDialog();
                }
            }
        }

        private void btnLoadPreset_Click(object sender, EventArgs e)
        {
            var selectedPreset = cbPresets.SelectedItem;
            if (selectedPreset == null)
            {
                MessageBox.Show("Please select a preset");
                return;
            }
            foreach (Preset preset in m_PresetList)
            {
                if (preset.GetName() == selectedPreset.ToString())
                {
                    ApiFunction request = m_Api.SetPreset(preset.GetID());
                    int result = m_sendRequestFunction(request);
                    if (result == 0)
                    {
                        LogMessage("Set (" + preset.GetName() + ") request sent to server");
                    }
                    else
                    {
                        LogMessage("Sending Set (" + preset.GetName() + ") request failed");
                    }
                    return;
                }
            }
            MessageBox.Show("Preset not available");
        }
    }
}
