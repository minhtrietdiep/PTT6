namespace CalibrationPlateChangerClient {
    partial class EditConfigForm {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditConfigForm));
            this.lbCollimator = new System.Windows.Forms.ListBox();
            this.lbDrive = new System.Windows.Forms.ListBox();
            this.lblCollimator = new System.Windows.Forms.Label();
            this.lblDrive = new System.Windows.Forms.Label();
            this.btnMoveToDrive = new System.Windows.Forms.Button();
            this.btnMoveToCollimator = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbCollimator
            // 
            this.lbCollimator.FormattingEnabled = true;
            this.lbCollimator.Location = new System.Drawing.Point(12, 25);
            this.lbCollimator.Name = "lbCollimator";
            this.lbCollimator.Size = new System.Drawing.Size(139, 238);
            this.lbCollimator.TabIndex = 0;
            // 
            // lbDrive
            // 
            this.lbDrive.FormattingEnabled = true;
            this.lbDrive.Location = new System.Drawing.Point(215, 25);
            this.lbDrive.Name = "lbDrive";
            this.lbDrive.Size = new System.Drawing.Size(139, 238);
            this.lbDrive.TabIndex = 1;
            // 
            // lblCollimator
            // 
            this.lblCollimator.AutoSize = true;
            this.lblCollimator.Location = new System.Drawing.Point(53, 9);
            this.lblCollimator.Name = "lblCollimator";
            this.lblCollimator.Size = new System.Drawing.Size(52, 13);
            this.lblCollimator.TabIndex = 2;
            this.lblCollimator.Text = "Collimator";
            // 
            // lblDrive
            // 
            this.lblDrive.AutoSize = true;
            this.lblDrive.Location = new System.Drawing.Point(268, 9);
            this.lblDrive.Name = "lblDrive";
            this.lblDrive.Size = new System.Drawing.Size(32, 13);
            this.lblDrive.TabIndex = 3;
            this.lblDrive.Text = "Drive";
            // 
            // btnMoveToDrive
            // 
            this.btnMoveToDrive.Location = new System.Drawing.Point(157, 99);
            this.btnMoveToDrive.Name = "btnMoveToDrive";
            this.btnMoveToDrive.Size = new System.Drawing.Size(52, 23);
            this.btnMoveToDrive.TabIndex = 4;
            this.btnMoveToDrive.Text = ">>>";
            this.btnMoveToDrive.UseVisualStyleBackColor = true;
            this.btnMoveToDrive.Click += new System.EventHandler(this.btnMoveToDrive_Click);
            // 
            // btnMoveToCollimator
            // 
            this.btnMoveToCollimator.Location = new System.Drawing.Point(157, 137);
            this.btnMoveToCollimator.Name = "btnMoveToCollimator";
            this.btnMoveToCollimator.Size = new System.Drawing.Size(52, 23);
            this.btnMoveToCollimator.TabIndex = 5;
            this.btnMoveToCollimator.Text = "<<<";
            this.btnMoveToCollimator.UseVisualStyleBackColor = true;
            this.btnMoveToCollimator.Click += new System.EventHandler(this.btnMoveToCollimator_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(279, 269);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 7;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // EditConfigForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(368, 297);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnMoveToCollimator);
            this.Controls.Add(this.btnMoveToDrive);
            this.Controls.Add(this.lblDrive);
            this.Controls.Add(this.lblCollimator);
            this.Controls.Add(this.lbDrive);
            this.Controls.Add(this.lbCollimator);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "EditConfigForm";
            this.Text = "Edit current configuration";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lbCollimator;
        private System.Windows.Forms.ListBox lbDrive;
        private System.Windows.Forms.Label lblCollimator;
        private System.Windows.Forms.Label lblDrive;
        private System.Windows.Forms.Button btnMoveToDrive;
        private System.Windows.Forms.Button btnMoveToCollimator;
        private System.Windows.Forms.Button btnClose;
    }
}