using System.Collections.Generic;
using System.Windows.Forms;

namespace CalibrationPlateChangerClient
{
    public partial class PresetForm : Form
    {
        private Preset m_Preset;

        public PresetForm(Preset preset)
        {
            m_Preset = preset;
            InitializeComponent();
            ConfigureUI(m_Preset);
        }



        private void ConfigureUI(Preset preset)
        {
            lblPresetName.Text = preset.GetName();
            List<Plate> platelist = preset.GetPlates();
            foreach (Plate plate in platelist)
            {
                lbPlates.Items.Add(plate.ToString());
            }
        }
    }
}
