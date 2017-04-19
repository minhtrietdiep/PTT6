namespace CalibrationPlateChangerClient {
    partial class PresetForm {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.lbPlates = new System.Windows.Forms.ListBox();
            this.lblPresetName = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lbPlates
            // 
            this.lbPlates.FormattingEnabled = true;
            this.lbPlates.Location = new System.Drawing.Point(12, 25);
            this.lbPlates.Name = "lbPlates";
            this.lbPlates.Size = new System.Drawing.Size(150, 199);
            this.lbPlates.TabIndex = 0;
            // 
            // lblPresetName
            // 
            this.lblPresetName.AutoSize = true;
            this.lblPresetName.Location = new System.Drawing.Point(65, 9);
            this.lblPresetName.Name = "lblPresetName";
            this.lblPresetName.Size = new System.Drawing.Size(45, 13);
            this.lblPresetName.TabIndex = 1;
            this.lblPresetName.Text = "<name>";
            // 
            // PresetForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(174, 232);
            this.Controls.Add(this.lblPresetName);
            this.Controls.Add(this.lbPlates);
            this.Name = "PresetForm";
            this.Text = "Preset";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lbPlates;
        private System.Windows.Forms.Label lblPresetName;
    }
}