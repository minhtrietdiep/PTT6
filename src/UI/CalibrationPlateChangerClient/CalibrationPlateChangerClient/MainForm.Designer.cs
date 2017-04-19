namespace CalibrationPlateChangerClient {
    partial class MainForm {
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
            this.gbCurrentConfig = new System.Windows.Forms.GroupBox();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnEdit = new System.Windows.Forms.Button();
            this.lblDrive = new System.Windows.Forms.Label();
            this.lblCollimator = new System.Windows.Forms.Label();
            this.lbDrivePlates = new System.Windows.Forms.ListBox();
            this.lbCollimatorPlates = new System.Windows.Forms.ListBox();
            this.gbChoosePreset = new System.Windows.Forms.GroupBox();
            this.btnShowPreset = new System.Windows.Forms.Button();
            this.btnLoadPreset = new System.Windows.Forms.Button();
            this.cbPresets = new System.Windows.Forms.ComboBox();
            this.gbActionLog = new System.Windows.Forms.GroupBox();
            this.lbL = new System.Windows.Forms.ListBox();
            this.gbGeneralActions = new System.Windows.Forms.GroupBox();
            this.btnContinueSystem = new System.Windows.Forms.Button();
            this.btnEmergencyStop = new System.Windows.Forms.Button();
            this.btnCancelOperation = new System.Windows.Forms.Button();
            this.gbCurrentConfig.SuspendLayout();
            this.gbChoosePreset.SuspendLayout();
            this.gbActionLog.SuspendLayout();
            this.gbGeneralActions.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbCurrentConfig
            // 
            this.gbCurrentConfig.Controls.Add(this.btnReset);
            this.gbCurrentConfig.Controls.Add(this.btnEdit);
            this.gbCurrentConfig.Controls.Add(this.lblDrive);
            this.gbCurrentConfig.Controls.Add(this.lblCollimator);
            this.gbCurrentConfig.Controls.Add(this.lbDrivePlates);
            this.gbCurrentConfig.Controls.Add(this.lbCollimatorPlates);
            this.gbCurrentConfig.Location = new System.Drawing.Point(12, 12);
            this.gbCurrentConfig.Name = "gbCurrentConfig";
            this.gbCurrentConfig.Size = new System.Drawing.Size(387, 284);
            this.gbCurrentConfig.TabIndex = 0;
            this.gbCurrentConfig.TabStop = false;
            this.gbCurrentConfig.Text = "Current configuration";
            // 
            // btnReset
            // 
            this.btnReset.Location = new System.Drawing.Point(194, 253);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(75, 23);
            this.btnReset.TabIndex = 5;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnEdit
            // 
            this.btnEdit.Location = new System.Drawing.Point(113, 253);
            this.btnEdit.Name = "btnEdit";
            this.btnEdit.Size = new System.Drawing.Size(75, 23);
            this.btnEdit.TabIndex = 4;
            this.btnEdit.Text = "Edit";
            this.btnEdit.UseVisualStyleBackColor = true;
            this.btnEdit.Click += new System.EventHandler(this.btnEdit_Click);
            // 
            // lblDrive
            // 
            this.lblDrive.AutoSize = true;
            this.lblDrive.Location = new System.Drawing.Point(272, 32);
            this.lblDrive.Name = "lblDrive";
            this.lblDrive.Size = new System.Drawing.Size(32, 13);
            this.lblDrive.TabIndex = 3;
            this.lblDrive.Text = "Drive";
            // 
            // lblCollimator
            // 
            this.lblCollimator.AutoSize = true;
            this.lblCollimator.Location = new System.Drawing.Point(70, 32);
            this.lblCollimator.Name = "lblCollimator";
            this.lblCollimator.Size = new System.Drawing.Size(52, 13);
            this.lblCollimator.TabIndex = 2;
            this.lblCollimator.Text = "Collimator";
            // 
            // lbDrivePlates
            // 
            this.lbDrivePlates.FormattingEnabled = true;
            this.lbDrivePlates.Location = new System.Drawing.Point(214, 48);
            this.lbDrivePlates.Name = "lbDrivePlates";
            this.lbDrivePlates.Size = new System.Drawing.Size(144, 199);
            this.lbDrivePlates.TabIndex = 1;
            // 
            // lbCollimatorPlates
            // 
            this.lbCollimatorPlates.FormattingEnabled = true;
            this.lbCollimatorPlates.Location = new System.Drawing.Point(23, 48);
            this.lbCollimatorPlates.Name = "lbCollimatorPlates";
            this.lbCollimatorPlates.Size = new System.Drawing.Size(144, 199);
            this.lbCollimatorPlates.TabIndex = 0;
            // 
            // gbChoosePreset
            // 
            this.gbChoosePreset.Controls.Add(this.btnShowPreset);
            this.gbChoosePreset.Controls.Add(this.btnLoadPreset);
            this.gbChoosePreset.Controls.Add(this.cbPresets);
            this.gbChoosePreset.Location = new System.Drawing.Point(415, 12);
            this.gbChoosePreset.Name = "gbChoosePreset";
            this.gbChoosePreset.Size = new System.Drawing.Size(218, 123);
            this.gbChoosePreset.TabIndex = 1;
            this.gbChoosePreset.TabStop = false;
            this.gbChoosePreset.Text = "Choose preset";
            // 
            // btnShowPreset
            // 
            this.btnShowPreset.Location = new System.Drawing.Point(48, 56);
            this.btnShowPreset.Name = "btnShowPreset";
            this.btnShowPreset.Size = new System.Drawing.Size(121, 23);
            this.btnShowPreset.TabIndex = 2;
            this.btnShowPreset.Text = "Show preset";
            this.btnShowPreset.UseVisualStyleBackColor = true;
            this.btnShowPreset.Click += new System.EventHandler(this.btnShowPreset_Click);
            // 
            // btnLoadPreset
            // 
            this.btnLoadPreset.Location = new System.Drawing.Point(48, 85);
            this.btnLoadPreset.Name = "btnLoadPreset";
            this.btnLoadPreset.Size = new System.Drawing.Size(121, 23);
            this.btnLoadPreset.TabIndex = 1;
            this.btnLoadPreset.Text = "Load preset";
            this.btnLoadPreset.UseVisualStyleBackColor = true;
            this.btnLoadPreset.Click += new System.EventHandler(this.btnLoadPreset_Click);
            // 
            // cbPresets
            // 
            this.cbPresets.FormattingEnabled = true;
            this.cbPresets.Location = new System.Drawing.Point(48, 29);
            this.cbPresets.Name = "cbPresets";
            this.cbPresets.Size = new System.Drawing.Size(121, 21);
            this.cbPresets.TabIndex = 0;
            // 
            // gbActionLog
            // 
            this.gbActionLog.Controls.Add(this.lbL);
            this.gbActionLog.Location = new System.Drawing.Point(415, 141);
            this.gbActionLog.Name = "gbActionLog";
            this.gbActionLog.Size = new System.Drawing.Size(218, 220);
            this.gbActionLog.TabIndex = 2;
            this.gbActionLog.TabStop = false;
            this.gbActionLog.Text = "Action log";
            // 
            // lbL
            // 
            this.lbL.FormattingEnabled = true;
            this.lbL.Location = new System.Drawing.Point(7, 20);
            this.lbL.Name = "lbL";
            this.lbL.Size = new System.Drawing.Size(205, 186);
            this.lbL.TabIndex = 0;
            // 
            // gbGeneralActions
            // 
            this.gbGeneralActions.Controls.Add(this.btnContinueSystem);
            this.gbGeneralActions.Controls.Add(this.btnEmergencyStop);
            this.gbGeneralActions.Controls.Add(this.btnCancelOperation);
            this.gbGeneralActions.Location = new System.Drawing.Point(13, 302);
            this.gbGeneralActions.Name = "gbGeneralActions";
            this.gbGeneralActions.Size = new System.Drawing.Size(386, 59);
            this.gbGeneralActions.TabIndex = 3;
            this.gbGeneralActions.TabStop = false;
            this.gbGeneralActions.Text = "General";
            // 
            // btnContinueSystem
            // 
            this.btnContinueSystem.Location = new System.Drawing.Point(258, 22);
            this.btnContinueSystem.Name = "btnContinueSystem";
            this.btnContinueSystem.Size = new System.Drawing.Size(99, 23);
            this.btnContinueSystem.TabIndex = 2;
            this.btnContinueSystem.Text = "Continue system";
            this.btnContinueSystem.UseVisualStyleBackColor = true;
            this.btnContinueSystem.Click += new System.EventHandler(this.btnContinueSystem_Click);
            // 
            // btnEmergencyStop
            // 
            this.btnEmergencyStop.Location = new System.Drawing.Point(139, 22);
            this.btnEmergencyStop.Name = "btnEmergencyStop";
            this.btnEmergencyStop.Size = new System.Drawing.Size(99, 23);
            this.btnEmergencyStop.TabIndex = 1;
            this.btnEmergencyStop.Text = "Emergency stop";
            this.btnEmergencyStop.UseVisualStyleBackColor = true;
            this.btnEmergencyStop.Click += new System.EventHandler(this.btnEmergencyStop_Click);
            // 
            // btnCancelOperation
            // 
            this.btnCancelOperation.Location = new System.Drawing.Point(22, 22);
            this.btnCancelOperation.Name = "btnCancelOperation";
            this.btnCancelOperation.Size = new System.Drawing.Size(99, 23);
            this.btnCancelOperation.TabIndex = 0;
            this.btnCancelOperation.Text = "Cancel operation";
            this.btnCancelOperation.UseVisualStyleBackColor = true;
            this.btnCancelOperation.Click += new System.EventHandler(this.btnCancelOperation_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(651, 374);
            this.Controls.Add(this.gbGeneralActions);
            this.Controls.Add(this.gbActionLog);
            this.Controls.Add(this.gbChoosePreset);
            this.Controls.Add(this.gbCurrentConfig);
            this.Name = "MainForm";
            this.Text = "Form1";
            this.gbCurrentConfig.ResumeLayout(false);
            this.gbCurrentConfig.PerformLayout();
            this.gbChoosePreset.ResumeLayout(false);
            this.gbActionLog.ResumeLayout(false);
            this.gbGeneralActions.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbCurrentConfig;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnEdit;
        private System.Windows.Forms.Label lblDrive;
        private System.Windows.Forms.Label lblCollimator;
        private System.Windows.Forms.ListBox lbDrivePlates;
        private System.Windows.Forms.ListBox lbCollimatorPlates;
        private System.Windows.Forms.GroupBox gbChoosePreset;
        private System.Windows.Forms.Button btnLoadPreset;
        private System.Windows.Forms.ComboBox cbPresets;
        private System.Windows.Forms.GroupBox gbActionLog;
        private System.Windows.Forms.ListBox lbL;
        private System.Windows.Forms.Button btnShowPreset;
        private System.Windows.Forms.GroupBox gbGeneralActions;
        private System.Windows.Forms.Button btnContinueSystem;
        private System.Windows.Forms.Button btnEmergencyStop;
        private System.Windows.Forms.Button btnCancelOperation;
    }
}

