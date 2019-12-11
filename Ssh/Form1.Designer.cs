namespace WindowsFormsAppKcoTestSsh
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonSSH = new System.Windows.Forms.Button();
            this.groupBoxSSH = new System.Windows.Forms.GroupBox();
            this.comboBoxPassword = new System.Windows.Forms.ComboBox();
            this.comboBoxUser = new System.Windows.Forms.ComboBox();
            this.comboBoxIpAddress = new System.Windows.Forms.ComboBox();
            this.labelCommand = new System.Windows.Forms.Label();
            this.comboBoxCommand = new System.Windows.Forms.ComboBox();
            this.textHistorique = new System.Windows.Forms.TextBox();
            this.buttonStreamRead = new System.Windows.Forms.Button();
            this.buttonSendCtrlC = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.buttonQuit = new System.Windows.Forms.Button();
            this.buttonCommandRead = new System.Windows.Forms.Button();
            this.groupBoxSSH.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonSSH
            // 
            this.buttonSSH.Location = new System.Drawing.Point(133, 19);
            this.buttonSSH.Name = "buttonSSH";
            this.buttonSSH.Size = new System.Drawing.Size(92, 33);
            this.buttonSSH.TabIndex = 0;
            this.buttonSSH.Text = "Connect";
            this.buttonSSH.UseVisualStyleBackColor = true;
            this.buttonSSH.Click += new System.EventHandler(this.buttonSSH_Click);
            // 
            // groupBoxSSH
            // 
            this.groupBoxSSH.Controls.Add(this.comboBoxPassword);
            this.groupBoxSSH.Controls.Add(this.comboBoxUser);
            this.groupBoxSSH.Controls.Add(this.comboBoxIpAddress);
            this.groupBoxSSH.Controls.Add(this.buttonSSH);
            this.groupBoxSSH.Location = new System.Drawing.Point(12, 12);
            this.groupBoxSSH.Name = "groupBoxSSH";
            this.groupBoxSSH.Size = new System.Drawing.Size(231, 100);
            this.groupBoxSSH.TabIndex = 1;
            this.groupBoxSSH.TabStop = false;
            this.groupBoxSSH.Text = "SSH Connection";
            // 
            // comboBoxPassword
            // 
            this.comboBoxPassword.FormattingEnabled = true;
            this.comboBoxPassword.Items.AddRange(new object[] {
            "temppwd",
            "q"});
            this.comboBoxPassword.Location = new System.Drawing.Point(6, 75);
            this.comboBoxPassword.Name = "comboBoxPassword";
            this.comboBoxPassword.Size = new System.Drawing.Size(121, 21);
            this.comboBoxPassword.TabIndex = 4;
            // 
            // comboBoxUser
            // 
            this.comboBoxUser.FormattingEnabled = true;
            this.comboBoxUser.Items.AddRange(new object[] {
            "debian",
            "root"});
            this.comboBoxUser.Location = new System.Drawing.Point(6, 48);
            this.comboBoxUser.Name = "comboBoxUser";
            this.comboBoxUser.Size = new System.Drawing.Size(121, 21);
            this.comboBoxUser.TabIndex = 3;
            // 
            // comboBoxIpAddress
            // 
            this.comboBoxIpAddress.FormattingEnabled = true;
            this.comboBoxIpAddress.Items.AddRange(new object[] {
            "192.168.7.2",
            "192.168.128.79"});
            this.comboBoxIpAddress.Location = new System.Drawing.Point(6, 19);
            this.comboBoxIpAddress.Name = "comboBoxIpAddress";
            this.comboBoxIpAddress.Size = new System.Drawing.Size(121, 21);
            this.comboBoxIpAddress.TabIndex = 2;
            // 
            // labelCommand
            // 
            this.labelCommand.AutoSize = true;
            this.labelCommand.Location = new System.Drawing.Point(19, 133);
            this.labelCommand.Name = "labelCommand";
            this.labelCommand.Size = new System.Drawing.Size(57, 13);
            this.labelCommand.TabIndex = 2;
            this.labelCommand.Text = "Command:";
            // 
            // comboBoxCommand
            // 
            this.comboBoxCommand.FormattingEnabled = true;
            this.comboBoxCommand.Items.AddRange(new object[] {
            "pwd",
            "ls",
            "date; sleep 5; date",
            "watch date",
            "./testdate.sh",
            "./t.sh"});
            this.comboBoxCommand.Location = new System.Drawing.Point(22, 149);
            this.comboBoxCommand.Name = "comboBoxCommand";
            this.comboBoxCommand.Size = new System.Drawing.Size(121, 21);
            this.comboBoxCommand.TabIndex = 5;
            // 
            // textHistorique
            // 
            this.textHistorique.Location = new System.Drawing.Point(22, 187);
            this.textHistorique.Multiline = true;
            this.textHistorique.Name = "textHistorique";
            this.textHistorique.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textHistorique.Size = new System.Drawing.Size(481, 128);
            this.textHistorique.TabIndex = 6;
            // 
            // buttonStreamRead
            // 
            this.buttonStreamRead.Enabled = false;
            this.buttonStreamRead.Location = new System.Drawing.Point(241, 123);
            this.buttonStreamRead.Name = "buttonStreamRead";
            this.buttonStreamRead.Size = new System.Drawing.Size(109, 23);
            this.buttonStreamRead.TabIndex = 5;
            this.buttonStreamRead.Text = "Stream Read";
            this.buttonStreamRead.UseVisualStyleBackColor = true;
            this.buttonStreamRead.Click += new System.EventHandler(this.buttonStreamRead_Click);
            // 
            // buttonSendCtrlC
            // 
            this.buttonSendCtrlC.Enabled = false;
            this.buttonSendCtrlC.Location = new System.Drawing.Point(149, 123);
            this.buttonSendCtrlC.Name = "buttonSendCtrlC";
            this.buttonSendCtrlC.Size = new System.Drawing.Size(69, 47);
            this.buttonSendCtrlC.TabIndex = 7;
            this.buttonSendCtrlC.Text = "Send CTRL-C";
            this.buttonSendCtrlC.UseVisualStyleBackColor = true;
            this.buttonSendCtrlC.Click += new System.EventHandler(this.buttonSendCtrlC_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(22, 321);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(75, 23);
            this.buttonClear.TabIndex = 8;
            this.buttonClear.Text = "clear";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // buttonQuit
            // 
            this.buttonQuit.Location = new System.Drawing.Point(428, 321);
            this.buttonQuit.Name = "buttonQuit";
            this.buttonQuit.Size = new System.Drawing.Size(75, 23);
            this.buttonQuit.TabIndex = 10;
            this.buttonQuit.Text = "Quit";
            this.buttonQuit.UseVisualStyleBackColor = true;
            this.buttonQuit.Click += new System.EventHandler(this.buttonQuit_Click);
            // 
            // buttonCommandRead
            // 
            this.buttonCommandRead.Enabled = false;
            this.buttonCommandRead.Location = new System.Drawing.Point(241, 152);
            this.buttonCommandRead.Name = "buttonCommandRead";
            this.buttonCommandRead.Size = new System.Drawing.Size(109, 23);
            this.buttonCommandRead.TabIndex = 11;
            this.buttonCommandRead.Text = "Command Read";
            this.buttonCommandRead.UseVisualStyleBackColor = true;
            this.buttonCommandRead.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(515, 352);
            this.Controls.Add(this.buttonCommandRead);
            this.Controls.Add(this.buttonQuit);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.buttonSendCtrlC);
            this.Controls.Add(this.buttonStreamRead);
            this.Controls.Add(this.textHistorique);
            this.Controls.Add(this.comboBoxCommand);
            this.Controls.Add(this.labelCommand);
            this.Controls.Add(this.groupBoxSSH);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBoxSSH.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonSSH;
        private System.Windows.Forms.GroupBox groupBoxSSH;
        private System.Windows.Forms.ComboBox comboBoxPassword;
        private System.Windows.Forms.ComboBox comboBoxUser;
        private System.Windows.Forms.ComboBox comboBoxIpAddress;
        private System.Windows.Forms.Label labelCommand;
        private System.Windows.Forms.ComboBox comboBoxCommand;
        private System.Windows.Forms.TextBox textHistorique;
        private System.Windows.Forms.Button buttonStreamRead;
        private System.Windows.Forms.Button buttonSendCtrlC;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonQuit;
        private System.Windows.Forms.Button buttonCommandRead;
    }
}

